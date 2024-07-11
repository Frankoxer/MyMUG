# MyMUG

浙江大学 2024 年短学期课程《C++ 项目管理与工程实践》大作业项目：MyMUG，一个简单的四轨道键盘交互音游。

## 开发者

**HUANG** Y.F., **YUE** S.J., **WANG** M.K.

## 项目结构

`code/` 目录下是项目源代码，`documents/` 目录下是项目文档（包括协作方式、游戏介绍等），`resources/` 目录下是项目资源。

项目尚在开发中。

## 构建注意事项

1. 将 CMakeLists 中的 Qt 路径切换为自己电脑的相应路径；
2. 将 Qt 安装目录的 bin 文件夹添加进环境变量，然后在命令行中输入：
   ```text
    windeployqt.exe filepath
   ```
   其中 `filepath` 为 cmake-build-debug 文件夹中的 MyMUG.exe 可执行文件的路径。例如：
    ```text
     windeployqt.exe E:\course\c++\MyMUG\cmake-build-debug\MyMUG.exe
    ```
