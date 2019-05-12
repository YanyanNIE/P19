#!/usr/bin/python3

from time import sleep
from threading import Thread
import threading
from sys import stdin, stdout, stderr, argv
import select

import io

lock = threading.Lock()

def envoyer():
    while(True):
        lock.acquire()

        print("Ceci est une phrase.")
        stdout.flush()

        lock.release()

        sleep(1)

def recevoir():
    # Source: https://repolinux.wordpress.com/2012/10/09/non-blocking-read-from-stdin-in-python/

    while(True):
        lock.acquire()
        
        value = ""
        while stdin in select.select([stdin], [], [], 0)[0]:
            line = stdin.readline()
            if line: value += line

        if value != "": stderr.write("LU: "+value+"\n")
        
        lock.release()


if __name__ == "__main__":
    thread2 = Thread(target=envoyer)
    thread2.start()

    thread1 = Thread(target=recevoir)
    thread1.start()
