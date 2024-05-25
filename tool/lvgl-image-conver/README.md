
# 

使用方法 

1、安装 python 环境，在 windows 环境下，打开命令行，输入 **python --version**，出现版本号表示 python 安装成功
~~~
C:\>python --version
Python 3.11.4
~~~

2、安装必要的 python 包，输入命令 **pip install pillow**
~~~
C:\>pip install pillow
~~~

3、执行图片转换脚本，下面命令将文件夹 ./img/ 下的所有图片，以 RGB565 的图片格式，转化为 .C 文件，转化完成的图片放在 ./img/img_output/ 文件夹下。
~~~
C:\imageConver> python main.py ./img/ -cf RGB565 -ff C -o ./img/img_output/
~~~

4、可以执行 **python main.py -h** 查看帮助
~~~
usage: main.py [-h] [-f {true_color,true_color_alpha,true_color_chroma,indexed_1,indexed_2,indexed_4,indexed_8,alpha_1,alpha_2,alpha_4,alpha_8,raw,raw_alpha,raw_chroma}] [-cf {RGB332,RGB565,RGB565SWAP,RGB888}] [-ff {C,BIN}] [-o O] [-r] [-d] filepath [filepath ...]

positional arguments:
  filepath              images dir paths (or file paths) you wanna convert

options:
  -h, --help            show this help message and exit
  -f {true_color,true_color_alpha,true_color_chroma,indexed_1,indexed_2,indexed_4,indexed_8,alpha_1,alpha_2,alpha_4,alpha_8,raw,raw_alpha,raw_chroma}, -format {true_color,true_color_alpha,true_color_chroma,indexed_1,indexed_2,indexed_4,indexed_8,alpha_1,alpha_2,alpha_4,alpha_8,raw,raw_alpha,raw_chroma}
                        converted file format: true_color, true_color_alpha, true_color_chroma, indexed_1, indexed_2, indexed_4, indexed_8, alpha_1, alpha_2, alpha_4, alpha_8, raw, raw_alpha, raw_chroma. The default is: true_color_alpha
  -cf {RGB332,RGB565,RGB565SWAP,RGB888}, -color-format {RGB332,RGB565,RGB565SWAP,RGB888}
                        converted color format: RGB332, RGB565, RGB565SWAP, RGB888
  -ff {C,BIN}, -file-format {C,BIN}
                        converted file format: C(*.c), BIN(*.bin)
  -o O, -output-filepath O
                        output file path. if not set, it will saved in the input dir
  -r                    convert files recursively
  -d                    need to dith
~~~

5、img_test.png 为 8\*8 像素大小的图片，生成的 img_test.c 的 img_test_map 的大小为 192 = 8\*8*(RBG565 + ALPHA)。RBG565 大小为 2 字节，ALPHA 通道大小为 1 一字节。



