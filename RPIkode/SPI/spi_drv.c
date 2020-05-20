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
#define MODULE_DEBUG 0   // Enable/Disable Debug messages

static int flag = 0;
static DECLARE_WAIT_QUEUE_HEAD(wq);

int gpios_len;
static struct platform_driver gpio_drv;

/* Definition of GPIO devices */
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
int spi_drv_read_byte(struct file *filep, struct spi_device *spi, int *data);
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
  printk(KERN_ALERT "Interrupt from Slave!\n");
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

  err = platform_driver_register(&gpio_drv);
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

  platform_driver_unregister(&gpio_drv);
  spi_unregister_driver(&spi_drv_spi_driver);
  class_destroy(spi_drv_class);
  cdev_del(&spi_drv_cdev);
  unregister_chrdev_region(devno, 255);
}

/*
 * Character Driver Read File Operations Method
 */
ssize_t spi_drv_read(struct file *filep, char __user *ubuf,
                     size_t count, loff_t *f_pos)
{
  int minor;
  int resultBuf[MAXLEN];
  s16 result=1234;

  minor = iminor(filep->f_inode);       // get minor number

  if(gpio_devs[minor].enable == 1)      // check gpio enable
  {
    return gpio_drv_read(filep, ubuf, count, f_pos);        // call gpio read-function
  }

  spi_drv_read_byte(filep, spi_devs[minor].spi, &(spi_devs[minor].datain));      // call SPI read-function
  result = spi_devs[minor].datain;
  
  resultBuf[0] = (result >> 8);             // Rightshift 8 to remove everything but seconds.
  resultBuf[1] = (result & 255);            // AND with 255 to remove everything but milliseconds.

  printk("resultbuf0: %i", resultBuf[0]);
  printk("resultbuf1: %i", resultBuf[1]);

  if(MODULE_DEBUG)
    printk(KERN_ALERT "%s-%i read: %i\n",
           spi_devs[minor].spi->modalias, spi_devs[minor].channel, result);

  /* Copy data to user space */
  if(copy_to_user(ubuf, resultBuf, 16))
    return -EFAULT;

  /* Move fileptr */
  //*f_pos += len;
  return 3;
}

int gpio_open(struct inode *inode, struct file *filep)
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
                  printk(KERN_ALERT "request_irq failed with %d\n", err);
                  goto errhandler;
              }

              printk("IRQ allocated: %i\n", irq);
        }
    
    return 0;
    errhandler:
    return err;
}

int gpio_release(struct inode *inode, struct file *filep)
{
   int minor, major;
   
   major = MAJOR(inode->i_rdev);
   minor = MINOR(inode->i_rdev);


    if(gpio_devs[minor].enable == 1)
    {
        free_irq(gpio_to_irq(gpio_devs[minor].no), NULL);
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

ssize_t spi_drv_read_byte(struct file *filep, struct spi_device *spi, int *data)
{
  struct spi_transfer t[3];
  struct spi_message m;
  int dataSek = 0, dataMs = 0;
  int sendSek = 0x20;
  int sendMs = 0x10;

  memset(t, 0, sizeof(t));    //fylder t med 0
  spi_message_init(&m);
  m.spi = spi;

  t[0].tx_buf = &sendSek;
  t[0].rx_buf = NULL;
  t[0].len = 1;
  spi_message_add_tail(&t[0], &m);

  t[1].tx_buf = &sendMs;
  t[1].rx_buf = &dataSek;
  t[1].len = 1;
  spi_message_add_tail(&t[1], &m);

  t[2].tx_buf = NULL; 
  t[2].rx_buf = &dataMs;
  t[2].len = 1;
  spi_message_add_tail(&t[2], &m);

  int err = spi_sync(m.spi, &m);
  if (err < 0)
  {
    printk(KERN_ALERT "SPI communication error");
    printk("Error code%i", err);
    return -EFAULT;
  }

  printk("SEK: %i", dataSek);
  printk("MS: %i", dataMs);

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
    .read    = spi_drv_read,
    .release = gpio_release,
    .open    = gpio_open,
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
                                 NULL, "SPI_0");
  if (IS_ERR(spi_drv_device))
    printk(KERN_ALERT "FAILED TO CREATE DEVICE\n");
  else
    printk(KERN_ALERT "Using spi_devs%i on major:%i, minor:%i\n",
           spi_devs_cnt, MAJOR(devno), spi_devs_cnt);

  /* Update local array of SPI devices */
  spi_devs[spi_devs_cnt].spi = sdev;
  spi_devs[spi_devs_cnt].channel = 0x00; // channel address
  ++spi_devs_cnt;

  return 0;
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

static int gpio_probe(struct platform_device *pdev)
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
      err = gpio_request(gpio_devs[spi_devs_cnt].no, "gpio");
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

static int gpio_remove(struct platform_device *pdev)
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

static const struct of_device_id gpio_drv_device_match[] = 
{
    { .compatible = "ase, plat_drv",}, {},
};

static struct platform_driver gpio_drv =
	{
		.probe = gpio_probe,
		.remove = gpio_remove,
		.driver = {
			.name = "my_gpio_platdev",
			.of_match_table = gpio_drv_device_match,
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
MODULE_AUTHOR("Projekt gruppe 5 F2020");
MODULE_LICENSE("GPL");
