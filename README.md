[![Build Status](https://secure.travis-ci.org/pblottiere/dominus.png)]
(http://travis-ci.org/pblottiere/dominus)


# DOMINUS

Dominus is a **low cost home automation system** providing:

- **Autotools** to build the application
- a **Dockerfile** to build the RPI3 BSP and cross-compile the application
- a support for **various sensors**
- a logger based on **syslog** to have a remote access to the current status
- an interface to interact with **Domoticz**
- an **Ansible playbook** to remotely deploy Dominus on boards
- an easy way to build your own automation system **without a single line of code!**

But watch out, Dominus will become the master of your own house!


## Getting the project

To clone the project from github:

```shell
$ git clone https://github.com/pblottiere/dominus
```

## BSP

A Dockerfile is provided to build the BSP for the RPI3 as well as a *docker.sh*
script allowing to simplify the workflow:

```shell
$ cd dominus/docker/rpi3
$ ./docker.sh
Usage: docker.sh [OPTIONS]:

Options:

  img                 Copy the sdcard image from the container to the host
  build               Build the BSP in a Docker image
  clean               Remove the underlying Docker image
  connect             Create an interactive bash within a Docker container
  configure           Run the configure script using the cross-compiler
  install             Install cross-compiled application in a sub-directory
  maintainer-clean    Clean generated files
  make                Cross-compile the application
  qemu                Run QEMU with the built in RFS
```

To compile the BSP for the RPI3 board:

```shell
$ ./docker.sh build
```

Then you can retrieve the BSP and flash your sdcard with the image:

```shell
$ ./docker.sh img
Image: sdcard.img
$ dd if=sdcard.img of=/dev/sdX
```

Now, you may boot your board and establish an ssh connection:

```shell
$ ssh dominus@<BOARD_IP> # password: dominus1*
```

Moreover, Domoticz should be available through your web-browser on
`http://<BOARD_IP>:8080`.

## Cross-compilation

To compile Dominus libraries and binaries with the native compiler of your host
machine:

``` shell
$ ./autogen.sh
$ ./configure --prefix=$PWD/install
$ make
$ make install
```

If you want to use a cross-compiler, you have to use the *--host* option. For
example with the *arm-linux-gcc* compiler:

``` shell
$ ./autogen.#!/bin/sh
$ ./configure --prefix=$PWD/install --host=arm-linux
$ make
```

If you're using the BSP embedded in the Docker image, you can directly
cross-compile the application thanks to the *docker.sh* script:

```shell
$ cd docker/rpi3
$ ./docker.sh configure
$ ./docker make
$ ./docker install
$ file ../../install/bin/dominus-server
ELF 32-bit LSB executable, ARM, EABI5 version 1 (SYSV), dynamically linked,
interpreter /lib/ld-uClibc.so.0, not stripped
```


## Deployment

Once the application is cross-compiled and the board is online, we can use
an Ansible playbook to deploy Dominus on the board. But a ssh connection is
needed for the *root* user.

So, you have to update the *sshd* configuration file `/etc/ssh/sshd_config`
directly on the board:

```shell
PermitRootLogin yes #prohibit-password
```

Then you should update the `~/.ssh/config` file on the host machine:

```shell
Host dominus
    Hostname <BOARD_IP>
    User root
```

Finally, you're able to remotely deploy Dominus on the board:

```shell
$ cd Ansible
$ ./deploy.sh
Copy libs ------------------------------------------------------------------------------ 2.66s
Copy init.d script --------------------------------------------------------------------- 0.51s
Update ldconfig for dominus libs ------------------------------------------------------- 0.49s
Copy client ---------------------------------------------------------------------------- 0.46s
Copy server ---------------------------------------------------------------------------- 0.45s
Creates lib subdirectory --------------------------------------------------------------- 0.40s
Copy syslog configuration file --------------------------------------------------------- 0.38s
Copy configuration file ---------------------------------------------------------------- 0.33s
Copy syslogd options file -------------------------------------------------------------- 0.33s
Creates default directory -------------------------------------------------------------- 0.33s
Copy profile file ---------------------------------------------------------------------- 0.32s
```

Then you just have to reboot your board and Dominus is operational! And do not
forget to reset the ssh access for the *root* user.

## Configuration

### Dominus

TODO

### Device Tree Blob

TODO
