#include <linux/cdev.h>   // cdev_add, cdev_init
#include <linux/uaccess.h>  // copy_to_user
#include <linux/module.h> // module_init, GPL
#include <linux/spi/spi.h> // spi_sync,
#include <linux/kernel.h>
#include <linux/of_gpio.h>
#include <linux/gpio.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>

#define MAXLEN 32
#define MODULE_DEBUG 1   // Enable/Disable Debug messages

static int flag = 0;
static DECLARE_WAIT_QUEUE_HEAD(wq);

int gpios_len;
static struct platform_driver led_drv;


struct gpio_dev {
  int no;   // GPIO number
  int dir; // 0: in, 1: out
  int enable;
};

static struct gpio_dev gpio_devs[255];

/* Char Driver Globals */
static struct spi_driver spi_drv_spi_driver;
struct file_operations spi_drv_fops;
static struct class *spi_drv_class;
static dev_t devno;
static struct cdev spi_drv_cdev;

/* Definition of SPI devices */
struct Myspi {
  struct spi_device *spi; // Pointer to SPI device
  int channel;            // channel, ex. adc ch 0
  int datain;
};
/* Array of SPI devices */
/* Minor used to index array */
struct Myspi spi_devs[4];
const int spi_devs_len = 4;  // Max nbr of devices
static int spi_devs_cnt = 0; // Nbr devices present
int my_spi_read_byte(struct file *filep, struct spi_device *spi, int *data);
ssize_t gpio_drv_read(struct file *filep, char __user *ubuf, size_t count, loff_t *f_pos);
/* Macro to handle Errors */
#define ERRGOTO(label, ...)                     \
  {                                             \
    printk (__VA_ARGS__);                       \
    goto label;                                 \
  } while(0)

/**********************************************************
 * CHARACTER DRIVER METHODS
 **********************************************************/

irqreturn_t handle_gpio_irq(int irq, void *dev_id)
{
  printk(KERN_ALERT "Haha, would you look at that. Morten is fucking a big ass cow again today. It's like the fifth time that has happened this week! That's why we call him the cow fucker! What a man!\n");
  flag = 1;
  wake_up_interruptible(&wq);
  return IRQ_HANDLED;
}

/*
 * Character Driver Module Init Method
 */
static int __init spi_drv_init(void)
{
  int err=0;
  
  printk("spi_drv driver initializing\n");

  /* Allocate major number and register fops*/
  err = alloc_chrdev_region(&devno, 0, 255, "spi_drv driver");
  if(MAJOR(devno) <= 0)
    ERRGOTO(err_no_cleanup, "Failed to register chardev\n");
  printk("Assigned major no: %i\n", MAJOR(devno));

  cdev_init(&spi_drv_cdev, &spi_drv_fops);
  err = cdev_add(&spi_drv_cdev, devno, 255);
  if (err)
    ERRGOTO(err_cleanup_chrdev, "Failed to create class");

  /* Polulate sysfs entries */
  spi_drv_class = class_create(THIS_MODULE, "spi_drv_class");
  if (IS_ERR(spi_drv_class))
    ERRGOTO(err_cleanup_cdev, "Failed to create class");

  /* Register SPI Driver */
  /* THIS WILL INVOKE PROBE, IF DEVICE IS PRESENT!!! */
  err = spi_register_driver(&spi_drv_spi_driver);
  if(err)
    ERRGOTO(err_cleanup_class, "Failed SPI Registration\n");

  err = platform_driver_register(&led_drv);
  if(err)
    ERRGOTO(err_cleanup_class, "Failed GPIO Registration\n");

  /* Success */
  return 0;

  /* Errors during Initialization */
 err_cleanup_class:
  class_destroy(spi_drv_class);

 err_cleanup_cdev:
  cdev_del(&spi_drv_cdev);

 err_cleanup_chrdev:
  unregister_chrdev_region(devno, 255);

 err_no_cleanup:
  return err;
}

/*
 * Character Driver Module Exit Method
 */
