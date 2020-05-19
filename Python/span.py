import argparse
import _thread
import azure_download
import ftp_download
from queue import Queue
import signal
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
    print ('kill app')
    os.kill(os.getpid(),signal.SIGTERM)


if __name__ == '__main__':
    signal.signal(signal.SIGTERM,kill_app)
    para_dict = set_cmd_para()
    print (para_dict)
    base_run_queue = Queue(maxsize=1000)
    ephemeris_run_queue = Queue(maxsize=1000)
    if para_dict["ephemeris"] == 'yes':
        _thread.start_new_thread(ftp_download.ephemeris_download,("ephemeris_thread",para_dict["span_path"],base_run_queue))
    if para_dict["base"] == 'yes':
        _thread.start_new_thread(azure_download.base_download,("base_thread",para_dict["span_path"],para_dict["storage_name"],para_dict["storage_key"],ephemeris_run_queue))
    
    while True:
        str1 = base_run_queue.get()
        str2 = ephemeris_run_queue.get()
        if(str1 == 'ftp_end'):
            flag1 = 1
        if(str2 == 'azure_end'):
            flag2 = 1
        if(flag1 == 1) and (flag2 == 1):
            print("all")
            exit()
        time.sleep(5)