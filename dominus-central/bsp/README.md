# dominus

## Préparation de l'image RPI4

```` console
$ sh build.sh
````

Le conteneur créé est accessible via:

```` console
$ docker exec -it --user=root dominus-bsp bash
````

## Inspection de l'image

```` console
$ ./scripts/mount-boot
$ ls ./mnt
````

## Flash

Flash de l'image sur la carte SD `/dev/sd<X>`:

```` console
$ dd if=dominus.sdimg of=/dev/sd<X>
````

## Connexion SSH

Sur la machine hôte:

```` console
$ ip address add 192.168.33.3/24 broadcast + dev <interface>
$ ip link set dev <interface> up
$ ssh root@192.168.33.2
````
