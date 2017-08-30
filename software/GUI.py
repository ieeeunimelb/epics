from window import *
from random import *
from time import sleep
import threading
import serial

def changeColor(leds,finish):
    while not finish[0]:
        try:
            led = leds[randint(0,8)]
            if led.state == led.OFF:
                color = (randint(0,255),randint(0,255),randint(0,255))
                led.turnOn(color)
            else:
                led.turnOff()

            sleep(0.1)
        except:
            pass

def main():
    finish = [False]
    components = {}
    mainThread = threading.Thread(target=generateWindow,args=(components,finish))
    mainThread.start()
    sleep(1)

    listeningThread = threading.Thread(target=changeColor,args=(components['LED'],finish))
    listeningThread.start()

    mainThread.join()
    listeningThread.join()

if __name__ == "__main__":
    main()
