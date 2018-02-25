# DOMINUS - Src domoticz


## create_sensor.c

This code is designed to allow users to easily add sensors to a remote domoticz server.
Use it as follows:

    $ ./create_sensor IP Port Sensor_type Sensor_name ID_Sensor

With:

    IP          -> Computer's IP
    Port        -> Port used by Domoticz (generally 8080)
    Sensor_type -> Choose in the following list:
                        1   -> Pressure (Bar)
                        2   -> Percentage
                        80  -> Temperature
                        81  -> Humidity
                        82  -> Temperature & Humidity 
                        84  -> Temperature & Humidity & Barometer
                        85  -> Rain
                        86  -> Wind
                        87  -> UV
                        113 -> RFXMeter
                        90  -> Energy
                        249 -> TypeAirQuality
    Sensor_name -> The name your sensor will have in Domoticz
    ID_Sensor   -> The ID your sensor will have in Domoticz



