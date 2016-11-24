import socket
import time
from threading import Thread

UDP_IP = "127.0.0.1"
UDP_PORT = 5005
MESSAGE = "Hello, World!"

def listen(sock):
    while True:
        sock.bind((UDP_IP, UDP_PORT))
        data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
        print "received message:", data

def outgoing(sock):
    while True:
        sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
        time.sleep(1)

if __name__ == '__main__':
    sock = socket.socket(socket.AF_INET, # Internet
                         socket.SOCK_DGRAM) # UDP

    IOout = Thread(target=outgoing, args=(sock,))
    IOin = Thread(target=listen, args=(sock,))

    IOout.start()
    IOin.start()
