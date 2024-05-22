from ui_proto import *

import logging
from user_log import user_log
import generate_file_utils

class download_helper:
    def __init__(self, picture_directory, port="COM8"):
        self.commc_dev = ui_proto(0x0c, 0x7, port, 2000000, 2)
        #self.commc_dev.data_init()
        self.picture_directory = picture_directory
        self.picture_list = []
        self.flash_base_addr = 0x100000 # 1MB from 0 address
        self.ram_base_addr = 0xD0800000 # 8MB from 0 address
        self.addr_mod = 128
        self.account_size = 0

    def run(self):
        self.load_pictures()
        self.calculate_store_info()
        self.download_pitctures()
        self.generate_code()

    def load_pictures(self):
        import os
        for root, dirs, files in os.walk(self.picture_directory, topdown=False):
            for name in files:
                file = os.path.join(root, name)
                fp = os.stat(file)
                picture_info = {"name": name,
                                "file": file,
                                "size": fp.st_size,
                                }
                self.picture_list.append(picture_info)

    def calculate_store_info(self):
        ram_addr = self.ram_base_addr
        flash_addr = self.flash_base_addr
        for item in self.picture_list:
            size = item["size"]
            item["flash_base_addr"] = flash_addr
            item["ram_base_addr"] = ram_addr
            if size % self.addr_mod:
                size = (int(size/self.addr_mod) + 1) * self.addr_mod
            else:
                size = int(size/self.addr_mod) * self.addr_mod
            self.account_size += size
            flash_addr += size
            ram_addr += size

    def download_pitctures(self):
        self.commc_dev.send_cmd_enter_wipe_mode(self.account_size, self.flash_base_addr, 0)
        for item in self.picture_list:
            logging.debug(item)
            with open(item["file"], "rb") as fd:
                buf = fd.read(item["size"])
                self.commc_dev.send_cmd_send_picture_context(buf, item["flash_base_addr"], 0x00)

    def generate_code(self):
        code_buf = "\r\n\r\n"
        for item in self.picture_list:
            name = item["name"].split(".")[0]
            logging.debug(name)
            buf = "uint32_t * %s_addr = register_flash_sram(0x%x, 0x%x, %d);\r\n"%(name, item["flash_base_addr"], item["ram_base_addr"], item["size"])
            code_buf += buf
        logging.debug(code_buf)

user_log("111.log", logging.DEBUG)
ins = download_helper("pictures/led", "COM5")
ins.run()

gf = generate_file_utils.generate_file(ins.picture_list, "build", "bp_img_addr_init", "bp_img_src_init")
gf.run()
# print(ins.picture_list)
