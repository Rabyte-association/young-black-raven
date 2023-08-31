import threading
import GamepadAccess
import socket 
from time import sleep
import pickle

import math
class toSend:
    dirX = 0        
    dirY = 0
    dirR = 0
    camX = 0
    camY = 0
    def __bytes__(self):
        return

Data = toSend()
pad=GamepadAccess.padObj()

class passThroughClass:
    dane= '0'
passThrough = passThroughClass()

DeadZone = 0.15


def sockets():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
    print(f"Connecting to:")

    sock.connect((str("10.42.0.1"), int(8766)))

    print("connected", sock.getsockname())
    
    while True:
        pickled = passThrough.dane
        #print(pickled)
        sock.sendall(pickled)
        sleep(0.05)


def padding():
    while True:
        #pad.ShowDebug()
        if abs(pad.leftAxis.x)>DeadZone:
            Data.dirX = -pad.leftAxis.x*255
        else:
            Data.dirX = 0
        if abs(pad.leftAxis.y)>DeadZone:
            Data.dirY = pad.leftAxis.y*255
        else:
            Data.dirY = 0
        if abs(pad.rightAxis.x)>DeadZone:
            Data.dirR = pad.rightAxis.x*255
        else:
            Data.dirR = 0

        passThrough.dane = pickle.dumps(Data)
        sleep(0.05)



controllerThread = threading.Thread(target = pad.Initialize)
controllerThread.start()
socketsThread = threading.Thread(target=sockets)
socketsThread.start()
paddingThread = threading.Thread(target=padding)
paddingThread.start()


