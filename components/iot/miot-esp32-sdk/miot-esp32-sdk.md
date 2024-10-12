## WIFI SDK

> [wifi sdk 开发 文档](https://iot.mi.com/v2/new/doc/embedded-dev/sdk-dev/quickstart)

### 1.获取SDK

> SDK使用乐鑫 SDK 版本为v4.0.3，需要 Python2.7，在Ubuntu18.04环境下开发

### 2.配置环境

```sh
在 miot-esp32-sdk/debug 目录下，用printenv |grep "PATH"
# 1.检查是否有 IDF_PATH=$your_path/miot-esp32-sdk/debug/esp-idf
# IDF 设置：在 miot-esp32-sdk/debug 目录下，用source path_config.sh 设置生效 SDK path
source path_config.sh

# 2.检查是否有 PATH=$your_path/esp/xtensa-esp32-elf/bin
# Toolchain 设置：在 home 目录下用 vim .profile 编辑加入 export PATH="$your_path/esp/xtensa-esp32-elf/bin:$PATH" 并执行 source .profile
source ~/.profile

# 3.检查依赖 sudo apt-get install git wget flex bison gperf python python-pip python-setuptools python-serial python-click python-cryptography python-future python-pyparsing python-pyelftools cmake ninja-build ccache

# 4.乐鑫 SDK 是否打上小米 Patch: $your_path/miot-esp32-sdk/debug/esp-idf-patch

# 5.idf工具添加至 PATH 环境变量
alias get_idf='. $HOME/esp32/miot-esp32-sdk/debug/esp-idf/export.sh'
```

### 3.编译下载

```sh
cd MIoT-ESP32-SDK/debug/miio_project/
./gen_default.sh                     # 全编译
make flash                           # python 直接烧录，注意加载串口和进入 boot 模式

make menuconfig #- Configure IDF project
make defconfig #- Set defaults for all new configuration options
make all #- Build app, bootloader, partition table
make flash #- Flash app, bootloader, partition table to a chip
make clean #- Remove all build output
make size #- Display the static memory footprint of the app
make size-components, size-files #- Finer-grained memory footprints
make size-symbols #- Per symbol memory footprint. Requires COMPONENT=<component>
make erase_flash #- Erase entire flash contents
make erase_otadata #- Erase ota_data partition; First bootable partition (factory or OTAx) will be used on next boot." This assumes this project's partition table is the one flashed on the device.
make monitor #- Run idf_monitor tool to monitor serial output from app
make simple_monitor #- Monitor serial output on terminal console
make list-components #- List all components in the project
make app #- Build just the app
make app-flash #- Flash just the app
make app-clean #- Clean just the app
make print_flash_cmd #- Print the arguments for esptool when flash
make check_python_dependencies #- Check that the required python packages are installed
make bootloader', 'make bootloader-flash', 'make bootloader-clean
make partition_table #
```

构建产物

```sh
.
└── hetmod.light.demo22-2
    └── bins
        ├── bootloader.bin
        ├── iflash_hetmod.light.demo22-2_4MB.bin
        ├── phy_init_data.bin
        ├── upd_hetmod.light.demo22-2.bin
        ├── upd_hetmod.light.demo22-2.elf
        ├── upd_hetmod.light.demo22-2.map
        └── xiaomi_partitions_4M.bin
```









### Q&A

#### 1.配置合适的软件源

#### 2.make menuconfig 报错

```sh
vector@vector-pc:~/esp32/miot-esp32-sdk/debug/miio_project$ make menuconfig
Python requirements from /home/vector/esp32/miot-esp32-sdk/debug/esp-idf/requirements.txt are satisfied.
make[1]: 进入目录“/home/vector/esp32/miot-esp32-sdk/debug/esp-idf/tools/kconfig”
cc -c  -DCURSES_LOC="<curses.h>" -DLOCALE -MMD -MP -I "." -I "/home/vector/esp32/miot-esp32-sdk/debug/esp-idf/tools/kconfig"  /home/vector/esp32/miot-esp32-sdk/debug/esp-idf/tools/kconfig/mconf.c -o mconf.o
<command-line>:0:12: fatal error: curses.h: 没有那个文件或目录
compilation terminated.
Makefile:173: recipe for target 'mconf.o' failed
make[1]: *** [mconf.o] Error 1
make[1]: 离开目录“/home/vector/esp32/miot-esp32-sdk/debug/esp-idf/tools/kconfig”
make: *** 没有规则可制作目标“/home/vector/esp32/miot-esp32-sdk/debug/esp-idf/tools/kconfig/conf-idf”，由“/home/vector/esp32/miot-esp32-sdk/debug/esp-idf/tools/kconfig/mconf-idf” 需求。 停止。
```

这个错误是由于系统缺少 `libncurses` 库的开发包。`curses.h` 是 `ncurses` 库的一部分，而 `make menuconfig` 需要这个库来提供终端界面的支持。

你可以通过以下命令安装 `libncurses` 开发包：

```sh
sudo apt-get install libncurses5-dev libncursesw5-dev
```

#### 3.make flash  Permission denied

```
vector@vector-pc:~/esp32/miot-esp32-sdk/debug/miio_project$ make flash
Toolchain path: /home/vector/.espressif/tools/xtensa-esp32-elf/esp-2020r3-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc
Toolchain version: esp-2020r3
Compiler version: 8.4.0
Python requirements from /home/vector/esp32/miot-esp32-sdk/debug/esp-idf/requirements.txt are satisfied.
esptool.py v2.9-dev
Building partitions from /home/vector/esp32/miot-esp32-sdk/debug/miio_project/xiaomi_partitions_4M.csv...

App "miio_app" version: release/2.0.5-22-g0488bc1-dirty
LD build/miio_app.elf
esptool.py v2.9-dev
BIN phy_init_data.bin
Flashing binaries to serial port /dev/ttyUSB0 (app at offset 0x10000)...
esptool.py v2.9-dev
Serial port /dev/ttyUSB0
Traceback (most recent call last):
  File "/home/vector/esp32/miot-esp32-sdk/debug/esp-idf/components/esptool_py/esptool/esptool.py", line 3470, in <module>
    _main()
  File "/home/vector/esp32/miot-esp32-sdk/debug/esp-idf/components/esptool_py/esptool/esptool.py", line 3463, in _main
    main()
  File "/home/vector/esp32/miot-esp32-sdk/debug/esp-idf/components/esptool_py/esptool/esptool.py", line 3127, in main
    esp = chip_class(each_port, initial_baud, args.trace)
  File "/home/vector/esp32/miot-esp32-sdk/debug/esp-idf/components/esptool_py/esptool/esptool.py", line 268, in __init__
    self._port = serial.serial_for_url(port)
  File "/usr/lib/python2.7/dist-packages/serial/__init__.py", line 88, in serial_for_url
    instance.open()
  File "/usr/lib/python2.7/dist-packages/serial/serialposix.py", line 268, in open
    raise SerialException(msg.errno, "could not open port {}: {}".format(self._port, msg))
serial.serialutil.SerialException: [Errno 13] could not open port /dev/ttyUSB0: [Errno 13] Permission denied: '/dev/ttyUSB0'
/home/vector/esp32/miot-esp32-sdk/debug/esp-idf/components/esptool_py/Makefile.projbuild:88: recipe for target 'flash' failed
make: *** [flash] Error 1
```

1. 设置USB与虚拟机连接
2. 添加权限

```
sudo chmod 777 /dev/ttyUSB0
```

#### 4.固定ip

**打开网络配置文件：**

在 Ubuntu 18.04 中，网络配置文件通常位于 `/etc/netplan/` 目录下。你可以使用以下命令来查看和编辑该文件：

```sh
sudo vim /etc/netplan/01-netcfg.yaml
```

**编辑配置文件：**

配置文件的内容可能类似如下（根据实际情况，文件名可能有所不同）：

```yaml
# Let NetworkManager manage all devices on this system
network:
  version: 2
  renderer: NetworkManager
  ethernets:
          ens33:
                  gateway4: 192.168.136.2
                  addresses: [192.168.136.132/24]
                  dhcp4: no
                  optional: true
                  nameservers:
                          addresses: [8.8.8.8,8.8.4.4]
                          search: []

```

请根据以下几点编辑文件：

- **`ethernets:`** 下面的 `ens33` 是你的网络接口名称。可以通过命令 `ip a` 来确认实际的网络接口名称。
- **`addresses:`** 设置你想要的静态 IP 地址，例如 `192.168.136.132/24`，其中 `/24` 表示子网掩码 255.255.255.0。
- **`gateway4:`** 指定默认网关的 IP 地址，例如 `192.168.136.2`。
- **`nameservers:`** 设置 DNS 服务器地址，如 `8.8.8.8`（Google 的公共 DNS 服务器）。

**应用配置：**

保存文件后，运行以下命令以应用配置：

```sh
sudo netplan apply
```