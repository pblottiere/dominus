V4 : We have decided to create a client/server in a different architecture than the proposed one. So the domoticz server is hosted on the board which contains the client and the server is on the board hosting the LED/Relay.

The relay is plugged in the following way :

The power pin is on the 5V of the Raspberry Pi or on the 220V (depending of the intensity required to activate it and of the maximum voltage of this guy). There must be a common ground between the board and the relay. The LED is plugged with its + pin on the output of the relay (NO), and the minus pin on the - pin of the power supply.
 The power supply goes to the input of the relay (COM4).
The raspberry has a ground going to the relay and the GPIO 17, going to the signal input of the relay (CH4).

If you want to use the binaries on another Raspberry, you need to know that the files 'client' and 'server' have to be on the user's folders, and  this is the same with the associated files 'server.conf' and 'client.conf'. If you use the same raspberry to test it, you won't have to change anything. If you want to use 2 separates raspberry, you will need to change the ip of the server which is the first line of the 'client.conf' file. The second one of the client.conf file is the socket used. The servers has only one argument inside its config file, which is the socket used.
Moreover, the client must have the two scripts ('switch0_on.sh' and 'switch0_off.sh') included in the 'scripts' folder of the 'dominus' repository in '/opt/domoticz/scripts/' of the client. To finish, all the binaries ('client' and 'server') have to be launched in sudo (root user) mode.


V5 : les scripts à mettre dans /opt/domoticz/scripts sont dans les répertoires src/domoticz/scripts du dépot dominus.
Pour que le tout marche, il faut faire (en utilisateur normal) : echo "light_off" > /tmp/light.dat sur la raspberry.
Puis lancer le client et le serveur. Je n'ai pas réussi à lancer avec init.d .

François Cebron / Philipe Miranda de moura / Mohamad Mezher
