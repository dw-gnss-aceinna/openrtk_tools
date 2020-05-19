import signal
import argparse
import _thread
import azure_download
import ftp_download
from queue import Queue

import time
import os 

def get_args():
	parser = argparse.ArgumentParser()
	parser.description = argparse.ArgumentParser(description='span args command:')
	parser.add_argument("--storage_name", type=str, help="my storagename")
	parser.add_argument("--storage_key", type=str, help="my storagekey")
	parser.add_argument("--span_path", type=str, help="span file path")
	parser.add_argument("--base", type=str, help="is download base data",choices=['yes','no'])
	parser.add_argument("--ephemeris", type=str, help="is download ephemeris data",choices=['yes','no'])
	return parser.parse_args()


def set_cmd_para():
    args = get_args()

    para_dict = {"storage_name": "","storage_key": "","span_path": "","base": "","ephemeris":""}
    if args.storage_name == None:	
        print ("please input your storage name")
        storage_name = input()
    else:
        storage_name = args.storage_name
    para_dict["storage_name"] = storage_name
    if args.storage_key == None:
        print ("please input your storage key")
        storage_key = input()
    else:
        storage_key = args.storage_key
    para_dict["storage_key"] = storage_key
    if args.span_path == None:
        print ("please input your span path")
        span_path = input()
    else:
        span_path = args.span_path
    para_dict["span_path"] = span_path

    if args.base == None:
        print ("is download base data? yes or no")
        base_download = input()
    else:
        base_download = args.base
    para_dict["base"] = base_download

    if args.ephemeris == None:
        print ("is download ephemeris data? yes or no")
        ephemeris_download = input()
    else:
        ephemeris_download = args.ephemeris
    para_dict["ephemeris"] = ephemeris_download
    return para_dict


def kill_app(signal_int,call_back):
    print ('exit app')
    os.kill(os.getpid(),signal.SIGINT)

if __name__ == '__main__':
    signal.signal(signal.SIGINT,kill_app)
    para_dict = set_cmd_para()
    print (para_dict)
    base_run_queue = Queue(maxsize=1000)
    ephemeris_run_queue = Queue(maxsize=1000)
    
    if para_dict["ephemeris"] == 'yes':
        _thread.start_new_thread(ftp_download.ephemeris_download,("ephemeris_thread",para_dict["span_path"],ephemeris_run_queue))
    if para_dict["base"] == 'yes':
        _thread.start_new_thread(azure_download.base_download,("base_thread",para_dict["span_path"],para_dict["storage_name"],para_dict["storage_key"],base_run_queue))

    base_queue_mes = ''
    ephemeris_queue_mes = ''
    base_run_flag = False
    ephemeris_run_flag = False
    while True:
        try:
            base_queue_mes = base_run_queue.get_nowait()
        except:
            pass
        try:
            ephemeris_queue_mes = ephemeris_run_queue.get_nowait()
        except:
            pass
        if(ephemeris_queue_mes == 'ftp_end'):
            ephemeris_run_flag = True
            print(ephemeris_queue_mes)
        if(base_queue_mes == 'azure_end'):
            base_run_flag = True
            print(base_queue_mes)
        if(ephemeris_run_flag == True) and (base_run_flag == True):
            print("exit")
            exit()
        time.sleep(5)