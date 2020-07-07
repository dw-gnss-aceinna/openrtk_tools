# -*- coding: utf-8 -*-
import os
import sys
from ftplib import FTP
import ftplib
import gzip
import time
import datetime
import zlib
import zipfile
import unlzw
from queue import Queue

def un_gz(localpath,file_name):
	file_now = localpath + '/' + file_name
	print("file_now = %s" % file_now)
	f_name = file_now.replace(".gz", "")
	g_file = gzip.GzipFile(file_now)
	open(f_name, "wb+").write(g_file.read())
	g_file.close()


def decompress_z(localpath,file_name):
	src = localpath + '/' + file_name
	my_dst = src[0:-2]
	uc_func = unlzw.unlzw if src.endswith('.Z') else gzip.decompress
	with open(src, 'rb') as sf, open(my_dst, 'wb') as df:
		buffer = sf.read()
		df.write(uc_func(buffer))

def ftpConnect(ftpserver, port, usrname, password):
    ftp = FTP()
    try:
        ftp.connect(ftpserver, port)
        ftp.login(usrname, password)
    except:
        raise IOError(' FTP connection failed, please check the code!')
    else:
        print(ftp.getwelcome())
        print('+------- ftp connection successful!!! --------+')
        return ftp


def ftpDownloadFile(ftp, ftpfile, localfile):
    bufsize =  1024
    with open(localfile, 'wb') as fid:
        ftp.retrbinary('RETR {0}'.format(ftpfile), fid.write, bufsize)
    return True


def ftpDownload(ftp, ftpath, localpath):
    print('ftp_path: {0}'.format(ftpath))
    if not os.path.exists(localpath):
        os.makedirs(localpath)
    try:
        ftp.cwd(ftpath)
    except ftplib.error_perm:
        print ('error cannot cd to %s' % (ftpath) )
        return False
    print('+---------- downloading ----------+')
    for file in ftp.nlst('-a', '.'):
        #print('file = --------------------%s' % file)
        if 'BRDC00IGS_R' in file:
            local = os.path.join(localpath, file)
            print('local = ---------------------%s' % local)
            if os.path.isdir(file):
                if not os.path.exists(local):
                    os.makedirs(local)
                ftpDownload(ftp, file, local)
            else:
                ftpDownloadFile(ftp, file, local)
                decompress_z(localpath,file)
        else:
            continue
    ftp.cwd('..')
    #ftp.quit()
    return True


def ftpDisConnect(ftp):
	try:
		ftp.quit()
	except:
		print("close error")
'''         
def file_search(root_dir,signle_search):
    print ('start file search')
    for root,dirs,files in os.walk(root_dir):
        if signle_search == True:
            return dirs,files
'''
def file_search(root_dir):
	print ('start file search')
	file_path_list = []
	for root,dirs,files in os.walk(root_dir):
		for filename in files:
			if ('novatel' in filename) and ('.bin' in filename):
				filepath = os.path.join(root, filename)
				file_path_list.append(filepath)
	return file_path_list
		

def get_utc_day(time_list):
	'''
	year = int(time.strftime("%Y"))
	month = int(time.strftime("%m"))
	day = int(time.strftime("%d"))
	hour = int(time.strftime("%H"))
	minute = int(time.strftime("%M"))
	second = int(time.strftime("%S"))
	'''
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
	#print(str(utc_st))
	utc_year_str = (str(utc_st))[0:4]
	utc_day_int = int(utc_str.split( )[0])
	utc_day_str = str(utc_day_int + 1)

	return utc_day_str,utc_year_str


def to_width(old_value):
	value = int(old_value)
	if value < 10:
		ret = str("00%d" % value)
	elif value < 100:
		ret = str("0%d" % value)
	else:
		ret = old_value
	return ret

def ephemeris_download(thread_name,span_path,queue):
	print(span_path)
	ftpserver = 'cddis.gsfc.nasa.gov' 
	#ftp://198.118.242.40/pub/gps/data/daily/2020/184/20p/
	ftpserver = 'cddis.nasa.gov'
	ftpserver = '198.118.242.40'
	port = 21
	usrname = ''
	pwd = ''
	localpath = './data/'
	#dir,files = file_search('./',False)
	file_list = file_search(span_path)
	print(file_list)
	path_list = []
	for file in file_list:
		path_list.append(os.path.dirname(file))
	print (path_list)
	for i in range(len(path_list)):
		print("select file is: %s" % file)
		file_time = file_list[i][-23:-4]
		time_list = file_time.split('_')
		utc_day,utc_year = get_utc_day(time_list)
		utc_day = to_width(utc_day)
		print("utc_day = %s,utc_year = %s" % (utc_day,utc_year))
		ftpath = 'pub/gps/data/daily/' + utc_year + '/' + utc_day + '/' + utc_year[2:] + 'p/'
		localpath = path_list[i] + '/' + 'ephemeris/'
		print (localpath)
		print(ftpath)
		ftp = ftpConnect(ftpserver, 21, usrname, pwd)
		flag = ftpDownload(ftp, ftpath, localpath)
		ftpDisConnect(ftp)
		if flag == False:
			print("+-------- FAILED!!! --------+\n")
		else:
			print("+-------- OK!!! --------+\n")
	queue.put("ftp_end")

