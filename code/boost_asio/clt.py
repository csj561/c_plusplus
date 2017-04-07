#! /usr/bin/python
# -*- coding: UTF-8 -*-

import socket,time,thread
port = 11111
ip = "10.0.2.111"

sock_list=[]
for i in range(100):
    sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM,0)
    sock.connect((ip,port))
    print "connect success!!!"
    sock_list.append(sock)
    #sock.shutdown(socket.SHUT_WR)
    sock.setblocking(False)
def send(t):
    l = 0
    while(True):
        for s in sock_list:
            str="sock[%d]: aaa_%08d" % (s.fileno(),l)
            try:
                s.send(str)
            except Exception, e:
                pass
            l+=1
        time.sleep(1)
def recv(t):
    while(True):
        for s in sock_list:
            try:
                str=s.recv(100)
                print str
            except Exception, e:
                pass
            
        time.sleep(0.5)
thread.start_new_thread(send,(1,))
thread.start_new_thread(recv,(1,))
time.sleep(10000)