static void __exit spi_drv_exit(void)
{
  printk("spi_drv driver Exit\n");

  platform_driver_unregister(&led_drv);
  spi_unregister_driver(&spi_drv_spi_driver);
  class_destroy(spi_drv_class);
  cdev_del(&spi_drv_cdev);
  unregister_chrdev_region(devno, 255);
}

/*
 * Character Driver Write File Operations Method
 */
ssize_t spi_drv_write(struct file *filep, const char __user *ubuf,
                      size_t count, loff_t *f_pos)
{
  int minor, len, value;
  char kbuf[MAXLEN];

  minor = iminor(filep->f_inode);

  if(gpio_devs[minor].enable == 1)
  {
    return count;
  }

  printk(KERN_ALERT "Writing to spi_drv [Minor] %i \n", minor);

  /* Limit copy length to MAXLEN allocated andCopy from user */
  len = count < MAXLEN ? count : MAXLEN;
  if(copy_from_user(kbuf, ubuf, len))
    return -EFAULT;

  /* Pad null termination to string */
  kbuf[len] = '\0';

  if(MODULE_DEBUG)
    printk("string from user: %s\n", kbuf);

  /* Convert sting to int */
  sscanf(kbuf,"%i", &value);
  if(MODULE_DEBUG)
    printk("value %i\n", value);

  /* Legacy file ptr f_pos. Used to support
   * random access but in char drv we dont!
   * Move it the length actually  written
   * for compability */
  *f_pos += len;

  /* return length actually written */
  return len;
}

/*
 * Character Driver Read File Operations Method
 */
ssize_t spi_drv_read(struct file *filep, char __user *ubuf,
                     size_t count, loff_t *f_pos)
{
  int minor, len;
  int resultBuf[MAXLEN];
  s16 result=1234;

  minor = iminor(filep->f_inode);

  if(gpio_devs[minor].enable == 1)
  {
    return gpio_drv_read(filep, ubuf, count, f_pos);
  }

  //my_spi_read_byte(filep, spi_devs[minor].spi, &(spi_devs[minor].datain));
  //result = spi_devs[minor].datain;

  result = ((120 << 8) + 9);
  resultBuf[0] = (result >> 8);
  resultBuf[1] = (result & 255);

  if(MODULE_DEBUG)
    printk(KERN_ALERT "%s-%i read: %i\n",
           spi_devs[minor].spi->modalias, spi_devs[minor].channel, result);

  /* Copy data to user space */
  if(copy_to_user(ubuf, resultBuf, 16))
    return -EFAULT;

  /* Move fileptr */
  //*f_pos += len;
  return 16;
}

int mygpio_open(struct inode *inode, struct file *filep)
{
    int major, minor, err = 0, irq = -1;
    major = MAJOR(inode->i_rdev);
    minor = MINOR(inode->i_rdev);

    printk("Opening Device [major], [minor]: %i, %i\n", major, minor);


    if(gpio_devs[minor].enable == 1)
        {
          printk("gpio no: %i", gpio_devs[minor].no);
          irq = gpio_to_irq(gpio_devs[minor].no);
          err = request_irq(irq, handle_gpio_irq, IRQF_TRIGGER_RISING, "my_irq", NULL);
          if (err < 0)
              {
                  printk(KERN_ALERT "request_irg failed with %d\n", err);
                  goto errhandler;
              }

              printk("IRQ allocated: %i\n", irq);
        }
    
    return 0;
    errhandler:
    return err;
}

int mygpio_release(struct inode *inode, struct file *filep)
{
   int minor, major;
   
   major = MAJOR(inode->i_rdev);
   minor = MINOR(inode->i_rdev);
   int irq = gpio_to_irq(gpio_devs[minor].no);


    if(gpio_devs[minor].enable == 1)
    {
        free_irq(irq, NULL);
        printk("Releasing irq: %i", irq);
    }

   printk("Releasing Device [major], [minor]: %i, %i\n", major, minor);

   return 0;
}

ssize_t gpio_drv_read(struct file *filep, char __user *ubuf, size_t count, loff_t *f_pos)
{
  wait_event_interruptible(wq, flag==1);
  flag = 0;
  char buf2[2] = {1, '\0'};

 if(copy_to_user(ubuf, buf2, 2))
    return -EFAULT;

  return 2;
}

