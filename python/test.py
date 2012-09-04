from Tkinter import *  
 
class HilbertPeano(Frame):  
      
    beginning = 1 
    anticlockwise = 1 
    startX = 0 
    startY = 0 
    level = 7 
 
    def __init__(self, master=None):  
         Frame.__init__(self, master)  
         self.grid()  
         self.createWidgets()  
 
    def createWidgets(self):  
         self.quitButton = Button(self, text="QUIT", command=self.quit)  
         self.quitButton.pack(side=BOTTOM, fill=BOTH)  
         self.draw = Canvas(self, width=800, height=600)  
         self.draw.pack(side=LEFT)  
         self.drawCanvas(self.level, -(self.anticlockwise), 100,50,700,550)  
 
    def drawCanvas(self, level, direction, x1, y1, x2, y2):  
         dx = x2-x1  
         dy = y2-y1  
         if (level == 1 ):  
             self.lineTo((x1+dx/4),(y1+dy/4))  
             self.lineTo((x1+dx/4+(1-direction)*dx/4),(y1+dy/4+(1+direction)*dy/4))  
             self.lineTo((x1+3*dx/4),(y1+3*dy/4))  
             self.lineTo((x1+dx/4+(1+direction)*dx/4),(y1+dy/4+(1-direction)*dy/4))  
         else :  
            if (direction == self.anticlockwise) :  
                 self.drawCanvas(level-1,-direction,x1,y1,(x1+x2)/2,(y1+y2)/2)  
                 self.drawCanvas(level-1,direction,x1,(y1+y2)/2,(x1+x2)/2,y2)  
                 self.drawCanvas(level-1,direction,(x1+x2)/2,(y1+y2)/2,x2,y2)  
                 self.drawCanvas(level-1,-direction,x2,(y1+y2)/2,(x1+x2)/2,y1)  
            else :  
                 self.drawCanvas(level-1,-direction,x1,y1,(x1+x2)/2,(y1+y2)/2)  
                 self.drawCanvas(level-1,direction,(x1+x2)/2,y1,x2,(y1+y2)/2)  
                 self.drawCanvas(level-1,direction,(x1+x2)/2,(y1+y2)/2,x2,y2)  
                 self.drawCanvas(level-1,-direction,(x1+x2)/2,y2,x1,(y1+y2)/2)  
              
 
      
    def lineTo (self, endX, endY) :  
        if (self.beginning == 1) :  
             self.beginning=0 
        else :  
             self.draw.create_line(self.startX,self.startY,endX,endY)  
        self.startX = endX  
        self.startY = endY  
 
 
 
app = HilbertPeano()  
app.master.title("HilbertPeano (recursive)")  
app.mainloop() 
