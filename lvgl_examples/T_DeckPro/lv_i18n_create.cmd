
@echo off
REM 关闭回显

REM 输入*.yml路径和编译输出路径
set yml_path=assets
set out_path=.\..\ui_base\assets

REM 使用 for /f 命令执行 node -v 并捕获输出
for /f "tokens=*" %%i in ('npm -v') do set "param=%%i"

for /f "tokens=*" %%i in ('node -v') do set "param1=%%i"

for /f "tokens=*" %%i in ('lv_i18n -v') do set "lv_i18n=%%i"

REM 输出捕获到的版本信息
echo "********************************"
echo "npm version: %param%"
echo "node version: %param1%"
echo "lv_i18n version: %lv_i18n%"
echo "lv_i18n compile -t %yml_path%\*.yml -l zh-cn -o %out_path%
echo "********************************"

REM 如果没有 node.js 环境直接退出
if "%param%" == "0" (
    echo "No `node.js` environment found"
    exit /b 1
)

REM 如果没有安装 lv_i18n, 并且有 node.js 环境，则安装 lv_i18n
if "%lv_i18n%" == "0" (
    if not "%param%" equ "0" (
        echo "install lv_i18n"
        @REM 安装 lv_i18n
        npm i lv_i18n -g
    )
) else (
    echo "lv_i18n compile ..."
    @REM 编译 lv_i18n
    @REM cd lvgl_examples\T_DeckPro\assets
    for /f "tokens=*" %%i in ('lv_i18n compile -t %yml_path%\*.yml -l zh-cn -o %out_path%') do set "ret_val=%%i"
)

REM 如果啥也没有返回，表示 lv_i18n 编译生成成功
if "%ret_val%" == "" (
    echo "lv_i18n compile succeed!"
) else (
    echo "lv_i18n compile failed!"
)
