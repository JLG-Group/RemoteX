import time

import cv2
import mss
import numpy

import socket

from io import StringIO
import numpysocket;


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


def main():
    npSocket = numpysocket.NumpySocket();
    screen_capture()

main();
