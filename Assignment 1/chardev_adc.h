#ifndef CHARDEV_H
#define CHARDEV_H

#include <linux/ioctl.h>

#define MAJOR_NUM 100


 // Set the channel for the adc device driver //

#define Channel_select _IOR(MAJOR_NUM, 1, int *)

 // For the selection of alignment in register for the adc device driver //

#define alignment_select _IOR(MAJOR_NUM, 2, int *)

#define DEVICE_FILE_NAME "/dev/adc-dev"

#endif
