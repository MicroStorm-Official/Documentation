![Top View](https://github.com/MicroStorm-Official/Resources/blob/main/PCB-View-Top-Drawing.png?raw=true)

# Microstorm Prototype V2

Microstorm Prototype V2 is the second version of the orginial Microstorm Prototype. With this version some more features are embedded on to the board.


# Specifications


| | Features| Specifications
|--|--|--|
|**Connectivity**| WiFi| 802.11 b/g/n/d/e/i/k/r (802.11n up to 150 Mbps)
||Bluetooth|Bluetooth v4.2 BR/EDR and BLE specification
||I2C|Accessable from 3 expansion headers
|**Sensors**|3-axis MEMS accelerometer|Acceleration Range: ± 2g, ± 4g, ± 8g, ± 16g (NOT WORKING)
||3-axis MEMS gyroscope|Gyroscope Range: ± 250°/s, ± 500°/s, ± 1000°/s, ± 2000°/s (NOT WORKING)
|**Lighting**|2x Neopixels|Individual Addressable LED's (WS2812b)
|**Actuators**|Dual Motor Connectors|Compatible with Lego Mindstorms EV3/NXT (Including their encoders)



## Pinout
![Top View](https://github.com/MicroStorm-Official/Resources/blob/main/Pinout.png?raw=true)

| Number | 1 | 2 | 3 | 4 | 5 | 6 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16
|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|
| **Description** | +3.3V | VCC (Battery) | GND | +5V | SCL | SDA | RXD | TXD | TXD2 | RXD2 | GPIO14 | GPIO5 | GPIO18 | GPIO15 | GPIO23 | GPIO19 |


## Known issues
The following issues are known with Prototype V2

 - Voltage monitoring not working
 - Expension -> Expansion
 - MPU6050 Not working (Probably something with the wiring), use external module instead
## FAQ
### Arduino IDE keeps trying to connect to board
> `Connecting........________........________........`
>
> This is default behaviour of the ESP32 Chip. *GPIO 0* should be pulled low to accept connection. On the board a *latch circuit* is used to do this automatically. In some cases it doesn't respond. To fix this, hold the BOOT button when uploading your code.

### Can't connect to build-in IMU (MPU6050)

> This is a kown issue with this version of the board, please use an external module instead via the I2C Expansion connectors.
