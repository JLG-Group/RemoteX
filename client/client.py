import numpy
import socket
from io import StringIO
import sys
import num

def create_socket():
     
    s = socket.socket()         # 创建 socket 对象
    host = socket.gethostname() # 获取本地主机名
    port = 12345                # 设置端口号 
    s.connect((host, port))
    while True:
        tmp = s.recv(1024)
    s.close()

create_socket()