ssize_t my_spi_read_byte(struct file *filep, struct spi_device *spi, int *data)
{
  /*protokol: 2 buffere, en til sekunder (120 i alt) en til millisek (9 i alt)
  0111 1000 er 120 i bin. 
  fejlhåndtering. Overvej måske at der altid sendes et start bit på 1?

  */ 

  struct spi_transfer t[2];
  struct spi_message m;
  int dataSek = 0, dataMs = 0;
  int modtaget = 0x1A;

  memset(t, 0, sizeof(t));
  spi_message_init(&m);
  m.spi = spi;

  t[0].tx_buf = &modtaget;
  t[0].rx_buf = &dataSek;
  t[0].len = 1;
  spi_message_add_tail(&t[0], &m);

  t[1].tx_buf = &modtaget; 
  t[1].rx_buf = &dataMs;
  t[1].len = 1;
  spi_message_add_tail(&t[1], &m);

  int err = spi_sync(m.spi, &m);
  if (err < 0)
  {
    printk(KERN_ALERT "SPI communication error");
    printk("Error code%i", err);
    return -EFAULT;
  }
  int Msparity = (dataMs >> 2) % 2;
  int Sekparity = dataSek % 2;

  if (((dataMs & 1) != 0) && (Msparity == 0)){
    dataMs = 169;
    dataSek = 169;
    return 0;
  } 

  if (((dataMs & 2) != 0) && (Sekparity == 0)){
    dataMs = 169;
    dataSek = 169;
    return 0;
  }

  dataMs = dataMs >> 2;
  dataSek = dataSek << 8;
  data[0] = dataSek + dataMs;

  return 0;
}

/*
 * Character Driver File Operations Structure
 */
struct file_operations spi_drv_fops =
  {
    .owner   = THIS_MODULE,
    .write   = spi_drv_write,
    .read    = spi_drv_read,
    .release = mygpio_release,
    .open    = mygpio_open,
  };

/**********************************************************
 * LINUX DEVICE MODEL METHODS (spi)
 **********************************************************/

/*
 * spi_drv Probe
 * Called when a device with the name "spi_drv" is
 * registered.
 */
static int spi_drv_probe(struct spi_device *sdev)
{
  int err = 0;
  struct device *spi_drv_device;

  printk(KERN_DEBUG "New SPI device: %s using chip select: %i\n",
         sdev->modalias, sdev->chip_select);

  /* Check we are not creating more
     devices than we have space for */
  if (spi_devs_cnt > spi_devs_len) {
    printk(KERN_ERR "Too many SPI devices for driver\n");
    return -ENODEV;
  }

  /* Configure bits_per_word, always 8-bit for RPI!!! */
  sdev->bits_per_word = 8;
  spi_setup(sdev);

  /* Create devices, populate sysfs and
     active udev to create devices in /dev */

  /* We map spi_devs index to minor number here */
  spi_drv_device = device_create(spi_drv_class, NULL,
                                 MKDEV(MAJOR(devno), spi_devs_cnt),
                                 NULL, "SPI_%d", spi_devs_cnt);
  if (IS_ERR(spi_drv_device))
    printk(KERN_ALERT "FAILED TO CREATE DEVICE\n");
  else
    printk(KERN_ALERT "Using spi_devs%i on major:%i, minor:%i\n",
           spi_devs_cnt, MAJOR(devno), spi_devs_cnt);

  /* Update local array of SPI devices */
  spi_devs[spi_devs_cnt].spi = sdev;
  spi_devs[spi_devs_cnt].channel = 0x00; // channel address
  ++spi_devs_cnt;

  return err;
}

/*
 * spi_drv Remove
 * Called when the device is removed
 * Can deallocate data if needed
 */
static int spi_drv_remove(struct spi_device *sdev)
{
  int its_minor = 0;

  printk (KERN_ALERT "Removing spi device\n");

  /* Destroy devices created in probe() */
  device_destroy(spi_drv_class, MKDEV(MAJOR(devno), its_minor));

  return 0;
}

