from window import *
from random import *
from time import sleep
import threading
import logging
import serial

def changeColor(lists,leds,finish,ser):
    #flush input and output buffer, discarding all its contents
    ser.flushInput()
    ser.flushOutput()
    while not finish[0]:
        if len(lists)!=0:
            command = lists.pop(0)
            red = (command[2]-48)*100+(command[3]-48)*10+(command[4]-48)
            green = (command[5]-48)*100+(command[6]-48)*10+(command[7]-48)
            blue = (command[8]-48)*100+(command[9]-48)*10+(command[10]-48)
            color = (red,green,blue)
            leds[command[1]-48].turnOn(color)

def receiver(lists,finish,ser):
    while not finish[0]:
        if ser.readable():
            command = ser.read(12)
            logging.debug(command)
            if len(command) == 12 and command[0] == ord('s') and command[11] == ord('e'):
                lists.append(command)


def transmit(rotary,finish,ser):
    while not finish[0]:
        #construct the message
        ch = 'r'
        temp = rotary[0].checkValue()
        if temp == "EASY":
            ch += chr(1+48) + 'E'
        elif temp == "MEDIUM":
            ch += chr(1+48) + 'M'
        elif temp == "HARD":
            ch += chr(1+48) + 'H'
        else:
            ch += temp

        ch += chr(2+48) + chr(0+48) + chr(3+48) + chr(0+48)

        ch += 'e'
        #check if any state changed
        if ch[2] != chr(0+48) or ch[4] != chr(0+48) or ch[6] != chr(0+48):
            #print(ch)
            ser.write(ch.encode())


def main():
    logging.basicConfig(level=logging.DEBUG)
    #logger.setLevel(logging.DEBUG)
    ser = serial.Serial()
    ser.baudrate = 115200
    ser.port = 'COM10'
    ser.timeout = 1
    ser.writeTimeout = 2
    ser.open()
    sleep(0.5)
    lists = []

    finish = [False]
    components = {}
    mainThread = threading.Thread(target=generateWindow,args=(components,finish,ser))
    mainThread.start()
    sleep(0.5)

    transmitter = threading.Thread(target=transmit,args=(components['rotSwt'],finish,ser))
    transmitter.start()

    listener = threading.Thread(target=receiver,args=(lists,finish,ser))
    listener.start()

    led = threading.Thread(target=changeColor,args=(lists,components['LED'],finish,ser))
    led.start()

    mainThread.join()
    listener.join()
    transmitter.join()
    led.join()
    # while True:
    #     logging.debug("mainThread " + mainThread.isAlive())
    #     logging.debug("listener "+listener.isAlive())
    #     logging.debug("transmitter "+transmitter.isAlive())
    #     logging.debug("Led "+led.isAlive())
    #     sleep(1)

if __name__ == "__main__":
    main()
