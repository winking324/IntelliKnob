# IntelliKnob

如何做一个有“意义”的智能旋钮呢？

## 1 原型

参考 [SmartKnob](https://github.com/scottbez1/smartknob) 可以做出一个非常炫酷的旋钮。

### 1.1 无刷电机

第一步需要先搞定电机，由于 SmartKnob 里面用到的电机已经停产，几乎已经买不到，所以换电机影响就非常大了，例如说后续各种尺寸全都要更改。

详情可以参考[替换的方案](https://github.com/scottbez1/smartknob/wiki/Motor-Status)。

### 1.2 PCB 打样与 SMT 贴片

PCB 打样和 SMT 贴片都是在[嘉立创](https://www.jlc.com/)完成，当然有能力并且设备齐全的，可以只在嘉立创进行 PCB 打样就好了，几乎只出邮费的钱就可以了。

* PCB 打样，需要使用 Gerber 文件，分两部分：      

  - Base，目前最新是 [v0.4](https://github.com/scottbez1/smartknob/releases/tag/releases%2Fview_base%2Fv0.4)

  - View，目前最新是 [v0.2](https://github.com/scottbez1/smartknob/releases/tag/releases%2Fview_screen%2Fv0.2)

* SMT 贴片，需要使用 BOM 和 BOM 坐标文件，大部分芯片嘉立创商城可以直接选购，部分缺货或者没有的可以从淘宝购买后邮寄：
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
  3. View 板连接到 Base 板的连接线，线材要求非常细，需要从电机中心的小孔中穿过，可以用漆包线或者 30 AWG 的 OK 线，也可以用 8 芯的耳机线更方便；
  4. 应变片 BF350-3AA（每块板子需要 4 片）；
  5. 螺丝、螺母以及垫圈，需要以下几种类型：
     * 平头 m1.6x9（m1.6x9 不好买可以用 m1.6x10 加 1mm 垫圈）：用于固定 PCB，电机座（MountBase）和电机；
     * 沉头 m1.6x3：用于固定旋转模块（RotorSpacer）到电机上；
     * 盘头 m2x5 + 螺母：用于固定 PCB 到底座上；
  6. 透明胶带、502；
* 有更好：
  1. 玻璃盖板，直径 39.5mm，厚 1mm；
  2. 3M 无痕双面胶，厚 2mm（用于固定 LCD 屏幕到 View 板上，不然有可能旋钮旋转过程中会碰到屏幕）；
  3. 电机端子 1.25mm 3P（电机默认有端子，看情况可以不需要）；

### 1.5 制作过程

制作主要分为几大步：

1. 将应变片 BF350-3AA 粘贴到 Base 板上，并焊接，可以参考[应变片安装教程](https://www.bilibili.com/video/BV1b64y1S7At)（先压平，贴上胶带，然后粘在对应位置上，掀开一边，滴上 502，再次压平，完全干了以后撕掉胶带）；
2. 将旋转模块（RotorSpacer）固定到电机上；
3. 将 8 根 OK 线焊接到 View 板上（注意不要焊接到屏幕的那一侧，应该是焊接到电机的那一侧）；
4. 组装 Base 板、电机座（MountBase）、电机、屏幕底座（ScreenPlatform）、屏幕，并将 8 根 OK 线穿过电机中间的小孔；
5. 使用万用表测量每一根 OK 线，并焊接到 Base 板对应的位置上；
6. 安装 Base 板的底座（BackPlate）；
7. 安装其他外壳（Enclosure 和 Knob）；

### 1.6 刷固件

在 VSCode 中安装 PlatformIO 插件，然后将 SmartKnob 连接到电脑上，编译并上传即可（第一次编译会比较慢）。

### 1.7 问题和解决

1. 出现旋转按钮时异常旋转和定位不准确的问题？

   校准：编译并上传后，在监控中启动时按 shift + Y，将校准后的值填写到 `motor_task.cpp` 中的 `zero_electric_offset` 处；

2. 切换时崩溃？

   在 `interface_task.cpp` 中将切换时的 `motor_task_.playHaptic(true);` 移除即可临时解决，实际原因待调查；

3. `On/off Strong detent` 到中间时崩溃？

   怀疑跟切换时崩溃是相同问题，先在 `interface_task.cpp` 中移除了 `On/off Strong detent` 这个模式，实际原因待调查；

## 2 智能

