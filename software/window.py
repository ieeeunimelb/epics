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
    def __init__(self,master,block=None,serialObj = None,rotSwt = None,text = "     "):
        self.block = block  #block No
        self.handler = Button(master, text = text ,command=self.transmit)
        self.serialObj = serialObj
        self.rotSwts = rotSwt

    def getHandler(self):
        return self.handler

    def transmit(self):
        if self.block == 11:
            ch = 'b'+'r'
            for i in range(6):
                ch += 'e'
            self.serialObj.write(ch.encode())
        else:
            ch = 'b'+chr(self.block+48)
            for i in range(6):
                ch += 'e'
            self.serialObj.write(ch.encode())

class rotarySwitch:
    def __init__(self,master,no,value,serialObj = None):
        self.no = no;
        self.handler = Spinbox(master, values = value,width=10)
        self.previousValue = self.handler.get()

    def checkValue(self):
        presentValue = self.handler.get()
        if self.previousValue != presentValue:
            self.previousValue = presentValue
            return presentValue;
        else:
            #if it doesn't change
            return chr(1+48) + chr(0+48)

    def getHandler(self):
        return self.handler

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
        ledButtons.append(button(master,i,serialObj=serialObj))
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

    #create a seperator
    separator_2 = Frame(height=2, bd=10,width=300, relief=SUNKEN,bg='black')
    separator_2.grid(row=9,columnspan=3,pady=15)

    #the three rotary switch
    rotSwts = []
    VALUES = (("EASY","MEDIUM","HARD"),(4,5,6),(7,8,9))
    for i in range(3):
        rotSwts.append(rotarySwitch(master,i,VALUES[i],serialObj))
        rotSwts[i].getHandler().grid(row=10,column=i)

    separator_3 = Frame(height=2, bd=10,width=300, relief=SUNKEN,bg='black')
    separator_3.grid(row=11,columnspan=3,pady=15)

    #the action and reset button
    action = button(master,block=10,text="ACTION",serialObj=serialObj)
    action.getHandler().grid(row=8,column=0)
    reset = button(master,block=11,text="REST",rotSwt =rotSwts,serialObj=serialObj)
    reset.getHandler().grid(row=8,column=2)

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
