# Relay Trigger on RPi 3 for Embedded system and Domoticz
This is for the Embedded system course at ENSTA Bretagne.

## Version 2

Basic script to trigger on or off a GPIO (GPIO17)

### To compile:

```
  sudo make v2
```
It will create two binaries : gpion and gpioff.

### To use :

You can chose the pin you want to trigger:

```
  ./gpion -g 17 // if you want to trigger on the GPIO 17
  ./gpioff -g 17 // if you want to trigger off the GPIO 17
```

### And with Bash :

the *onoff.sh* script is an exemple of use with bash to make it work with Domoticz.

## Version 4:

### To compile:

```
  sudo make
```
it will create two binaries : server and client

### To use :

```
sudo ./build/server -g 17
```
Will launch the server for the GPIO17

```
  sudo ./build/client -i "127.0.0.1" -m "allumer"
  sudo ./build/client -i "127.0.O.1" -m "eteindre"
  sudo ./build/client -i "127.0.0.1" -m "off"
```

triggers on or off the GPIO, and shut down the server.

## Version 5:
Added init.d
## Authors :

* **Hussam Al Hertani** - *Initial GPIO Class* - [halherta](https://github.com/halherta)
* **Raphael Abellan--Romita** - *server and documentation* - [SelenKelan](https://github.com/SelenKelan)
* **William Blachère** - *Command Prompt* - [wblachere](https://github.com/wblachere)



