Implementation of IIO device driver using I2C for bmp280 temparature and pressure sensor.

![image](https://user-images.githubusercontent.com/99579261/166174919-1430ab2c-d251-4a8d-bfc6-86a925341080.jpeg)

We have used Raspberry pi 4b to implement this project \n
Makefile of the device kernel module was executed, creation of object files. \n
"sudo modprobe industrialio" was executed. \n
Insertion of module is done "sudo insmod bmp280.ko". \n
module inserted in "lsmod".
I2C slave address is registered by "i2cdetect -y 1"
Device isnt registered. 
