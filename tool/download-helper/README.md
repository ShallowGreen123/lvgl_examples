# BP Download Help

[BP 项目](http://192.168.10.114/epower/gui-stm32h725igt6)快速烧录资源至 SPI Flash ，并生成项目需要的格式文件的工具 


## 使用指南

本项目入口文件为 `download_helper.py`，以下代码皆以此文件为上下文。
### 前置操作    
1. **项目下载**
```bash
$ git clone http://192.168.10.114/pc_assistant/download-helper.git 
```

2. **环境检测**   
    1. 本项目基于 `PYTHON` 搭建，需检测本地有无 PYTHON 环境
    2. `serial` 库检测与安装   
        ```bash
        # 检测 -> 查看输出有无 serial，没有则安装
        $ pip list
        
        # 安装
        $ pip install pyserial
        
        # 可能遇到的问题
        # check_hostname requires server_hostname => 检查网络，关闭代理
        ```

3. **串口确认**   
    > 查找并确认 BP 核心板串口 ID

    「此电脑」→ 「管理」→「设备管理器」→「端口」


### 烧录流程
> 将素材烧录至 BP 核心板中  

1. **指定烧录文件夹与串口**

    ```python
    # 以 "./pictures" 为指定烧录文件夹，串口，串口 "COM8" 为例：
    ins = download_helper("pictures", "COM8")
    ins.run()
    ```


2. **执行代码**   

    ```bash
    $ python download_helper.py
    
    # 可能遇到的问题
    # 1. ID mismatch => 更改函数 ui_proto 最后一位实参，将其增大
    # eg: self.commc_dev = ui_proto(0x0c, 0x7, port, 2000000, 2) => self.commc_dev = ui_proto(0x0c, 0x7, port, 2000000, 2)
    # 2. Check Hardware link => 检查串口是否正确、是否连接 => 转「串口确认」
    ```   

### 资源变更   
> 通过文件替换形式，更新 [BP 项目](http://192.168.10.114/epower/gui-stm32h725igt6)的资源文件依赖
1. **拷贝生成文件至 [BP 项目](http://192.168.10.114/epower/gui-stm32h725igt6)**   
    ```bash
    生成目录： `./build`   
    目标目录： `./GUI/lvgl_app/lv_demo_bp/assets`
    ```