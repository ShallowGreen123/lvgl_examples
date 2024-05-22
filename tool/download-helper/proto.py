# -*- coding: utf-8 -*-
import struct
import hashlib
import os
import time
import serial.tools.list_ports
import logging

CRC8Table = [
    0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65,
    157, 195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220,
    35, 125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98,
    190, 224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255,
    70, 24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7,
    219, 133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154,
    101, 59, 217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36,
    248, 166, 68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185,
    140, 210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205,
    17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14, 80,
    175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176, 238,
    50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18, 145, 207, 45, 115,
    202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180, 234, 105, 55, 213, 139,
    87, 9, 235, 181, 54, 104, 138, 212, 149, 203, 41, 119, 244, 170, 72, 22,
    233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246, 168,
    116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107, 53
]

CRC16Table = [
    0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
    0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
    0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
    0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
    0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
    0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
    0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
    0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
    0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
    0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
    0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
    0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
    0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
    0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
    0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
    0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
    0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
    0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
    0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
    0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
    0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
    0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
    0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
    0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
    0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
    0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
    0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
    0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
    0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
    0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
    0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
    0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
]

crc8 = 0
crc8_init = 0x77
crc16_init_rec = 0x5281
crc16_init_com = 0x3692
cnt = 60
crc8_err = 0
crc16_err = 0


def dump_hex(buff):
    print_buf = []
    str_buf = "[ "
    for item in buff:
        str_buf += "%02x "%item
    str_buf += " ]"
    logging.debug(str_buf)

def chkCRC8(bytes):
    crc8 = crc8_init
    ret = 0
    for byte in bytes:
        ret = crc8 ^ byte
        crc8 = CRC8Table[ret]
    return crc8


def chkCRC16(bytes):
    crc16 = crc16_init_com
    ret = 0

    for byte in bytes:
        ret = byte
        crc16 = (crc16 >> 8 & 0xff) ^ CRC16Table[(0xff & crc16) ^ ret]
    return crc16

