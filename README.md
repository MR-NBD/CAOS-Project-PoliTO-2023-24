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
- [FreeRTOS](https://www.freertos.org/index.html) 
- QEMU
- Arm GNU Toolchain
- CMake
- Make

## Steps to quickly install

Our base of support for the entire tutorial will be an Ubuntu 22.04.3 LTS operating system on Windows 10 x86_64.
1. First we need to download QEMU and the arm architecture extension
 ```shell
    sudo apt install qemu-system-arm
 ```
To verify the correct installation
    ```shell
	qemu-system-arm --version
    ```
2. Download FreeRTOS
[FreeRTOS](https://www.freertos.org/index.html)
or
[FreeRTOS github](https://github.com/FreeRTOS/FreeRTOS)

3. Download and install the debugger for Arm, in this case we have selected the Arm GNU toolchain(gcc-arm-none-eabi):

On Linux, the Arm GNU toolchain provides GDB with Python support. Requires version 3.8 to be installed, any other version may return errors.
To install the correct version of Python the commands are:  
    ```shell
    	sudo add-apt-repository ppa:deadsnakes/ppa
    ```
    ```shell
    	sudo apt install python3.8
    ```
then:
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
    ```shell
    	source /etc/profile
    ```
    ```shell
    	sudo apt install -y libncursesw5
    ```
To verify the correct installation
    ```shell
	arm-none-eabi-gcc --version
	arm-none-eabi-g++ --version
    ```

4. download and install compiler make and cmake:
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


Run this command in the folder ...FreeRTOS/FreeRTOS/Demo/CORTEX_MPS2_QEMU_IAR_GCC to run QEMU with FreeRTOS

```shell
qemu-system-arm -machine mps2-an385 -cpu cortex-m3 -kernel build/gcc/output/RTOSDemo.out -serial stdio -s -S

```
