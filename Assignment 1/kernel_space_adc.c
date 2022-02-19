#include<linux/init.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/device.h>
#include <linux/types.h>
#include <linux/random.h>
#include<linux/errno.h>
#include <linux/uaccess.h>
#include<linux/slab.h> 	
#include <linux/ioctl.h>
#include "chardev_adc.h"

#define Channel_select _IOW(MAJOR_NUM, 1, int *)
#define alignment_select _IOW(MAJOR_NUM, 2, int *)

uint16_t num;
uint32_t align,n;
static dev_t first; // variable for device number
static struct cdev adc; // variable for the adc
static struct class *cls; // variable for the device class

static int adc_open(struct inode *i, struct file *f)
{
	printk(KERN_INFO "adc : open()\n");
	return 0;
}

static int adc_close(struct inode *i, struct file *f)
{
	printk(KERN_INFO "adc : close()\n");
	return 0;
}

static ssize_t adc_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "adc : read()\n");
	get_random_bytes(&num, 2);
	if(align == 0)
	{
	printk(KERN_INFO "Lower 12 bits alignment\n");
	printk(KERN_INFO "value : %d\n",num);
	num=(num & 0x0FFF);
	printk(KERN_INFO "ADC value : %d\n",num);
	copy_to_user(buf, &num, 2);
	}
	
	else
	{
	printk(KERN_INFO "Higher 12 bits alignment\n");
	printk(KERN_INFO "value : %d\n",num);
	num=((num<<4) & 0xFFF0);
	printk(KERN_INFO "ADC value : %d\n",num);
	copy_to_user(buf, &num, 2);
	}
	return 0;
}

static long adc_ioctl(struct file *file, unsigned int m, unsigned long arg)
{
         switch(m) {
                case Channel_select:
                        copy_from_user(&n ,(int32_t*) arg, sizeof(num));
                        printk(KERN_INFO "ADC Channel = %d\n", n);
                        break;

                case alignment_select:
                        copy_from_user(&align ,(int32_t*) arg, sizeof(align));
                        printk(KERN_INFO "Alignment No. = %d\n", align);
                        break;
        }
        return 0;
}

static struct file_operations fops =                                 // file operation structure calling back 
{
  .owner 	= THIS_MODULE,
  .open 	= adc_open,
  .release 	= adc_close,
  .read 	= adc_read,
  .unlocked_ioctl = adc_ioctl
};
 
									// init function initialisation and creation of device and class

static int __init mychar_init(void) 
{
	printk(KERN_INFO "ADC registered");
	if (alloc_chrdev_region(&first, 0, 1, "adc-dev") < 0)
	{
		return -1;
	}
    if ((cls = class_create(THIS_MODULE, "chardrv")) == NULL)
	{
		unregister_chrdev_region(first, 1);
		return -1;
	}
    if (device_create(cls, NULL, first, NULL, "adc-dev") == NULL)
	{
		class_destroy(cls);
		unregister_chrdev_region(first, 1);
		return -1;
	}	
									// adding cdev struction 
									
    cdev_init(&adc, &fops);
    if (cdev_add(&adc, first, 1) == -1)
	{
		device_destroy(cls, first);
		class_destroy(cls);
		unregister_chrdev_region(first, 1);
		return -1;
	}
	return 0;
}
 									// exit function declaration and deletion of cdev, device,class
static void __exit mychar_exit(void) 
{
	cdev_del(&adc);
	device_destroy(cls, first);
	class_destroy(cls);
	unregister_chrdev_region(first, 1);
	printk(KERN_INFO "ADC unregistered\n\n");
}
 
module_init(mychar_init);
module_exit(mychar_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Suhas_Rahul");
MODULE_DESCRIPTION("Device Driver for ADC");