static int my_led_probe(struct platform_device *pdev)
{
    int err = 0;
    struct device *dev = &pdev->dev; // Device ptr derived from current platform_device
    struct device_node *np = dev->of_node; // Device tree node ptr
    enum of_gpio_flags flags;
    static struct device *my_gpio_device;
    int index_gpio = 0;
    gpios_len = of_gpio_count(np);

    while((index_gpio < gpios_len))
    {
      gpio_devs[spi_devs_cnt].no = of_get_gpio(np, index_gpio);
      of_get_gpio_flags(np, index_gpio, &flags);
      gpio_devs[spi_devs_cnt].dir = flags;
      gpio_devs[spi_devs_cnt].enable = 1;
      
      int err = 0;
      err = gpio_request(gpio_devs[spi_devs_cnt].no, "LED");
      if(err < 0)
      {
          goto gpio_err;
      }

      // Set GPIO direction (in or out)
      if(gpio_devs[spi_devs_cnt].dir == 1)
      {
          err = gpio_direction_output(gpio_devs[spi_devs_cnt].no, 0);
          if (err < 0) goto err_gpio;
      }else{
          err = gpio_direction_input(gpio_devs[spi_devs_cnt].no);
          if (err < 0) goto err_gpio;
      }

      if(IS_ERR(my_gpio_device = device_create(spi_drv_class, NULL, MKDEV(MAJOR(devno), spi_devs_cnt), NULL, "mygpio%d", gpio_devs[spi_devs_cnt].no)))
    {
      printk(KERN_ALERT "FAILED TO CREATE DEVICE\n");
      goto gpio_err;
    }
      printk(KERN_ALERT "Created /dev/mygpio%i with major:%i, minor:%i direction:%i\n", gpio_devs[spi_devs_cnt].no, MAJOR(devno), spi_devs_cnt, gpio_devs[spi_devs_cnt].dir);
      index_gpio++;
      spi_devs_cnt++;
    }

    return 0;
    err_gpio:
        for(int i = 0; i <gpios_len; i++)
        {
            gpio_free(gpio_devs[i].no);
        }
    gpio_err:
    printk(KERN_ALERT "GPIO ERROR\n");

        return err;
}

static int my_led_remove(struct platform_device *pdev)
{  
    for(int i = 0; i < (spi_devs_cnt+1); i++)
    {
        if(gpio_devs[i].enable == 1)
        {
          printk("Free gpio:%i\n", gpio_devs[i].no);
          // Free GPIO
          gpio_free(gpio_devs[i].no);
          printk(KERN_ALERT "Removing Platform device\n");
          device_destroy(spi_drv_class, MKDEV(MAJOR(devno), i));
        }

    }
    return 0;
}

/*
 * spi Driver Struct
 * Holds function pointers to probe/release
 * methods and the name under which it is registered
 */
static const struct of_device_id of_spi_drv_spi_device_match[] = {
  { .compatible = "ase, spi_drv", }, {},
};

static struct spi_driver spi_drv_spi_driver = {
  .probe      = spi_drv_probe,
  .remove     = spi_drv_remove,
  .driver     = {
    .name   = "spi_drv",
    .bus    = &spi_bus_type,
    .of_match_table = of_spi_drv_spi_device_match,
    .owner  = THIS_MODULE,
  },
};

static const struct of_device_id led_drv_device_match[] = 
{
    { .compatible = "ase, plat_drv",}, {},
};

static struct platform_driver led_drv =
	{
		.probe = my_led_probe,
		.remove = my_led_remove,
		.driver = {
			.name = "my_gpio_platdev",
			.of_match_table = led_drv_device_match,
			.owner = THIS_MODULE,
		    }
};

/**********************************************************
 * GENERIC LINUX DEVICE DRIVER STUFF
 **********************************************************/

/*
 * Assignment of module init/exit methods
 */
module_init(spi_drv_init);
module_exit(spi_drv_exit);

/*
 * Assignment of author and license
 */
MODULE_AUTHOR("Peter Hoegh Mikkelsen <phm@ase.au.dk>");
MODULE_LICENSE("GPL");
