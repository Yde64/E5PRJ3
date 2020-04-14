				// You need this #include to define the printf function
#include <linux/gpio.h>
void main(int argc, char *argv[])
{
    printf("Content-type: text/html\n\n");	// Tell the browser the type of document being sent

    printk("<html>");
    printk("<head>");
    printk("<title>Test</title>");
    printk("</head>");
    printk("<body>");
    printk("<p>Hello world!</p>");
    printk("</body>");
    printk("</html>");
    return;
}