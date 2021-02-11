# Windows-Camera-Capture
Windows Camera Capture Windows 下面摄像头的捕获和渲染，主要参考 WebRTC 代码使用 dshow 实现

编译方法

1、git clone https://github.com/yangpan4485/Windows-Camera-Capture.git

2、cd Windows-Camera-Capture

3、md build

4、cd build

5、cmake ..

6、打开 camera-capture-demo.sln 运行，注意要将 jpeg62.dll 和 SDL2.dll 拷贝到 output/bin/Release 目录下面