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
    tar -zxvf cmake-3.20.0.tar.gz"; "cd cmake-3.20.0
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
	
- modified "{DemoPath}/.vscode/launch.json" : uptade miDebuggerPath to the right one (my case is "/opt/gcc-arm-none-eabi/bin/arm-none-eabi-gdb")

- (install plugin vscode C/C++ Extextion and VSL extenction)
(VSL)
