import time

import cv2
import mss
import numpy

import socket

from io import StringIO

s = socket.socket()
host = socket.gethostname() 
port = 12345                # 设置端口
s.bind((host, port))

img = numpy.array(0)

def screen_capture():
    with mss.mss() as sct:
        # Part of the screen to capture
        monitor = {"top": 0, "left": 0, "width": 320, "height": 320}

        while "Screen capturing":
            last_time = time.time()
            t0 = time.time();
            # Get raw pixels from the screen, save it to a Numpy array
            img = numpy.array(sct.grab(monitor))
            print(type(img));

            # Display the picture
            cv2.imshow("OpenCV/Numpy normal", img)

            # Display the picture in grayscale
            # cv2.imshow('OpenCV/Numpy grayscale',
            #            cv2.cvtColor(img, cv2.COLOR_BGRA2GRAY))

            #print("fps: {}".format(1 / (time.time() - last_time)))
            print(time.time() - t0)

            # Press "q" to quit
            if cv2.waitKey(25) & 0xFF == ord("q"):
                cv2.destroyAllWindows()
                break


def create_socket():
    s.listen(5)                 # 等待客户端连接
    while True:
        c,addr = s.accept()     # 建立客户端连接
        print('连接地址：', addr)
        c.send(img.tostring())
    c.close()     

def main():
    create_socket()
    screen_capture()

main();
