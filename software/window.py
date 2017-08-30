from tkinter import *
import serial

#a LED class which creates a LED object
class led:
    def __init__(self,master,serialObj = None):
        self.ON = 0
        self.OFF = 1
        self.state = self.OFF
        self.handler = Canvas(master, width=100, height=100)
        #cannot pack the widget here otherwise we cannot grid it in the main function
        #self.handler.pack()
        self.rect = self.handler.create_rectangle(10, 10,100,100,fill='black')
        self.serialObj = serialObj

    def turnOn(self,color):
        color = '#%02x%02x%02x' % color
        self.handler.itemconfig(self.rect, fill=color)
        self.state = self.ON

    def turnOff(self):
        self.state = self.OFF
        self.handler.itemconfig(self.rect, fill='black')

    def getHandler(self):
        return self.handler

class button:
    def __init__(self,master,led=None,serialObj = None,text = "     "):
        self.led = led  #led num
        self.handler = Button(master, text = text ,command=self.transmit)
        self.serialObj = serialObj

    def getHandler(self):
        return self.handler

    def transmit(self):
        self.serialObj.write()
        #do serial communication

class rotarySwitch:
    def __init__(self,master,value,serialObj = None):
        self.handler = Spinbox(master, values = value,width=10)
        self.previousValue = self.handler.get()

    #this function should be invoked in every loop
    def checkValue(self):
        presentValue = self.handler.get()
        if self.previousValue != presentValue:
            self.previousValue = presentValue
            self.transmit()

    def getHandler(self):
        return self.handler

    def transmit(self):
        pass
        #self.handler.get()
        #do serial communication

#this method takes a dict and fills it with
#lists of 9 LEDs, 9 buttons, action button, reset button and 3 rotary switches
#{"root","LEDS","buttons","action","reset","rotSwt"}
def generateWindow(components,finish,serialObj):
    master = Tk()
    #the 9 LEDs and 9 buttons
    leds = []
    ledButtons = []
    for i in range(9):
        leds.append(led(master,serialObj))
        ledButtons.append(button(master,i+1,serialObj=serialObj))
        if i<3:
            leds[i].getHandler().grid(row = 0,column = i)
            ledButtons[i].getHandler().grid(row=1,column = i)
        elif i>=3 and i<6:
            leds[i].getHandler().grid(row = 3,column = i-3)
            ledButtons[i].getHandler().grid(row=4,column = i-3)
        else:
            leds[i].getHandler().grid(row = 5,column = i-6)
            ledButtons[i].getHandler().grid(row=6,column = i-6)

    #create a seperator
    separator_1 = Frame(height=2, bd=10,width=300, relief=SUNKEN,bg='black')
    separator_1.grid(row=7,columnspan=3,pady=15)

    #the action and reset button
    action = button(master,text="ACTION",serialObj=serialObj)
    action.getHandler().grid(row=8,column=0)
    reset = button(master,text="REST",serialObj=serialObj)
    reset.getHandler().grid(row=8,column=2)

    #create a seperator
    separator_2 = Frame(height=2, bd=10,width=300, relief=SUNKEN,bg='black')
    separator_2.grid(row=9,columnspan=3,pady=15)

    #the three rotary switch
    rotSwts = []
    VALUES = ((1,2,3),(4,5,6),(7,8,9))
    for i in range(3):
        rotSwts.append(rotarySwitch(master,VALUES[i],serialObj))
        rotSwts[i].getHandler().grid(row=10,column=i)

    separator_3 = Frame(height=2, bd=10,width=300, relief=SUNKEN,bg='black')
    separator_3.grid(row=11,columnspan=3,pady=15)

    #update the components
    components['LED'] = leds
    components['buttons'] = ledButtons
    components['action'] = action
    components['reset'] = reset
    components['rotSwt'] = rotSwts

    master.mainloop()
    finish[0] = True
    #power button
    #mainSwitch = Button(master,text="POWER",command=lambda: loop(master))
    #mainSwitch.grid(row=3,column=4)
