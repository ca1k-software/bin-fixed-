#tkinter module
from tkinter import * #import everything from tkinter
#->>Main
#->Initializing objects
pos = 1.0
calcsum = 1
mode = 0
#->Window
par = Tk()
mainpad = Frame(par)
numpad = Frame(mainpad)
opPad = Frame(mainpad)
par.title("Calculator")
io = Text(mainpad,width=25,height=1)
io.pack(fill=X)
#->textbox methods
def reset():
    global mode, calcsum
    io.delete(1.0,END)
    mode = 0
    calcsum = 1
def callbk(num):
    global pos
    io.insert(pos,num)
    pos += 1
def opcall(num):
    global calcsum, mode
    if num == 1:#add
        calcsum += int(io.get(1.0,END))-1
        io.delete(1.0,END)
        mode = 1
    if num == 2:#subtract
        calcsum -= int(io.get(1.0,END))-1
        io.delete(1.0,END)
        mode = 2
    if num == 3:#multiply
        calcsum *= int(io.get(1.0,END))
        io.delete(1.0,END)
        mode = 3
    if num == 4:#divide
        calcsum = int(io.get(1.0,END))
        io.delete(1.0,END)
        mode = 4
def evalcall(num):
    global calcsum
    if num == 1:#add
        calcsum += int(io.get(1.0,END))
        io.delete(1.0,END)
    if num == 2:#subtract
        calcsum -= int(io.get(1.0,END))
        io.delete(1.0,END)
    if num == 3:#multiply
        calcsum *= int(io.get(1.0,END))
        io.delete(1.0,END)
    if num == 4:#divide
        calcsum /= int(io.get(1.0,END))
        io.delete(1.0,END)
    io.insert(pos,calcsum)
#->formatting
mainpad.pack(fill=X)
numpad.pack(side=LEFT,ipadx=15)
opPad.pack(side=LEFT)
#->numpad buttons
b1 = Button(numpad,text="  1  ",command=lambda:callbk(1)).grid(row=1,column=0)
b2 = Button(numpad,text="  2  ",command=lambda:callbk(2)).grid(row=1,column=1)
b3 = Button(numpad,text="  3  ",command=lambda:callbk(3)).grid(row=1,column=2)
b4 = Button(numpad,text="  4  ",command=lambda:callbk(4)).grid(row=2,column=0)
b5 = Button(numpad,text="  5  ",command=lambda:callbk(5)).grid(row=2,column=1)
b6 = Button(numpad,text="  6  ",command=lambda:callbk(6)).grid(row=2,column=2)
b7 = Button(numpad,text="  7  ",command=lambda:callbk(7)).grid(row=3,column=0)
b8 = Button(numpad,text="  8  ",command=lambda:callbk(8)).grid(row=3,column=1)
b9 = Button(numpad,text="  9  ",command=lambda:callbk(9)).grid(row=3,column=2)
b0 = Button(numpad,text="  0  ",command=lambda:callbk(0)).grid(row=4,column=0)
bC = Button(numpad,text="  C  ",command=reset).grid(row=4,column=1)
#->opPad buttons
bAdd = Button(opPad,text="  +  ",command=lambda:opcall(1)).grid(row=1,column=0)
bSub = Button(opPad,text="  -  ",command=lambda:opcall(2)).grid(row=1,column=1)
bMult = Button(opPad,text="  *  ",command=lambda:opcall(3)).grid(row=2,column=0)
bDiv = Button(opPad,text="  /  ",command=lambda:opcall(4)).grid(row=2,column=1)
bDiv = Button(opPad,text="  =  ",command=lambda:evalcall(mode)).grid(row=3,column=0)


