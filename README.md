
学习LVGL ，当前分支为 release/v8.3 版本为 v8.3.10
---
对 lv_conf.h 的配置，lv_conf.h 文件路径为 LVGL.Simulator/lv_conf.h
---
~~~c
/*Enable features to draw on transparent background.
 *It's required if opa, and transform_* style properties are used.
 *Can be also used if the UI is above another layer, e.g. an OSD menu or video player.*/
#define LV_COLOR_SCREEN_TRANSP 1


/*API for fopen, fread, etc*/
#define LV_USE_FS_STDIO 1
#if LV_USE_FS_STDIO
    #define LV_FS_STDIO_LETTER 'A'                                    /*Set an upper cased letter on which the drive will accessible (e.g. 'A')*/
    #define LV_FS_STDIO_PATH "./../lvgl_mydemo/assert/image/"         /*Set the working directory. File/directory paths will be appended to it.*/
    #define LV_FS_STDIO_CACHE_SIZE 0    /*>0 to cache this number of bytes in lv_fs_read()*/
#endif


/*PNG decoder library*/
#define LV_USE_PNG 1

/*BMP decoder library*/
#define LV_USE_BMP 1

/* JPG + split JPG decoder library.
 * Split JPG is a custom format optimized for embedded systems. */
#define LV_USE_SJPG 1

/*GIF decoder library*/
#define LV_USE_GIF 1

/*QR code library*/
#define LV_USE_QRCODE 1


/*1: Show CPU usage and FPS count*/
#define LV_USE_PERF_MONITOR 0
#if LV_USE_PERF_MONITOR
    #define LV_USE_PERF_MONITOR_POS LV_ALIGN_BOTTOM_RIGHT
#endif

/*1: Show the used memory and the memory fragmentation
 * Requires LV_MEM_CUSTOM = 0*/
#define LV_USE_MEM_MONITOR 0
#if LV_USE_MEM_MONITOR
    #define LV_USE_MEM_MONITOR_POS LV_ALIGN_BOTTOM_LEFT
#endif

~~~


更改模拟屏幕大小，更改文件 lvgl_demo/lvgl_app.h 中的两个宏
---
~~~c
#define LCD_HOR_SIZE 240
#define LCD_VER_SIZE 240
~~~






---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
---
LVGL 官方 README
---


# Visual Studio simulator project for LVGL embedded GUI Library

![Screenshot](Screenshot.png)

## Introduction

This is a pre-configured Visual Studio project to try LVGL on a Windows PC. The
project only depend on Win32 API, C Runtime and C++ STL, so you can compile it
without any extra dependencies.

The project is currently maintained using Visual Studio 2019. It may well work
without modification in Visual Studio 2017 but it is not actively supported 
with that version, so please install and test with Visual Studio 2019 before 
reporting any bugs.

Some one will notice that this repository had been renamed from 
`lv_sim_visual_studio_sdl` to `lv_sim_visual_studio`. You can read 
[here](https://github.com/lvgl/lvgl/issues/2043) and know why.

**This project is not for Visual Studio Code, it is for Visual Studio 2019.**

Instructions for cloning, building and running the application are found below.

## Known Issues

- The LV_MEM_SIZE macro in lv_conf.h should be 128KiB or larger because you may
  meet the out of memory issue when you are using the 64-bit simulator.
  - Note: In this project, the size is set to 1024KiB.
- Users need to check the target selected in Visual Studio, because the 
  simulator project support ARM64 and Visual Studio will choose ARM64 in the 
  first time because of the alphabetical order.

## Supported Features

This repo is designed for keeping the simulator behavior. If you wonder to 
adapt your LVGL application to Windows, please visit 
[lvgl/lv_port_windows](https://github.com/lvgl/lv_port_windows).

- [x] Only depends on Win32 API, C Runtime and C++ STL.
- [x] Native support for x86, x64 and ARM64 Windows.
- [x] Support compiling with [VC-LTL](https://github.com/Chuyu-Team/VC-LTL) 
      toolchain to make the binary size as smaller as using MinGW.
- [x] Support Per-monitor DPI Aware.
- [x] Support Windows keyboard and mouse wheel event in the HAL level.
- [x] FreeType integration.

## Drop the ARM32 Windows support

For my deliberate consideration, The lv_port_windows project will drop the ARM32
support on the Windows platform. Here are the reasons:

- The latest version of ARM32 version for Windows desktop is Redstone 2 Insider
  Build 15035. I know Windows RT 8.1 and Windows 10 IoT Core aren't in the 
  stage of end of support, but most of daily users are drop their devices 
  (Windows RT 8.x tablets) or have a better solution (Windows 10 IoT Core users
  on Raspberry Pi devices should migrate to Linux or ARM64 version for Windows 
  10 desktop).
- Future ARM processors are deprecating ARM32 ISA support, and Apple Silicon M1
  had dropped the ARM32 support at all. So we can't run ARM32 version of Windows
  desktop applications on these devices.
- Reduce the size of release package and make the continuous integration faster.

## How to Clone

This repository contains other, necessary LVGL software repositories as 
[git submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules). Those 
submodules are not pulled in with the normal git clone command and they will be
needed. There are a couple of techniques to pull in the submodules.

### Everything at Once

This command will clone the lv_sim_visual_studio repository and all submodules
in a single step.

```
git clone --recurse-submodules https://github.com/lvgl/lv_sim_visual_studio.git
```

### Main Repository First, Submodules Second

If you've already cloned the main repository you can pull in the submodules 
with a second command. Both commands are shown below.

```
git clone https://github.com/lvgl/lv_sim_visual_studio.git
cd lv_port_win_visual_studio
git submodule update --init --recursive
```

### Keeping Your Clone Up-To-Date

If you have cloned this repository and would like to pull in the latest 
changes, you will have to do this in two steps. The first step will pull in
updates to the main repo, including updated _references_ to the submodules. The
second step will update the code in the submodules to match those references.
The two commands needed to accomplish this are shown below, run these commands
from inside the main repository's directory (top level `lv_sim_visual_studio`
directory works fine).

```
git pull
git submodule update --init --recursive
```

If you have chosen to fork this repository then updating the fork from upstream
will require a different, more involved procedure.

## How To Build & Run

Open the `LVGL.Simulator.sln` solution file in Visual Studio. Set the 
`LVGL.Simulator` project as the startup project. Click on the `Local Windows
Debugger` button in the top toolbar.  The included project will be built and 
run, launching from a cmd window.

## Trying Things Out

There are a list of possible test applications in the 
[LVGL.Simulator.cpp](LVGL.Simulator/LVGL.Simulator.cpp) file. Each test or demo
is launched via a single function call.  By default the `lv_demo_widgets` 
function is the one that runs, but you can comment that one out and choose any
of the others to compile and run.

Use these examples to start building your own application test code inside the
simulator.

## A Note About Versions

This repository has its submodule references updated shortly afk with minor 
version updates. When submodule updates take place a matching version tag is
added tter the release of new, major releases of LittlevGL's core 
[lvgl](https://github.com/lvgl/lvgl) project. Occasionally it is updated to
woro this repository.

If you need to pull in bug fixes in more recent changes to the submodules you
will have to update the references on your own. If source files are added or
removed in the submodules then the visual studio project will likely need
adjusting. See the commit log for examples of submodule updates and associated
visual studio file changes to guide you.
