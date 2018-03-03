# Scripts

## Startup scripts

The `dominus` file must be placed as is in the `/etc/init.d` directory.  
The `dominus.sh` file must be completed with the absolute path of the root of the Dominus folder and then placed into the `/etc/profile.d` directory.

The following command must be executed in a shell:

		sudo update-rc.d dominus defaults 80

Then reboot the system, the server is operational!


## Domoticz scripts

The scripts `switch_on.sh` and `switch_off.sh` must be bind with a virtual switch from Domoticz. Therefore they must be placed into the `Domoticz/scripts` directory.  
The IP addresses may be changed according to the host of the Dominus server. In this case, it's required to place the `dominus.sh` file in the `/etc/profile.d` directory on the client as well.
