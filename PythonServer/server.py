import pickle
from time import sleep
from serial import Serial
import socket
import threading

class toSend:
    dirX = 0           #zmiana stanu ledow => Select
    dirY = 0
    dirR = 0
    camX = 0
    camY = 0
    def __bytes__(self):
        return

class DataHold:
    data = ""

datahold = DataHold()
datahold.data = ""
picoID = '0'

def InitializeSocket(PORT):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(('10.42.0.1', PORT))
    print(f"elo, {s.getsockname()}")
    while True:
        s.listen()
        conn, addr = s.accept()
        print('Connected by', addr)
        while True:
            try:
                datahold.data = conn.recv(4096)
                if datahold.data == b'':
                    break
            except:
                print('server error')
                break
        datahold.data = b''

def InitializeACM(): # xiao do jazdy, pico do strzalow
    serialpico = Serial(port='/dev/ttyACM'+picoID, baudrate=115200, timeout=None)
    while True:
        if len(datahold.data)>2:
            #print(datahold.data)
            try:
                decoded = pickle.loads(datahold.data)
                serialpico.write(bytes('x' + str(decoded.dirX), 'utf-8'))
                serialpico.write(bytes('y' + str(decoded.dirY), 'utf-8'))
                serialpico.write(bytes('r' + str(decoded.dirR), 'utf-8'))
                serialpico.write(bytes('p' + str(decoded.camX), 'utf-8'))
                serialpico.write(bytes('t' + str(decoded.camY), 'utf-8'))


            except:
                print("err")
                decoded = b''
            

if __name__ == "__main__":
    acm = threading.Thread(target=InitializeACM)
    acm.start()

    port = threading.Thread(target=InitializeSocket, args=[8766])
    port.start()
