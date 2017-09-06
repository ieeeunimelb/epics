from window import *
from random import *
from time import sleep
import threading
import serial

def changeColor(leds,finish,ser):
    #flush input and output buffer, discarding all its contents
    ser.flushInput()
    ser.flushOutput()
    while not finish[0]:
        if ser.readable():
            command = ser.read(13)
            if command[0] == ord('s'):
                red = (command[2]-48)*100+(command[3]-48)*10+(command[4]-48)
                green = (command[5]-48)*100+(command[6]-48)*10+(command[7]-48)
                blue = (command[8]-48)*100+(command[9]-48)*10+(command[10]-48)
                color = (red,green,blue)
                leds[command[1]-48].turnOn(color)

def main():
    ser = serial.Serial()
    ser.baudrate = 9600
    ser.port = 'COM6'
    ser.timeout = 1
    ser.writeTimeout = 2
    ser.open()
    sleep(0.5)

    finish = [False]
    components = {}
    mainThread = threading.Thread(target=generateWindow,args=(components,finish,ser))
    mainThread.start()
    sleep(1)

    listeningThread = threading.Thread(target=changeColor,args=(components['LED'],finish,ser))
    listeningThread.start()

    mainThread.join()
    listeningThread.join()

if __name__ == "__main__":
    main()
