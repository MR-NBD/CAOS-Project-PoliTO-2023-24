# HaclOSsim Project group 4

## Alberto Ameglio, Giovanni Luca Di Bella, Enrico Di Stasio, Giuseppe Salvemini, Cosimo Vergari

This repository contains:

-  FreeRTOS Demo (CORTEX-MPS2_QEMU_IAR_GCC) with dependencies
-  Short report (report_group4.tex, report_group4.pdf)
-  Powerpoint presentation (presentation_group4.pdf, presentation_group4.pptx)
-  Code implementations of the following scheduling algorithms:
  	- General Purpose:
		- First Come First Served [FreeRTOS/Demo/CORTEX-MPS2_QEMU_IAR_GCC/main_fcfs.c]
   		- Shortest Job First [FreeRTOS/Demo/CORTEX-MPS2_QEMU_IAR_GCC/main_sjf.c]
		- Round Robin [FreeRTOS/Demo/CORTEX-MPS2_QEMU_IAR_GCC/main_rr.c]
	- Real Time:
   		- Timeline Scheduling [FreeRTOS/Demo/CORTEX-MPS2_QEMU_IAR_GCC/main_timelinescheduling.c]
		- Rate Monotonic [FreeRTOS/Demo/CORTEX-MPS2_QEMU_IAR_GCC/main_RM.c]


## Abstract

This project illustrates the main features of FreeRTOS, its implementation with QEMU, and various usage experiments aimed at deepening the main contents presented during the course. This project is based on embedded systems, which are now ubiquitous in modern technology, requiring specialized operating systems due to resource constraints and real-time requirements. For our project, we chose FreeRTOS, a lightweight, open-source real-time operating system with the Demo "CORTEX-MPS2" a multicore processor designed for high-performance embedded systems and compiled with gcc. We will present the characteristics of this OS, an example tutorial on how to simulate an Arm architecture with QEMU, and explanations of the topics addressed above and explored in depth by our group.

# What is QEMU and why would we want to debug with it?
- Reduced development costs as physical hardware is not required.
- Increased testing flexibility, allowing the execution of multiple scenarios.
- Early debugging and problem identification.
- Safe experimentation without the risks associated with hardware manipulation.

# What we need to get started?
- [FreeRTSO](https://www.freertos.org/index.html) 
- QEMU
- Arm GNU Toolchain
- CMake
- Make

## Steps to quickly install

Our base of support for the entire tutorial will be an Ubuntu 22.04.3 LTS operating system on Windows 10 x86_64

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

This is a Guide for QEMU Emulation that work with another architecture 
[QEMU on FreeRTOS](https://mcturra2000.wordpress.com/2019/11/16/freertos-on-qemu/)

Run this command in the folder ...FreeRTOS/FreeRTOS/Demo/CORTEX_MPS2_QEMU_IAR_GCC to run QEMU with FreeRTOS

```shell
qemu-system-arm -machine mps2-an385 -cpu cortex-m3 -kernel build/gcc/output/RTOSDemo.out -serial stdio -s -S

```

# Kosimo-patch

STEPS AFTER INSTALLING WSL/UBUNTU

install all the dipendencies:

before all: "sudo apt update"
then:
- QEMU :   
    ```shell
    sudo apt install qemu-system-arm
    ```
- Python3.8 : 
    ```shell
    sudo add-apt-repository ppa:deadsnakes/ppa
    ```
    ```shell
    sudo apt install python3.8
    ```
- ARM toolchain(gcc-arm-none-eabi)(following guide of "https://lindevs.com/install-arm-gnu-toolchain-on-ubuntu") : 
    ```shell
    ARM_TOOLCHAIN_VERSION=$(curl -s https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads | grep -Po '<h4>Version \K.+(?=</h4>)')
    ```
    ```shell
    curl -Lo gcc-arm-none-eabi.tar.xz "https://developer.arm.com/-/media/Files/downloads/gnu/${ARM_TOOLCHAIN_VERSION}/binrel/arm-gnu-toolchain-${ARM_TOOLCHAIN_VERSION}-x86_64-arm-none-eabi.tar.xz"
    ```
    ```shell
    sudo tar xf gcc-arm-none-eabi.tar.xz --strip-components=1 -C /opt/gcc-arm-none-eabi"
    ```
    ```shell
    echo 'export PATH=$PATH:/opt/gcc-arm-none-eabi/bin' | sudo tee -a /etc/profile.d/gcc-arm-none-eabi.sh"
    ```
    (adding the gcc to PATH)
    ```shell
    source /etc/profile
    ```
    (to refresh config)
    ```shell
    sudo apt install -y libncursesw5
    ```
- CMAKE (following guide of https://vitux.com/how-to-install-cmake-on-ubuntu/): 
    ```shell
    sudo apt-get install build-essential libssl-dev
    ```
    ```shell
    cd /tmp
    ```
    ```shell
    wget https://github.com/Kitware/CMake/releases/download/v3.20.0/cmake-3.20.0.tar.gz
    ```
    ```shell
    tar -zxvf cmake-3.20.0.tar.gz
    ```
    ```shell
    cd cmake-3.20.0
    ```
    ```shell
    ./bootstrap
    ```
    ```shell
    make
    ```
    ```shell
    sudo make install
    ```



---

- downloaded "https://sourceforge.net/projects/freertos/files/latest/download?source=files"

- extracted the FreeRTOS Folder

- deleted all Demos exept the one we choose ("CORTEX_MPS2_QEMU_IAR_GCC") and the "Common" folder which conteins essential files for building the project

- built the Demo gcc project with the command "make" in the FreeRTOS/Demo/CORTEX_MPS2_QEMU_IAR_GCC/build/gcc/

- added file "{DemoPath}/.vscode/c_cpp_proprieties.json":

```code
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**",
                "${workspaceFolder}/../../**"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c17",
            "cppStandard": "gnu++17",
            "intelliSenseMode": "linux-gcc-x64"
        }
    ],
    "version": 4
}
```
	
- modified "{DemoPath}/.vscode/launch.json" : uptade miDebuggerPath to the right one (my case is "/opt/gcc-arm-none-eabi/bin/arm-none-eabi-gdb")

- (install plugin vscode C/C++ Extextion and VSL extenction)
(VSL)
