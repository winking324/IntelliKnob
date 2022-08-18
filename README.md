# IntelliKnob

如何做一个有“意义”的智能旋钮呢？至少也要能连接电脑或者其他设备（例如说家居），提供一定的智能化功能，才能称得上“智能”，所以只是复刻一个 SmartKnob 只能玩几天，那就失去了它的价值。

所以本项目在 SmartKnob 的硬件和固件的基础上，去实现一些有意义有价值的功能，让这个旋钮更加的智能化。

Please use Google Translate for this document if necessary. <img src="Resources/doge.png" alt="cplusplus" height="30"/>

## 1 原型

参考 [SmartKnob](https://github.com/scottbez1/smartknob) 可以做出一个非常炫酷的旋钮。

### 1.1 无刷电机

第一步需要先搞定电机，由于 SmartKnob 里面用到的电机已经停产，几乎已经买不到，所以换电机影响就非常大了，例如说后续各种尺寸全都要更改。

详情可以参考 [替换的方案](https://github.com/scottbez1/smartknob/wiki/Motor-Status)。

### 1.2 PCB 打样与 SMT 贴片

PCB 打样和 SMT 贴片都是在 [嘉立创](https://www.jlc.com/) 完成，当然有能力并且设备齐全的，可以只在嘉立创进行 PCB 打样就好了，几乎只出邮费的钱就可以了。

* PCB 打样，需要使用 Gerber 文件，分两部分：      

  - ViewBase，目前最新是 [v0.4](https://github.com/scottbez1/smartknob/releases/tag/releases%2Fview_base%2Fv0.4)

  - ViewScreen，目前最新是 [v0.2](https://github.com/scottbez1/smartknob/releases/tag/releases%2Fview_screen%2Fv0.2)，**注意厚度为 0.6mm**；

* SMT 贴片，需要使用 BOM 和 [BOM 坐标文件](https://github.com/winking324/IntelliKnobClient/issues/1)，大部分芯片嘉立创商城可以直接选购，部分缺货或者没有的可以从淘宝购买后邮寄：
  * TMC6300：电机驱动芯片
  * SK6812：LED
  * VEML7700：环境光传感器
  * GC9A01：1.28 寸 LCD 屏幕
  * T-Micro32 Plus：主控芯片

**注意：** 应变片 BF350-3AA 不需要贴片，不要邮寄给嘉立创。

### 1.3 外壳打印

3D 外壳打印可以选树脂或者尼龙，尼龙具有更高的热变形温度，但是表面粗糙，价格较贵，树脂则相反，对应的 STL 文件为 [View: Mechanical v185](https://github.com/scottbez1/smartknob/releases/tag/releases%2Fmechanical%2Fv185-dummy-tag)，一共分为 6 个部分。

### 1.4 其他材料

除了上面这些之外，还需要准备一些其他的材料，在收到 PCB 和外壳之后，进行进一步的组装。

* 必需品：
  1. 万用表；
  2. 电烙铁、焊锡膏、焊锡；
  3. ViewScreen 板连接到 ViewBase 板的连接线，线材要求非常细，需要从电机中心的小孔中穿过，可以用漆包线或者 30 AWG 的 OK 线，也可以用 8 芯的耳机线更方便；
  4. 应变片 BF350-3AA（每块板子需要 4 片）；
  5. 螺丝、螺母以及垫圈，需要以下几种类型（其实在 Bom 中有写具体型号，我没有注意询问别人时遭到了鄙视）：
     * 平头 m1.6x9（m1.6x9 不好买可以用 m1.6x10 加 1mm 垫圈）：用于固定 PCB，电机座（MountBase）和电机；
     * 沉头 m1.6x3：用于固定旋转模块（RotorSpacer）到电机上；
     * 盘头 m2x5 + 螺母：用于固定 PCB 到底座上；
  6. 透明胶带、502；
* 有更好：
  1. 玻璃盖板，直径 39.5mm，厚 1mm（其实在 Bom 中有写具体型号，我没有注意询问别人时遭到了鄙视）；
  2. 3M 无痕双面胶，厚 2mm（用于固定 LCD 屏幕到 ViewScreen 板上，不然有可能旋钮旋转过程中会碰到屏幕）；
  3. 电机端子 1.25mm 3P（电机默认有端子，看情况可以不需要）；
  4. 游标卡尺；

### 1.5 制作过程

制作主要分为几大步：

1. 将应变片 BF350-3AA 粘贴到 ViewBase 板上，并焊接，可以参考 [应变片安装教程](https://www.bilibili.com/video/BV1b64y1S7At)（先压平，贴上胶带，然后粘在对应位置上，掀开一边，滴上 502，再次压平，完全干了以后撕掉胶带）；
2. 将旋转模块（RotorSpacer）固定到电机上；
3. 将 8 根 OK 线焊接到 ViewScreen 板上（注意不要焊接到屏幕的那一侧，应该是焊接到电机的那一侧）；
4. 组装 ViewBase 板、电机座（MountBase）、电机、屏幕底座（ScreenPlatform）、屏幕，并将 8 根 OK 线穿过电机中间的小孔；
5. 使用万用表测量每一根 OK 线，并焊接到 Base 板对应的位置上；
6. 安装 ViewBase 板的底座（BackPlate）；
7. 安装其他外壳（Enclosure 和 Knob）；

### 1.6 刷固件

在 VSCode 中安装 PlatformIO 插件，然后将 SmartKnob 连接到电脑上，编译并上传即可（第一次编译会比较慢）。

### 1.7 问题和解决

1. 出现旋转按钮时异常旋转和定位不准确的问题？

   **Status：Resolved**

   校准：编译并上传后，启动时在 VSCode 控制台 Monitor 中按 shift + Y（控制台有提示，提示时要快点按，不然可能错过），将校准后的值填写到 `motor_task.cpp` 中的 `zero_electric_offset` 处，再次重新编译并上传，该问题解决。

2. 切换时崩溃？

   **Status：Resolved**

   ~~在 `interface_task.cpp` 中将切换时的 `motor_task_.playHaptic(true);` 移除即可临时解决，实际原因待调查。~~

   详情可以参考 [Reboot when the switch is toggled(On/Off Strong detent)](https://github.com/scottbez1/smartknob/issues/88)，原因是由于 Mac 的 Type-C 接口输出最大电流是 500mA，导致电机需要更大电流时失败重启，更换到 USB 5V 3.1A 插头上，可以解决该问题；

3. `On/off Strong detent` 到中间时崩溃？

   **Status：Resolved**

   ~~怀疑跟切换时崩溃是相同问题，先在 `interface_task.cpp` 中移除了 `On/off Strong detent` 这个模式，实际原因待调查。~~

   解决方案参考切换时崩溃，是相同问题。

4. 屏幕底座（ScreenPlatform）固定屏幕不稳问题？可能跟 3D 打印的精度有关系？

### 1.8 价格

1. 闲鱼买的电机，100 元/个；
2. 嘉立创 PCB 打样 + SMT 贴片 + 零件（含邮寄），ViewBase 和 ViewScreen 每样 5 份，共 1789.43 元，357.89 元/套；
3. 3D 打印，树脂，26 元/套；
4. 玻璃盖板，2.75 元/片；
5. 螺丝，OK 线，焊锡等这些买的比较多，实际上只用到很少一部分，整体也不贵，就不算价格了；

所以整体上做一套的话，需要 486.64 元左右。

## 2 智能

初步想法是，在 PC 上实现一个软件，重新写一套对应的固件（IntelliKnob），然后通过蓝牙连接到 PC 上，进行一定功能的实现和控制等。

可能不同的项目需要实现不同的功能，或者连接到不同的设备上进行控制，所以实现上尽可能的实现模块化，能够通过配置或者组合调用，实现各自的需要。

一些可能需要用到的模块：

* OTA：不需要一直连到电脑上去更新固件（可以通过 `factory` 固件去自由下载不同固件以实现不同功能？）；
* 蓝牙：和不同设备之间通信实现功能；
* 显示：能够通过设备控制，显示不同的内容（例如目前很多手表支持从手机上控制表盘显示），休眠和唤醒等；
* LED：颜色的控制，以及休眠和唤醒等；

### 2.1 FreeRTOS

ViewBase 板上核心芯片使用的是 [T-Micro32 Plus](http://www.lilygo.cn/prod_view.aspx?TypeId=50063&Id=1091)（8M Flash，2M PSRAM），按照官方说法，其实就是一个 ESP32 芯片（功能完全一样），但是缩小了 45% 的面积，所以可以参考 [ESP32 文档](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/get-started/index.html) 进行开发。

而从 SmartKnob 的固件来看主要是使用的 Arduino 的开发框架，Arduino 和 ESP32 的关系，可以参考 [Arduino和ESP32他们到底是什么关系？](https://www.zhihu.com/question/458853667)

为了实现比较复杂的控制逻辑，使用 Arduino 顺序执行代码就比较捉襟见肘了，所以一般会采用有事件驱动能力的系统来进行支持，所以采用 Arduino + FreeRTOS 来实现，简单的介绍可以参考 [ARDUINO运行FREERTOS操作系统](https://www.freesion.com/article/9729559065/)。

FreeRTOS 的使用可以参考 [API 文档](https://www.freertos.org/a00106.html)。

### 2.2 分区表

这里遇到第一个问题，就是修改 `partitions.csv` 分区表，因为 T-Micro32 Plus 实际上是 8M Flash，而 PlatformIO 中使用的开发板 `esp32dev` 声明的是 4M Flash，所以如果修改 `partitions.csv` 并上传程序到开发板的话，开发板启动会失败报错。

正确的做法是在 `platformio.ini` 文件中增加声明 `board_upload.flash_size = 8MB`，这样再次编译上传程序，可以正常运行，可以参考 [Platform options](https://docs.platformio.org/en/latest/projectconf/section_env_platform.html) 和 [esp32dev.json](https://github.com/platformio/platform-espressif32/blob/develop/boards/esp32dev.json)。

下面为 `partitions.csv` 对应 Flash 分区的示意图，分区表可以参考 [ESP32 文档](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-guides/partition-tables.html)。

![](Resources/partitions.png)

### 2.3 OTA

蓝牙 BLE OTA 参考项目 [ESP32_BLE_OTA_Arduino](https://github.com/fbiego/ESP32_BLE_OTA_Arduino)（还没调通）。

OTA 具体的定义在 [ESP32 文档](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/system/ota.html) 有详细的描述。

### 2.4 SPIFFS

蓝牙 BLE OTA 中用到了 SPIFFS，在 `platform = espressif32@5.1.0` 会启动失败，错误原因 `flash format failed`。经过调查，需要配置 `board_build.flash_mode = qio` 才可以成功。

## 3 Agent

Agent 目前准备用 Qt 来开发，这样其他平台能够比较好的移植。

**注意：**安装 Qt 时，要在 `Additional Libraries` 中勾选 `Qt Connectivity`，否则蓝牙相关的模块不会被添加进来。

![](Resources/install_qt.png)

## 4 其他

### 4.1 CNC

默认使用塑料外壳，放在桌面上不固定的话，旋转旋钮容易晃动，可以考虑使用 CNC 雕刻的铝合金外壳。

STL 转 STP 文件，可以参考 [FreeCAD 中STL格式转化为STP格式](https://www.bilibili.com/video/BV11v411q766/?vd_source=fd5720629e67b12f90593a5a072198bf)，Mac 中需要点视图 -> 工具台 -> part 显示“零件”到菜单栏上。

### 4.2 软件

* KiCad
* FreeCAD
* Autodesk Fusion 360（Mac 版不是一般的难用，不推荐）
* Visual Studio Code + PlatformIO 插件