class V1_msg:
    def __init__(self):
        self._buf = bytes()

    def sender(self):
        return self._buf[4]

    @property
    def recver(self):
        return self._buf[5]

    @property
    def recverv2(self):
        return self._buf[9]

    def check_recver(self, recver):
        return (self.recver == recver)

    def check_recverv2(self, recver):
        return (self.recverv2 == recver)

    def seqNum(self):
        (seq,) = struct.unpack("<h", self._buf[6:8])
        return seq

    def cmdType(self):
        return self._buf[8]

    def cmdSet(self):
        return self._buf[9]

    def cmdID(self):
        return self._buf[10]

    def check_crc8(self):
        if chkCRC8(self._buf[0:4]) == 0:
            return True
        else:
            return False

    def check_crc16(self):
        if chkCRC16(self._buf) == 0:
            return True
        else:
            logging.debug("crc16 err")
            dump_hex(self._buf)
            return False

    def checksum_valid(self):
        return self.check_crc8() and self.check_crc16()

    def checksum_v0valid(self):
        return self.check_crc8() and self.check_crc16() # (chkCRC16(self._buf, crc16_init_com) == 0)

    def head_synced(self):
        if len(self._buf) == 0:
            return False
        if self._buf[0] != 0x55:
            return False
        if len(self._buf) < 4:
            return True
        if self.check_crc8():
            return True
        else:
            dump_hex(self._buf)
            logging.debug("crc8 err")
            #return True
            return False

    def v0exchangeFeedback(self):
        if len(self._buf) < 28:
            return None
        val             = {}
        val['esc_id']      = self._buf[6]
        val['esc_status']  = self._buf[7]
        val['bus_voltage'] = self._buf[8]  + (self._buf[9] << 8)
        val['esc_cur']     = self._buf[10] + (self._buf[11] << 8)
        val['mcu_tmpr']    = self._buf[12] + (self._buf[13] << 8)
        val['esc_speed']   = self._buf[14] + (self._buf[15] << 8)
        val['thrt_rxd']    = self._buf[16] + (self._buf[17] << 8)
        val['esc_cmd_out'] = self._buf[18] + (self._buf[19] << 8)
        val['debug0']      = self._buf[20] + (self._buf[21] << 8)
        val['debug1']      = self._buf[22] + (self._buf[23] << 8)
        val['debug2']      = self._buf[24] + (self._buf[25] << 8)
        val['crc16']       = self._buf[26] + (self._buf[27] << 8)
        return val

    def msg_len(self):
        if not self.check_crc8():
            return 0
        (len_ver,) = struct.unpack("<h", self._buf[1:3])
        return len_ver & 0x3ff

    @property
    def msg_ver(self):
        if not self.check_crc8():
            return 0
        (len_ver,) = struct.unpack("<h", self._buf[1:3])
        return (len_ver >> 10) & 0xf

    def add_no_check(self, buf):
        for i in range(len(buf)):
            self._buf += struct.pack('<B', buf[i])
            while (not self.head_synced()) and (len(self._buf) > 0):
                self._buf = self._buf[1:]
            if (len(self._buf) > 12) and (self.bytes_expected() == 0):
                if self.checksum_valid():
                    return True
                else:
                    logging.debug("checksum error")
                    self._buf = self._buf[1:]
        return False

    def add(self, buf, sendId):
        for i in range(len(buf)):
            self._buf += struct.pack('<B', buf[i])
            while (not self.head_synced()) and (len(self._buf) > 0):
                self._buf = self._buf[1:]
            if (len(self._buf) > 12) and (self.bytes_expected() == 0):
                if self.checksum_valid():
                    if self.check_recver(sendId):
                        return True
                    else:
                        dump_hex(self._buf)
                        #self._buf = bytes()
                        self._buf = self._buf[1:]
                        logging.debug('Check Receive failed')
                        return False
                else:
                    logging.debug("checksum error")
                    self._buf = self._buf[1:]
        return False

    def add_with_slave(self, buf, sendId, slave_receive_id):
        for i in range(len(buf)):
            self._buf += struct.pack('<B', buf[i])
            while (not self.head_synced()) and (len(self._buf) > 0):
                self._buf = self._buf[1:]
            if (len(self._buf) > 12) and (self.bytes_expected() == 0):
                if self.checksum_valid():
                    if self.check_recver(sendId):
                        return 1
                    elif self.check_recver(slave_receive_id):
                        return 2
                    else:
                        return 0
                else:
                    logging.debug("checksum error")
                    self._buf = self._buf[1:]
        return 0

    def addv2(self, buf, sendId):
        for i in range(len(buf)):
            self._buf += struct.pack('<B', buf[i])
            while (not self.head_synced()) and (len(self._buf) > 0):
                self._buf = self._buf[1:]
            if (len(self._buf) > 12) and (self.bytes_expected() == 0):
                if self.checksum_valid():
                    return True
                else:
                    logging.debug("checksum error")
                    self._buf = self._buf[1:]
        return False

    def addv0(self, buf):
        for i in range(len(buf)):
            self._buf += struct.pack('<B', buf[i])
            while (not self.head_synced()) and (len(self._buf) > 0):
                self._buf = self._buf[1:]
            if (len(self._buf) > 12) and (self.bytes_expected() == 0):
                if self.checksum_valid():
                    return True
                else:
                    logging.debug("checksum error")
                    self._buf = self._buf[1:]
        return False

    def bytes_expected(self):
        if len(self._buf) < 4:
            return 12 - len(self._buf)
        return self.msg_len() - len(self._buf)

    def valid(self):
        if len(self._buf) > 12 and self.bytes_expected() == 0 and self.checksum_valid():
            return True
        else:
            # print self.bytes_expected()
            if len(self._buf) > 12 and self.bytes_expected() == 0:
                self._buf = bytes()
            return False

    def v0valid(self):
        if len(self._buf) == 28 and self.bytes_expected() == 0 and self.checksum_valid():
            return True
        else:
            # print self.bytes_expected()
            if len(self._buf) > 12 and self.bytes_expected() == 0:
                self._buf = bytes()
            return False

