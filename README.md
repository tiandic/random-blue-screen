<!--
 * @encode: utf-8
 * @Date: 2025-07-27 21:54:04
 * @LastEditTime: 2025-08-18 16:30:22
 * @FilePath: /random blue screen/README.md
-->
# 随机蓝屏程序
## 简要说明

- 它安装后,会在任意时间,跳出`win10`的蓝屏界面,让你冷静10分钟(doge)
- 它只是会显示一个蓝屏的图像,不会产生实际破坏
- 它使用`BlockInput`函数来禁用键盘与鼠标,所以在蓝屏界面依旧可以使系统级别的快捷键
![蓝屏图像](./res/blueScreen.png)

当然,也提供了一个真实蓝屏的选项
这会实实在在触发蓝屏

---
## 安装与使用
### 从安装包安装
一路下一步后
![setup](./README_RES/setup.png)

第一个选项为是否触发真实的蓝屏效果(后续可以运行安装路径中的`create_real.exe`来开启)
第二个则为是否立即开始随机触发,如果不勾选,则会在下一次开机后开始

### 从源码安装
1. 编译`src`
- VS 编译
打开`Developer Command Prompt for VS 2022`后,移动到本项目路径下,运行`make_cl.bat`即可
- gcc 编译
移动到本项目路径下,运行`make_gcc.bat`即可

2. 编译`Setup`
- 安装`Inno Setup Compiler`后
移动到项目的`Setup`目录,右键`setup.iss`,点击`compile`即可

3. 安装
- 安装包会在项目的`Setup/Output`下生成
接下来与`从安装包安装`步骤一样
---
本项目使用了 [stb_image](https://github.com/nothings/stb)