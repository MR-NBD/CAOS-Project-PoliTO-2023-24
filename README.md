# CAOS-Project-PoliTO-2023-24
This is a Computer architectures and operating systems Project for FreeRTOS Demo with QEMU emulator

# What is QEMU and why would we want to debug with it?
QEMU is a machine emulator that allows you to virtualize hardware types, even across different architectures.
 You can run applications against hardware target that you may not have immediate access to. This might be because:
 - You are still in the process of selecting a chipset for an embedded product design 
 - Your boards are somewhere else like a lab
 - ==You want to run automated tests without physical hardware== seems our case
 - The real hardware is simply in short supply

# What we need to get started?
- [FreeRTSO](https://pmvanker.blogspot.com/2020/05/freertos-with-ubuntu.html)
- VSCode 
- QEMU
- Arm GNU Toolchain
- CMake
- Git
- Make
- Add QEMU, Arm GNU Compiler, CMake, and Make installation paths to your environment variable 

[FreeRTOS debugger-tutoria](https://www.youtube.com/watch?v=l2GmlDN_SPo)
[FreeRTOS QEMU](https://www.freertos.org/install-and-start-qemu-emulator/)

## This comand allow to install QEMU with ARM architecture
```shell
sudo apt install qemu-system-arm
```
Before install toolchain check python3 version. You need 3.8 version. In case you need to unistanstall Python3 use
```shell
sudo apt-get remove python3."the current version"
```
For add Python3.8 use this command:
```shell
sudo apt update
sudo apt install software-properties-common
```
```shell
sudo add-apt-repository ppa:deadsnakes/ppa
```
press[ENTER]
```shell
sudo apt install python3.8
```
```shell
python3.8 --version
```

[Guida per intallare Arm GNU toolchain on Ubuntu ](https://lindevs.com/install-arm-gnu-toolchain-on-ubuntu)

[Guida per intsllare CMAKE](https://vitux.com/how-to-install-cmake-on-ubuntu/)

Ciao sono un coglione