class proto_dev:
    def __init__(self, devid, index, port, baudrate=115200, timeout=0, sender=0x01, receiver=0xec, retry_count=3):
        self.serial_device = port
        self.device_flag   = 0
        self.baudrate = baudrate
        self.dev_id = devid
        self.dev_index = index
        self.sender = sender
        self.receiver = receiver
        self.use_zigbee = 0
        self.zigbee_id = 0
        self.dest_module_id = 0
        self.retry_count = retry_count
        self.dev = None
        self.device_flag = 0
        self.timeout = timeout
        self.mac_addr = 0x0

        self.rx_seq_nbr = 0
        self.tx_seq_nbr = 0
        self.reply_func = {}
        self.reply_slave_func = {}
        self.reply_func_init()

        if not self.serial_device:
            return

        if os.path.isfile(self.serial_device):
            try:
                self.dev = open(self.serial_device, mode='rb')
                self.device_flag = 1
                self.dev.timeout = timeout
                self.dev.writeTimeout = timeout
            except:
                self.device_flag = 0
                return
        else:
            import serial
            try:
                self.dev = serial.Serial(self.serial_device, self.baudrate)
                self.device_flag = 1
                self.dev.timeout = timeout
                self.dev.writeTimeout = timeout
            except:
                self.device_flag = 0
                return

    def set_use_zigbee(self, use_zigbee, zigbee_id):
        self.use_zigbee = use_zigbee
        self.zigbee_id = zigbee_id

    def set_sender(self, sender):
        self.sender = sender

    def set_receiver(self, receiver):
        self.receiver = receiver

    def set_mac_addr(self, mac_addr):
        self.mac_addr = mac_addr

    def get_mac_addr(self):
        return self.mac_addr

    def set_dest_module_id(self, dest_module_id):
        self.dest_module_id = dest_module_id

    def device_is_open(self):
        return self.device_flag

    def close(self):
        if self.dev:
            self.dev.close()
            self.dev = None

    def write(self, buf):
        return self.dev.write(buf)

    def read(self, n):
        try:
            return self.dev.read()
        except:
            return ""

    def send(self, msg):
        try:
            #dump_hex(msg._buf)
            self.write(msg._buf)
        except:
            logging.debug("Write Failed: Check Hardware link")
            return False
        return True

    def _asc2str(self, asc_str):
        str_buf    = bytes()
        for i in range(int(len(asc_str)/2)):
            str_buf += struct.pack('<B', int(asc_str[2*i:2*i+2], 16))
        return str_buf

    def special_handle_v2(self, msg, cmdid):
        if msg.msg_ver == 2:
            msg._buf = msg._buf[5:(msg.msg_len() - 2)]
            return self.special_handle_v1(msg, cmdid)
        else:
            logging.debug("Receive V2 protocol failed...")
            return (False, None)

    def reply_func_register(self, cmdid, func):
        self.reply_func[cmdid] = func

    def reply_func_get_version(self, msg):
        buf = msg._buf[13:29]
        buf = buf.replace(b'\x00', b'')
        logging.info('Hardware version:\t' + str(buf))
        ld_ver = 0
        fw_ver = 0
        for i in [0, 1, 2 ,3]:
            ld_ver += msg._buf[29 + i] << (i * 8)
        for i in [0, 1, 2 ,3]:
            fw_ver += msg._buf[33 + i] << (i * 8)
        logging.info('Loader version:\t\t%08x'%(ld_ver))
        logging.info('Firmware version:\t%08x'%(fw_ver))
        return (True, {})

    def reply_func_get_product_info(self, msg):
        logging.info("Get Product Info:")
        product_info = {}
        buf = msg._buf[12:28]
        buf = buf.replace(b'\x00', b'')
        product_info['category'] = str(buf) #buf.decode("gbk")
        #logging.info('Category:\t\t' + str(buf)) #buf.decode("gbk"))
        buf = msg._buf[28:44]
        buf = buf.replace(b'\x00', b'')
        product_info['oem'] = str(buf) #buf.decode("gbk")
        #logging.info('OEM:\t\t' + str(buf)) # buf.decode("gbk"))
        buf = msg._buf[44:60]
        buf = buf.replace(b'\x00', b'')
        product_info['hw_ver'] = str(buf) #buf.decode("gbk")
        #logging.info('Hardware version:\t' + str(buf)) #buf.decode("gbk"))
        ldr_ver = 0
        fmw_ver = 0
        for i in [0, 1, 2 ,3]:
            fmw_ver += (msg._buf[60 + i] << (i * 8))
        for i in [0, 1, 2 ,3]:
            ldr_ver += (msg._buf[64 + i] << (i * 8))

        product_info['ldr_ver'] = ldr_ver
        product_info['fmw_ver'] = fmw_ver
        logging.info('Loader version:\t\t%08x'%ldr_ver)
        logging.info('Firmware version:\t%08x'%fmw_ver)
        return (True, product_info)

    def reply_func_get_programmer_info(self, msg):
        logging.info("Get Programmer Info:")
        product_info = {}
        buf = msg._buf[12:28]
        buf = buf.replace(b'\xff', b'\x00')
        product_info['category'] = str(buf)
        logging.info('Category:\t\t' + str(buf))
        buf = msg._buf[28:44]
        buf = buf.replace(b'\xff', b'\x00')
        product_info['oem'] = str(buf)
        logging.info('OEM:\t\t' + str(buf))
        buf = msg._buf[44:60]
        buf = buf.replace(b'\xff', b'\x00')
        product_info['hw_ver'] = str(buf)
        logging.info('Hardware version:\t' + str(buf))
        ldr_ver = 0
        fmw_ver = 0
        for i in [0, 1, 2 ,3]:
            fmw_ver += (msg._buf[60 + i] << (i * 8))
        for i in [0, 1, 2 ,3]:
            ldr_ver += (msg._buf[64 + i] << (i * 8))

        product_info['ldr_ver'] = ldr_ver
        product_info['fmw_ver'] = fmw_ver
        logging.info('Loader version:\t%08x'%ldr_ver)
        logging.info('Firmware version:\t%08x'%fmw_ver)
        return (True, {})

    def reply_func_get_sampler_info(self, msg):
        logging.info("Receive Sampler Info")
        self.rtn_cod = msg._buf[11]
        if self.rtn_cod == 0:
            ret = struct.unpack("<ffffffffffffffff", msg._buf[12:76])
            logging.info(ret)
            return (True, ret)
        else:
            logging.info("Sample ON-Going")
            return (False, None)

    def reply_func_receive_sampler_start(self, msg):
        logging.info("Receive Sampler Start Feedback")
        return (True, None)

    def reply_func_receive_from_pyboard(self, msg):
        logging.info("Receive from PYBoard")
        return (True, None)
    def reply_func_receive_beep(self, msg):
        logging.info("Receive Beep")
        return (True, None)
    def reply_func_get_time_info(self, msg):
        logging.info("Receive time info")
        dump_hex(msg._buf)
        ret = struct.unpack("<IHBBBBB", msg._buf[12:23])
        logging.info("Timestamp:\t%d"%ret[0])
        logging.info("Year:\t\t%d"%ret[1])
        logging.info("Month:\t%d"%ret[2])
        logging.info("Day:\t\t%d"%ret[3])
        logging.info("Hour:\t\t%d"%ret[4])
        logging.info("Minute:\t%d"%ret[5])
        logging.info("Second:\t%d"%ret[6])
        return (True, None)

    def reply_func_set_time_info(self, msg):
        logging.info("Receive time info")
        ret = struct.unpack("<IHBBBBB", msg._buf[12:23])
        logging.info("Timestamp:\t%d"%ret[0])
        logging.info("Year:\t\t%d"%ret[1])
        logging.info("Month:\t%d"%ret[2])
        logging.info("Day:\t\t%d"%ret[3])
        logging.info("Hour:\t\t%d"%ret[4])
        logging.info("Minute:\t%d"%ret[5])
        logging.info("Second:\t%d"%ret[6])
        return (True, None)

    def reply_func_init(self):
        func_mapping = {
            0x1: self.reply_func_get_version,
            0xd: self.reply_func_get_product_info,
            0x13: self.reply_func_get_programmer_info,
            0x14: self.reply_func_get_sampler_info,
            0x15: self.reply_func_receive_sampler_start,
            0x16: self.reply_func_receive_from_pyboard,
            0x17: self.reply_func_receive_beep,
            0x33: self.reply_func_get_time_info,
            0x34: self.reply_func_set_time_info,
        }
        for (cmdid, func) in func_mapping.items():
            self.reply_func_register(cmdid, func)

    def special_handle_v1(self, msg, cmdid):
        if msg.cmdID() != cmdid:
            logging.debug("MSG ID mismatch")
            dump_hex(msg._buf)
            return (False, None)
        if cmdid in self.reply_func.keys():
            return self.reply_func[cmdid](msg)
        else:
            logging.debug("...Could not find handle function for cmdid %d..."%cmdid)
            return (False, None)

    def send_v1_cmd_to_mc(self, seq, cmdset, cmdid, payload):
        """
        1.use echo - reply mode: send and receive in the same loop with retry
        2.add robustness protection
        """
        send_msg = V1_msg()
        cmdtype = 0x01 << 5
        length = len(payload) + 13
        length = length | (0x01 << 10)
        pad = 0
        if self.use_zigbee:
            send_msg._buf = struct.pack('<H', self.zigbee_id)
            pad = 2
        send_msg._buf += struct.pack('<Bh', 0x55, length)
        chk8 = chkCRC8(send_msg._buf[pad:pad+3])
        send_msg._buf += struct.pack('<BBBHBBB', chk8, self.sender, self.receiver, self.mac_addr, cmdtype, cmdset, cmdid)
        send_msg._buf += payload
        retry_count = self.retry_count
        chk16 = chkCRC16(send_msg._buf[pad:])
        send_msg._buf += struct.pack('<H', chk16)

        while retry_count > 0:
            retry_count -= 1
            if self.send(send_msg) == True:
                recv_msg = V1_msg()
                count = 0
                recv_count = 0
                while count < 10 and recv_count < 150:
                    n = recv_msg.bytes_expected()
                    try:
                        b = self.read(n)
                        if not b:
                            count += 1
                            continue
                        ret = recv_msg.add_with_slave(b, self.sender, 4)
                        if ret == 1:
                            (rtn, data) = self.special_handle_v1(recv_msg, cmdid)
                            count += 1
                            if False == rtn:
                                break
                            else:
                                return data
                        # receive package from master: switch it
                        elif ret == 2:
                            param_list = [{'type': 'u8', 'val': 0, 'param_id': 12505}]
                            payload = struct.pack("<H", 1)
                            for item in param_list:
                                payload += self.slave_set_param(item['type'], item['param_id'], item['val'])
                            self.send_reply_v1(recv_msg, payload, 0)
                            return None
                        else:
                            recv_count += 1
                    except:
                        return None
            logging.debug("Do retry")
        return None

    def send_reply_v1(self, recv_msg, payload, ack):
        time.sleep(0.002)
        send_msg = V1_msg()
        # 3Bytes: header length type
        length = (14 + len(payload)) | (0x01 << 10)
        send_msg._buf = struct.pack('<Bh', 0x55, length)
        chk8 = chkCRC8(send_msg._buf[0:3])
        # 9Bytes: crc8 sender receiver seqNum cmdset cmdid ack
        send_msg._buf += struct.pack('<BBBhBBBB', chk8, recv_msg.recver, recv_msg.sender(), 0, 0, 0, recv_msg.cmdID(), ack)
        send_msg._buf += payload
        chk16 = chkCRC16(send_msg._buf)
        send_msg._buf += struct.pack('<H', chk16)
        dump_hex(send_msg._buf)
        self.send(send_msg)

    def slave_set_param(self, type, param_id, val):
        buf = b''
        if type == 'f':
            buf = struct.pack("<Hf", param_id, val)
        elif type == 'u8':
            buf = struct.pack("<HB", param_id, val)
        elif type == 'i8':
            buf = struct.pack("<Hb", param_id, val)
        elif type == 'u16':
            buf = struct.pack("<HH", param_id, val)
        elif type == 'i16':
            buf = struct.pack("<Hh", param_id, val)
        elif type == 'u32':
            buf = struct.pack("<HI", param_id, val)
        elif type == 'i32':
            buf = struct.pack("<Hi", param_id, val)
        return buf

    def send_v2_cmd_to_mc(self, seq, cmdset, cmdid, payload):
        """
        1.use echo - reply mode: send and receive in the same loop with retry
        2.add robustness protection
        """
        send_msg = V1_msg()
        cmdtype = 0x01 << 5
        length = len(payload) + 13
        length = length | (0x01 << 10)
        send_msg._buf = struct.pack('<Bh', 0x55, length)
        chk8 = chkCRC8(send_msg._buf[0:3])
        send_msg._buf += struct.pack('<BBBhBBB', chk8, self.sender, self.receiver, seq, cmdtype, cmdset, cmdid)
        send_msg._buf += payload
        retry_count = self.retry_count
        chk16 = chkCRC16(send_msg._buf)
        send_msg._buf += struct.pack('<H', chk16)

        # support v2 protocol
        length = len(payload) + 13
        length = (length + 7) | (0x02 << 10)
        tmp_buf = struct.pack('<Bh', 0x55, length)
        chk8 = chkCRC8(tmp_buf[0:3])
        tmp_buf += struct.pack('<BB', chk8, self.dest_module_id)
        send_msg._buf = tmp_buf + send_msg._buf
        chk16 = chkCRC16(send_msg._buf)
        send_msg._buf += struct.pack('<H', chk16)
        # dump_hex(send_msg._buf)

        while retry_count > 0:
            if self.send(send_msg) == True:
                recv_msg = V1_msg()
                count = 0
                while True:
                    n = recv_msg.bytes_expected()
                    b = self.read(n)
                    if not b:
                        count += 1
                        if count > 3:
                            time.sleep(0.1)
                            break
                        continue
                    if recv_msg.addv2(b, self.sender):
                        (rtn, data) = self.special_handle_v2(recv_msg, cmdid)
                        if False == rtn:
                            break
                        else:
                            return data
            logging.debug("Do retry")
            retry_count -= 1
        return None

    def special_handle_v0(self, msg):
        val = msg.v0exchangeFeedback()
        return val

    def special_handle_v0_tcu(self, msg):
        val = {}
        ret = struct.unpack("<HHHHBbbBBbbBB", msg._buf[4:21])
        #logging.debug(ret)
        val["source_addr"] = ret[0]
        val["tcu_work_mode"] = ret[1]
        val["tcu_bit_status"] = ret[2]
        val["tcu_status"] = ret[3]
        val["bat_volt"] = ret[4]
        val["bat_current"] = ret[5]
        val["bat_temp"] = ret[6]
        val["sys_volt"] = ret[7]
        val["soc"] = ret[8]
        val["cur_angle"] = ret[9]
        val["target_angle"] = ret[10]
        val["acc_abs_max"] = ret[11]
        logging.debug(val)
        return (True, val)

    def receive_v0msg(self):
        msg = V1_msg()
        count = 0
        while True:
            n = msg.bytes_expected()
            b = self.read(n)
            if not b:
                count += 1
                if count > 3:
                    return (False, None)
                continue
                # return
            msg.addv0(b)
            if msg.v0valid():
                return self.special_handle_v0_tcu(msg)

    def send_v0_cmd_to_tcu(self, dest, cmdid, work_mode, time, latitude, longitude, altitude, target_angle, timezone):
        payload = struct.pack("<HHHIffhbb", dest, cmdid, work_mode, time, latitude, longitude, altitude, target_angle, timezone)
        return self.send_v0_cmd_to_mc(payload)

    def send_v0_cmd_to_mc(self, payload):
        send_msg = V1_msg()
        length = len(payload) + 6
        length = length | (0x00 << 10)
        send_msg._buf = struct.pack('<Bh', 0x55, length)
        chk8 = chkCRC8(send_msg._buf[0:3])
        send_msg._buf += struct.pack('<B', chk8)
        send_msg._buf += payload
        chk16 = chkCRC16(send_msg._buf)
        send_msg._buf += struct.pack('<H', chk16)
        retry_count = self.retry_count

        dump_hex(send_msg._buf)

        while retry_count > 0:
            if self.send(send_msg) == True:
                recv_msg = V1_msg()
                count = 0
                while True:
                    n = recv_msg.bytes_expected()
                    b = self.read(n)
                    if not b:
                        count += 1
                        if count > 3:
                            time.sleep(0.1)
                            break
                        continue
                    if recv_msg.addv0(b):
                        (rtn, data) = self.special_handle_v0_tcu(recv_msg)
                        if False == rtn:
                            break
                        else:
                            return data
            logging.debug("Do retry")
            retry_count -= 1
        return None

    def get_product_info(self):
        logging.info("Get Product Info")
        return self.send_v1_cmd_to_mc(0, 0, 0x0d, b'')

    def get_product_info_v2(self):
        logging.info("Get Product Info")
        return self.send_v2_cmd_to_mc(0, 0, 0x0d, b'')

    def get_version_info(self):
        logging.info("Get Version Info")
        return self.send_v1_cmd_to_mc(0, 0, 0x01, b'')

    def get_time_info(self):
        logging.info("Get Time Info")
        return self.send_v1_cmd_to_mc(0, 0, 0x33, b'')

    def set_time_info(self):
        logging.info("Set Time Info")
        payload = struct.pack("<IHBBBBB", 0, 2020, 1, 8, 10, 34, 00)
        return self.send_v1_cmd_to_mc(0, 0, 0x34, payload)

    def checksum(self, buf, len):
        sum = 0
        if len == 1:
            sum = buf[0]
            return sum & 0xffff

        for i in range(int(len/2)):
            val = buf[2*i] + (buf[2*i+1] << 8)
            sum += val
        if (len % 2):
            sum += buf[len - 1]
        while (sum>>16):
            sum = (sum & 0xffff) + (sum >> 16)
        return (sum & 0xffff)

