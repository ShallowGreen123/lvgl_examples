
@REM @echo off
@REM REM 关闭回显

@REM 将代码页设置为 UTF-8，并将输出重定向到 nul，以避免在输出中看到代码页的提示信息。
chcp 65001 > nul

@REM 需要生成的汉字
set HAN_ZI=1
@REM 需要生成的字体
set FONT_NAME=JetBrainsMono-Bold.ttf
@REM 存放字体所在的路径
set FANT_PATH=D:\dgx\source\Font\JetBrainsMono-2.304\fonts\ttf

@REM 输出字体的命名
set OUT_FONT_NAME=Font_Mono_Bold
@REM 定义输出字体大小的一个列表
set "FONT_SIZE=15 16 17 18 19 20 25 "
@REM 生成字体后，输出存放的路径
set OUT_PATH=.\..\ui_base\assets

for %%i in (%FONT_SIZE%) do (
    lv_font_conv --no-compress --format lvgl --font %FANT_PATH%\%FONT_NAME% -o %OUT_PATH%\%OUT_FONT_NAME%_%%i.c --bpp 4 --size %%i -r 0x20-0x7F --symbols %HAN_ZI%
    @REM echo lv_font_conv --no-compress --format lvgl --font %FANT_PATH%\%FONT_NAME% -o %OUT_PATH%\%OUT_FONT_NAME%_%%i.c --bpp 4 --size %%i -r 0x20-0x7F --symbols %HAN_ZI%
)

pause