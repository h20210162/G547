Implementation of IIO device driver using I2C for bmp280 temparature and pressure sensor.

![image](https://user-images.githubusercontent.com/99579261/166174919-1430ab2c-d251-4a8d-bfc6-86a925341080.jpeg)

We have used Raspberry pi 4b to implement this project. <br />
Connected Vdd of the sensor to 3.3V of Rpi, gnd to gnd, SDA to SDA, SCL to SCL. <br />
1. Makefile of the device kernel module was executed, creation of object files. <br />
2. "sudo modprobe industrialio" was executed. <br />
3. Insertion of module is done "sudo insmod bmp280.ko". <br />
4. module inserted in "lsmod".<br />
6. I2C slave address is registered by "i2cdetect -y 1". <br />
7. We tried to get data from the sensor but the file isn't created in the \sys\bus\iio\ directory. <br />
8. "dmesg" was executed to check if the device is registered.
9. Hence Device isn't registered. <br />