TEST_DEV = 'COM5'
def test_get_productInfo():
    a = proto_dev(0x0c, 0x7, TEST_DEV, 9600, 1)
    a.get_product_info()
    a.close()

def test_get_productInfo_v2():
    a = proto_dev(0x0c, 0x7, TEST_DEV, 9600, 1)
    a.get_product_info_v2()

def test_get_version_Info():
    a = proto_dev(0x0c, 0x7, TEST_DEV, 115200, 0.01)
    a.get_version_info()

def test_reboot():
    a = proto_dev(0x0c, 0x7, TEST_DEV, 115200, 0.01)
    a.send_v1_cmd_to_mc(0, 0, 0xb, b'')

def test_get_time_info():
    a = proto_dev(0x0c, 0x7, TEST_DEV, 115200, 0.01)
    a.get_time_info()

def test_set_time_info():
    a = proto_dev(0x0c, 0x7, TEST_DEV, 115200, 0.01)
    a.set_time_info()

def test_sync_v0():
    a = proto_dev(0x0c, 0x7, TEST_DEV, 38400, 0.01)

    #dest, cmdid, work_mode, time, latitude, longitude, altitude, target_angle, timezone):
    a.send_v0_cmd_to_tcu(14, 0x1, 0x1, 1234, 120.3333, 30.123, 3000, 30, 8)

if __name__ == '__main__':
    import user_log
    user_log.user_log('1.log', logging.DEBUG)
    # a = 1234.56
    # b = struct.pack("<f", a)
    # dump_hex(b)
    # test_sync_v0()
    test_get_productInfo()
    # test_reboot()
    # #test_get_time_info()
    # #test_get_time_info()
    # #test_get_productInfo_v2()
