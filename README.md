# png2ascii
A simple program that can let your png picture to ascii draw in black or colors by C

需要安装libpng库以确保编译成功
---
## 用以下指令编译

- gcc *.c -lpng -o p2a

## 用法

./p2a [文件目录] [精细程度](int) [色彩](1/0)
[文件名称](没有则不生成) [是否输出为html格式](1/0)
./p2a [file] [Fineness] (int) [Color] (1/0) [File name] (if there is none, it will not be generated) [Output in HTML format] [HTML](1/0)

## 目前进度
- [x] 实现png转换为ascii字符并可调节色彩精细程度，可输出至文件中
  - [X] 实现输出为html格式
- [ ] gif转ascii
- [ ] 视频转ascii(soon)
- [ ] gui界面

