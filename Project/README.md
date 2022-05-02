**Implementation of device driver using IIO subsytem, for I2C protocol, for bmp280 sensor module (temparature and pressure sensor)** <br />
**Instructor In-Charge: Dr. Devesh Samaiya** <br />
done by --> <br />
Rangu Suhas Rahul - 2021H1400162P <br />
Vemparala sai kumar - 2021H1400155P <br />

**Summary** <br />
->We have used Raspberry pi 4b to implement this project. <br />
->The remaining hardware components are breadboard, jumper wires and the 15.3 Watt Type-C power charger. <br />
->Connected Vdd of the sensor to 3.3V of Rpi, gnd to gnd, SDA(in) of rpi to SDA(out) of bmp280 module , SCA(out) of rpi to SCK(in) of bmp280 module. <br />

**Hardware Design**
![image](https://user-images.githubusercontent.com/99579261/166183208-8ec6d6e3-a161-4983-8db1-071ee8fcca79.png)
![image](https://user-images.githubusercontent.com/99579261/166183234-c0598b6f-bed9-41a5-906d-f60fd740cb6e.png)


**Kernel Space Driver and it’s build process**
1. Makefile of the device kernel module was executed, creation of object files. <br />
![image](https://user-images.githubusercontent.com/99579261/166183256-cbab5181-740f-417b-974a-b927ffa0f978.png)
2. "sudo modprobe industrialio" was executed. <br />
3. Insertion of module is done "sudo insmod bmp280.ko". <br />
4. module inserted in "lsmod". <br />
![image](https://user-images.githubusercontent.com/99579261/166183296-af8fcf32-1ac7-46a1-982e-c1ff0b80b344.png)
5. "dmesg" was executed to check if the device is registered. <br />
![image](https://user-images.githubusercontent.com/99579261/166183316-7f7a4b99-567e-4455-a4b8-621b119c2e69.png)
6. I2C slave address is registered by "i2cdetect -y 1". <br />
![image](https://user-images.githubusercontent.com/99579261/166183344-f50e28b0-6a39-4d5b-b4c5-b9a1d6f5bafe.png)
7. We tried to get data from the sensor but the file isn't created in the \sys\bus\iio\ directory. <br />
8. Hence Device isn't registered. <br />

