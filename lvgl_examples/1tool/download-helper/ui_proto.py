# -*- coding: utf-8 -*-
import struct
import proto
import logging
import time
from proto import dump_hex as dump_hex

class ui_proto(proto.proto_dev):
    def __init__(self, devid, index, port, baudrate, timeout, retry_count=3):
        self.splice_len = 512
        super().__init__(devid, index, port, baudrate, timeout, 0x03, 0xec, retry_count)
        func_mapping = {
            0x20: self.reply_func_enter_picture_send_mode,
            0x21: self.reply_func_enter_wipe_mode,
            0x22: self.reply_func_send_picture_context,
            0x23: self.reply_func_reboot,
        }
        for (cmdid, func) in func_mapping.items():
            self.reply_func_register(cmdid, func)

    def reply_func_enter_picture_send_mode(self, msg):  # 请求进入图片发送模式命令的下位机回复函数
        logging.info('[reply] Enter picture send mode')
        self.rtn_cod = msg._buf[11]
        if self.rtn_cod != 0:
            logging.debug("[reply] Receive rtn_code\t%02x"%self.rtn_cod)
            return (False, None)
        else:
            if len(msg._buf) == 16:
                self.splice_len = msg._buf[12] + (msg._buf[13]  << 8)
            return (True, {})

    def reply_func_enter_wipe_mode(self, msg):  # 发送擦除命令的下位机回复函数
        logging.info('[reply] Enter wipe mode')
        self.rtn_cod = msg._buf[11]
        if self.rtn_cod != 0:
            logging.debug("[reply] Receive rtn_code\t%02x"%self.rtn_cod)
            return (False, None)
        else:
            return (True, {})

    def reply_func_send_picture_context(self, msg):  # 发送图片内容命令的下位机回复函数
        logging.debug("[reply]receive picture context")
        self.rtn_cod = msg._buf[11]
        if self.rtn_cod != 0:
            logging.debug("[reply] Receive rtn_code\t%02x"%self.rtn_cod)
            return (False, None)
        self.rx_seq_nbr = 0
        for i in [0, 1, 2 ,3]:
            self.rx_seq_nbr += (msg._buf[12 + i] << (i * 8))
        if self.rx_seq_nbr == self.tx_seq_nbr:
            logging.info('[reply] RecvData OK\t%d %d'%(self.rx_seq_nbr, self.tx_seq_nbr))
            return (True, {})
        else:
            logging.debug('[reply] RecvData FAILED\t%d %d'%(self.rx_seq_nbr, self.tx_seq_nbr))
            return (False, None)

    def reply_func_reboot(self, msg):  # 发送设备重启命令的下位机回复函数
        logging.info("[reply] Reboot")
        self.rtn_cod = msg._buf[11]
        if self.rtn_cod != 0:
            logging.debug("[reply] Reboot Failed\t%02x"%self.rtn_cod)
            return (False, None)
        else:
            logging.info("[reply] Reboot OK")
            return (True, {})

    def send_cmd_enter_picture_send_mode(self, picture_len, picture_address, memory_type=1, version=1):  # 请求进入图片发送模式命令的上位机发送函数
        logging.debug("Request Enter write \n")
        payload = struct.pack('<IIBBBBBBBBB', picture_len, picture_address, memory_type, 0,0,0,0,0,0,0,0)  # 后面的0为保留字段
        if version == 1:
            return self.send_v1_cmd_to_mc(0, 0, 0x20, payload)
        elif version == 2:
            return self.send_v2_cmd_to_mc(0, 0, 0x20, payload)

    def send_cmd_enter_wipe_mode(self, wipe_len, wipe_start_address, wipe_type, version=1):  # 发送擦除命令的上位机发送函数
        payload = struct.pack('<IIHBBBBBBBB', wipe_len, wipe_start_address, wipe_type, 0,0,0,0,0,0,0,0)
        logging.debug("Send wipe cmd")
        logging.debug("Erase base address 0X%x, Length %d"%(wipe_start_address, wipe_len))
        if version == 1:
            return self.send_v1_cmd_to_mc(0, 0, 0x21, payload)
        if version == 2:
            return self.send_v2_cmd_to_mc(0, 0, 0x21, payload)

    def send_cmd_send_picture_context(self, picture_buf, picture_address, memory_type, version=1):  # 发送图片内容命令的上位机发送函数
        logging.debug ('Send firmware data')
        amount_len = picture_len = len(picture_buf)
        print(picture_len)
        logging.debug(picture_len)
        if self.send_cmd_enter_picture_send_mode(picture_len, picture_address, memory_type) is not None:
            self.tx_seq_nbr = 0
            split_len = self.splice_len
            while picture_len > 0:
                logging.debug(self.tx_seq_nbr)
                #time.sleep(0.01)
                t1 = time.time()
                if (picture_len >= split_len):
                    send_buf = picture_buf[0:split_len]
                    if self.send_picture_v1(self.tx_seq_nbr, 0, 0x22, send_buf, version) is not None:
                        picture_buf = picture_buf[split_len:]
                        picture_len -= split_len
                        self.tx_seq_nbr += 1
                        t2 = time.time()
                        t = t2-t1
                        list = [self.tx_seq_nbr, t]
                        #self.csv_writer.writerow(list)
                    else:
                        logging.debug("Send picture data seq number failed seqnum %d"%(self.tx_seq_nbr))
                        return False
                else:
                    send_buf = picture_buf[0:picture_len]
                    if self.send_picture_v1(self.tx_seq_nbr, 0, 0x22, send_buf, version) is not None:
                        picture_buf = picture_buf[split_len:]
                        picture_len -= split_len
                        self.tx_seq_nbr += 1
                    else:
                        logging.debug("Send picture data seq number failed seqnum %d"%(self.tx_seq_nbr))
                        return False
            return True


    def send_cmd_reboot(self, version):  # 发送设备重启命令的上位机发送函数
        logging.debug ("Send reboot cmd")
        if version == 1:
            return self.send_v1_cmd_to_mc(0, 0, 0x23, b'')
        elif version == 2:
            return self.send_v2_cmd_to_mc(0, 0, 0x23, b'')

    def send_picture_v1(self, seq, cmdset, cmdid, payload, version):
        # encrypt type: 0 - no encrypt
        # data sequence number
        # packet length
        pl = struct.pack('<IH', seq, self.splice_len)
        pl += payload
        if version == 1:
            return self.send_v1_cmd_to_mc(0, cmdset, cmdid, pl)
        elif version == 2:
            return self.send_v2_cmd_to_mc(0, cmdset, cmdid, pl)

    def data_init(self):
        import csv
        self.csv_file_name_base = time.strftime("./" +"_test_%Y_%m_%d_%H_%M_%S", time.localtime())
        self.csv_file_name = self.csv_file_name_base + ".csv"  # csv文件名
        self.save_data_file = open(self.csv_file_name,'a', encoding='utf-8',newline='')
        self.csv_writer = csv.writer(self.save_data_file)
        self.csv_writer.writerow(["num", "time"])


def test_write():
    a = ui_proto(0x0c, 0x7, "COM5", 2000000, 0.1)
    a.data_init()
    test_buf = b''
    for i in range(1024*128):
        test_buf += b'\x59\x59\x59\x59\x59\x59\x59\x59'
    t1 = time.time()
    a.send_cmd_send_picture_context(test_buf, 0x00, 0x00)
    t2 = time.time()
    logging.debug(t2-t1)
    logging.debug(len(test_buf))

def test_wipe_mode():
    a = ui_proto(0x0c, 0x7, "COM5", 2000000, 0.1)
    a.send_cmd_enter_wipe_mode(0x100000, 0x00, 0)

if __name__ == "__main__":
    import logging
    from user_log import user_log
    user_log("111.log", logging.DEBUG)
    test_write()
    # test_wipe_mode()
    # a.data_init()
    # test_buf = b''
    # for i in range(1024*1024):
    #     test_buf += b'\x59'
    # # for i in range(10):
    # t1 = time.time()
    # a.send_cmd_send_picture_context(test_buf, 0x00, 0x00)
    # t2 = time.time()
    # print(t2-t1)
    # print(len(test_buf))
    # a.send_cmd_enter_wipe_mode(0x25000, 0x00, 0)
    # a.get_product_info()
