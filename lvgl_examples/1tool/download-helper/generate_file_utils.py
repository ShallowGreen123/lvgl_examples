# -*- coding: utf-8 -*-
class generate_file:
    def __init__(self,  picture_list = [], dir_name="build", addr_file_name="addr_init", src_file_name="src_init"):
        self.dir_name = dir_name
        self.addr_file_name = addr_file_name
        self.src_file_name = src_file_name
        self.picture_list = picture_list

    def run(self):
        import os
        if not os.path.isdir(self.dir_name):
            os.makedirs(self.dir_name)
            if(self.picture_list == 0):
                # raise AttributeError("实参 picture_list 长度不能为 0")
                return
        self.generate_addr_file()
        self.generate_src_file()

    def generate_addr_file(self):
        targetVariableFile = "./%s/%s.c"%(self.dir_name, self.addr_file_name)
        with open(targetVariableFile, 'w+', newline='') as f:
            f.write("#include<stdint.h>\r\n")
            f.write("\r\n\r\n")
            
            
            f.write("extern uint8_t *register_flash_sram(uint32_t flash_addr, uint32_t sram_addr, uint32_t len);")
            f.write("\r\n\r\n")
            
            # 地址变量声明
            for item in self.picture_list:
                name = item["name"].split(".")[0]
                f.write("uint8_t *%s_addr;\r\n"%(name))

            f.write("\r\n")

            f.write("void bp_img_src_init(){\r\n")

            if True:  # 一次性注册
                # 内存注册
                first_item = self.picture_list[0]
                last_item = self.picture_list[-1]
                total_len = int(last_item["ram_base_addr"]) - int(first_item["ram_base_addr"]) + last_item["size"]
                
                f.write("\r\n")
                f.write("\t// source block register\r\n")
                f.write("\tregister_flash_sram(0x%x, 0x%x, %d);\r\n"%(first_item["flash_base_addr"], first_item["ram_base_addr"], total_len))
                f.write("\r\n")
                
                # 地址变量赋值
                f.write("\t// sigle block address\r\n")

                for item in self.picture_list:
                    name = item["name"].split(".")[0]
                    f.write("\t%s_addr = (uint8_t *)(0x%x);\r\n"%(name, item["ram_base_addr"]))
            else:
                # 地址变量赋值
                for item in self.picture_list:
                    name = item["name"].split(".")[0]
                    f.write("\t%s_addr = (uint8_t *)register_flash_sram(0x%x, 0x%x, %d);\r\n"%(name, item["flash_base_addr"], item["ram_base_addr"], item["size"]))


            f.write("}\r\n")
            f.write("\r\n")

    def generate_src_file(self):
        targetSourceFile = "./%s/%s.c"%(self.dir_name, self.src_file_name)
        with open(targetSourceFile, 'w+', newline='') as f:
            includePath = "\"../../lv_demo.h\""

            # 文件头
            f.write("#include %s\r\n#ifndef SIMULATOR\r\n#ifndef LV_ATTRIBUTE_IMG_SOURCE\r\n#define LV_ATTRIBUTE_IMG_SOURCE\r\n"%(includePath))
            
            f.write("\r\n")
            
            # 地址信息
            for item in self.picture_list:
                name = item["name"].split(".")[0]
                f.write("extern uint8_t * %s_addr;\r\n"%(name))

            f.write("\r\n")

            # 定义变量
            for item in self.picture_list:
                name = item["name"].split(".")[0]
                f.write("lv_img_dsc_t %s;\r\n"%(name))

            f.write("\r\n")

            f.write("\r\n\r\nint init_img_source(void);\r\n\r\n")
            f.write("int init_img_source(void){ \r\n")
            
            f.write("\r\n")
            
            # 固化图片头大小
            f.write("\tuint32_t img_header_size = (uint32_t) sizeof(lv_img_header_t);\r\n\r\n")
            # 图片对象赋值
            for item in self.picture_list:
                name = item["name"].split(".")[0]
                f.write("\t// %s\r\n"%(name))
                f.write("\tlv_img_header_t *%s_hd = (lv_img_header_t*) %s_addr;\r\n"%(name, name))
                f.write("\t%s.header.cf = %s_hd->cf;\r\n"%(name, name))
                f.write("\t%s.header.always_zero = 0;\r\n"%(name))
                f.write("\t%s.header.w = %s_hd->w;\r\n"%(name, name))
                f.write("\t%s.header.h = %s_hd->h;\r\n"%(name, name))
                f.write("\t%s.data_size = %d - img_header_size;\r\n"%(name, item["size"]))
                f.write("\t%s.data = (%s_addr + img_header_size);\r\n"%(name, name))
                f.write("\r\n")
            # 文件尾
            f.write("\treturn 0;\r\n")
            f.write("} \r\n\r\n")
            f.write("#endif /* LV_ATTRIBUTE_IMG_SOURCE */\r\n#endif /* SIMULATOR */")
            f.close()
if __name__ == '__main__':
    print('run')