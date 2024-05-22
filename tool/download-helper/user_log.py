# -*- coding: utf-8 -*-
import logging
import sys

class user_log:
    def __init__(self, log_filename, console_log_level):
        logging.basicConfig(
                level    = logging.DEBUG,
                format   = '%(asctime)s - %(message)s',
                datefmt  = '%d-%b-%y %H:%M:%S',
                filename = log_filename,
                filemode = 'a')
        console = logging.StreamHandler(sys.stdout)
        console.setLevel(console_log_level)
        # set a format which is simpler for console use
        formatter = logging.Formatter('%(asctime)s - %(module)s - %(lineno)-4d : %(levelname)-8s %(message)s')
        # tell the handler to use this format
        console.setFormatter(formatter)
        logging.getLogger('').addHandler(console)

if __name__ == '__main__':
    user_log('1.log', logging.INFO)
    logging.info('Hello Tristan')
    logging.debug('Hello Debug')
