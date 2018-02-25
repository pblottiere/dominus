# Dominus Lib

## GPIO Switch

This is the library that permit to control the GPIO switch for Dominus.
It checks if the GPIO pin is initialized in `/sys/class/gpio` and then set its direction (always out here) and value (0 or 1).
