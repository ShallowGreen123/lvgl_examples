@echo off
@REM REM 关闭回显

@REM 将代码页设置为 UTF-8，并将输出重定向到 nul，以避免在输出中看到代码页的提示信息。
chcp 65001 > nul

@REM 图片转换脚本所在路径
set IMG_CONV=D:\dgx\code\2_studycode\lvgl_examples\tool\lvgl-image-conver\main.py
@REM 需要生成图片文件夹路径
set IMG_SRC=D:\dgx\code\2_studycode\lvgl_examples\lvgl_examples\T_DeckPro\assets
@REM 生成图片输出路径
set IMG_OUT=D:\dgx\code\T-DeckPro\examples\test_factory\src
@REM 图片颜色格式， RGB332, RGB565, RGB565SWAP, RGB888
set COLOR_FORMAT=RGB332
@REM 图片文件格式， C, BIN
set FILE_FORMAT=C

@REM echo "%IMG_CONV%"
@REM python "" -h
python %IMG_CONV% %IMG_SRC% -cf %COLOR_FORMAT% -ff %FILE_FORMAT% -o %IMG_OUT%
