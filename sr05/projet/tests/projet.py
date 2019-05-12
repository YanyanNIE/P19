#!/usr/bin/python3

from sys import stdin, stdout, stderr, argv
import select
import tkinter as tk
from tkinter import ttk
from threading import Thread

class Interface(tk.Frame):
    def __init__(self, parent, *args, **kwargs):
        tk.Frame.__init__(self, parent, *args, **kwargs)
        self.parent = parent

        tk.Label(parent, text="Reçu: ").pack()
        self._in = tk.StringVar()
        tk.Label(parent, textvariable=self._in).pack()

        ttk.Separator(parent)

        tk.Label(parent, text="Envoyer: ").pack()

        self._out = tk.Entry(parent)
        self._out.pack()

        tk.Button(parent, text="Envoyer", command=self.envoyer).pack()

        #Run "recevoir"
        self._thread = Thread(target=self.recevoir)
        self._thread.start()

    def envoyer(self):
        value = self._out.get()
        stdout.write(value)

    def recevoir(self):
        # Source: https://repolinux.wordpress.com/2012/10/09/non-blocking-read-from-stdin-in-python/
        value = ""
        while stdin in select.select([stdin], [], [], 0)[0]:
            line = stdin.readline()
            if line: value += line

        self._in.set(value)

    def __del__(self):
        self._thread.join(timeout=0)

def envoyer():
    while(True):
        stdout.write("*")
        sleep(1)

def recevoir():
    # Source: https://repolinux.wordpress.com/2012/10/09/non-blocking-read-from-stdin-in-python/
    while(True):
        value = ""
        while stdin in select.select([stdin], [], [], 0)[0]:
            line = stdin.readline()
            if line: value += line

        if value != "": print(value)

if __name__ == "__main__":
    """root = tk.Tk()
    Interface(root).pack(side="top", fill="both", expand=True)
    root.mainloop()"""

    thread1 = Thread(target=recevoir)
    thread1.start()

    thread2 = Thread(target=envoyer)
    thread2.start()
