# -*- coding: utf-8 -*-
from azure.storage.blob import BlockBlobService
import os
import time
import datetime
#from utc import get_utc_day,file_search

def get_utc_day(time_list):
	year = int(time_list[0])
	month = int(time_list[1])
	day = int(time_list[2])
	hour = int(time_list[3])
	minute = int(time_list[4])
	second = int(time_list[5])
	local_time = datetime.datetime(year, month, day, hour, minute, second)
	time_struct = time.mktime(local_time.timetuple())
	utc_st = datetime.datetime.utcfromtimestamp(time_struct)
	d1 = datetime.datetime(year, 1, 1)
	utc_sub = utc_st - d1
	utc_str = utc_sub.__str__()
	print(str(utc_st))
	utc_year_str = (str(utc_st))[0:4]
	utc_day_int = int(utc_str.split( )[0])
	utc_day_str = to_width(str(utc_day_int + 1))

	utc_hour_str = (str(utc_st))[-8:-6]
	print(utc_hour_str)
	return utc_day_str,utc_year_str,utc_hour_str
	
def file_convbin_file(file_to_search,root_dir):
	for root,dirs,files in os.walk(root_dir):
		for filename in files:
			if (file_to_search in filename):
				return os.path.join(root, filename)
	
def downloadFilesInContainer(local_path,blob_service,blobContainName,utc_year,utc_day,utc_hour):
	dir = utc_year + '/' + utc_day
	file_save_list = []
	print(dir)
	generator = blob_service.list_blobs(blobContainName,dir)
	print("utc_hour = %d" % int(utc_hour))
	base_min = chr(int(utc_hour[1:2]) + 97)
	base_max = chr(int(utc_hour[1:2]) + 104)
	print("base_min = %s" % base_min)
	if not os.path.exists(local_path):
		os.makedirs(local_path)
	for blob in generator:
		if ('wx02' in blob.name) and (blob.name[-6] >= base_min) and (blob.name[-6] < base_max):
			blobDirName =  os.path.dirname(blob.name)
			print("blob.name = %s" % blob.name)
			'''
			newBlobDirName = os.path.join(blobContainName, blobDirName)
			if not os.path.exists(newBlobDirName):
				os.makedirs(newBlobDirName)
			'''
			local_file_name = os.path.join(local_path, os.path.basename(blob.name))

			print("local_file_name = %s" % local_file_name)
			file_save_list.append(local_file_name)
			blob_service.get_blob_to_path(blobContainName, blob.name, local_file_name)
		else:
			continue
	all_file_name = utc_year + '_' + utc_day + '_' + utc_hour + '.bin'
	all_file_name_path = os.path.join(local_path, all_file_name)
	fs = open(all_file_name_path,'ab')
	#rtcm3_file = 'rtcm3_data_' + utc_year + '_' + utc_day + '_' + utc_hour
	convbin_path = file_convbin_file('convbin.exe','./')

	print(file_save_list)
	for file in file_save_list:
		fs_to_read = open(file,'rb')
		data = fs_to_read.read()
		fs.write(data)
	fs.close()
	if convbin_path == None:
		return
	try:
		date = utc_year + '/' + utc_day + '/' + utc_hour
		cmd = os.path.abspath(convbin_path) + ' ' + os.path.abspath(all_file_name_path) + ' -r rtcm3' + ' -tr ' + date + ' 00:00:00  -v 3.04'
		print(cmd)
		os.system(cmd)
	except:
		pass


def to_width(old_value):
	value = int(old_value)
	if value < 10:
		ret = str("00%d" % value)
	elif value < 100:
		ret = str("0%d" % value)
	else:
		ret = old_value
	return ret

def file_search(root_dir):
	print ('start file search')
	file_path_list = []
	for root,dirs,files in os.walk(root_dir):
		for filename in files:
			if ('novatel' in filename) and ('.bin' in filename):
				filepath = os.path.join(root, filename)
				file_path_list.append(filepath)
	return file_path_list


if __name__ == '__main__':
	mystoragename = "virtualmachinesdiag817"
	#mystoragekey = "JKDLzWW4KcbmpeF9RDLZWemHOXcTTCwO/DHDYQ/h94Gx4NAiqa/s2xqn26NShnWfD7vN0UyJnURZ5kEhN/jXlw=="
	print('input your key:')
	key = input()
	mystoragekey = key
	blob_service = BlockBlobService(account_name=mystoragename, account_key=mystoragekey)

	containerGenerator = blob_service.list_containers()
	marker = None
	for con in containerGenerator:
		time_list = []
		if 'base-station' in con.name:
			file_list = file_search('./')
			print(file_list)
			path_list = []
			for file in file_list:
				path_list.append(os.path.dirname(file))
			print (path_list)
			for i in range(len(path_list)):
				file_time = file_list[i][-23:-4]
				time_list = file_time.split('_')
				print(time_list)
				utc_day,utc_year,utc_hour = get_utc_day(time_list)
				print("utc_day = %s,utc_year = %s,utc_hour = %s" % (utc_day,utc_year,utc_hour))
				localpath = path_list[i] + '/' + 'base/'
				downloadFilesInContainer(localpath,blob_service,con.name,utc_year,utc_day,utc_hour)













