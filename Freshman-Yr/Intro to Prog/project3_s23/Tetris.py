from tkinter import *
from Grid import Grid
from Tetrominoes import Tetrominoes
import numpy as np
import time
#AidanChin AidanCarey
class Tetris(Grid):
    def __init__(self):
        super().__init__(self)
        self.block=None
          
    def next(self):
        if self.block is None:
           return super().random_select()
        self.activate()       
    block=property(next)
    
    def down(self):
        self.vector = [1, 0]
        self.next()
        if self.nrow==40:
            self.vector=[0,0]
        else:
            pass
                  
    def is_overlapping(self,ii,jj):
        self.ii=ii
        self.jj=jj
        if self.ii or self.jj==0:
            return something
        
    def is_game_over():
        
    def pause():
        
    def is_pause():
        
        
        
    def up(self): #move up
        self.rotate()
                   
    def down(self): #move down
        if self.nrow!=40:
            return next()
        else: 
            self.vector = [0,0]
        
    def right(self): #change move vector to right
        self.vector = [0, 1]
        self.next()

    def left(self): #change move vector to left
        self.vector = [0, -1]
        self.next()    
    
        
   
    
#########################################################
############# Main code #################################
######################################################### 
def main():
    ##### create a window, canvas 
        root = Tk() # instantiate a tkinter window
        game=Tetris(root,36,12,25) 
        
        ####### Tkinter binding mouse actions
        root.bind("<Up>",lambda e:game.up())
        root.bind("<Left>",lambda e:game.left())
        root.bind("<Right>",lambda e:game.right())
        root.bind("<Down>",lambda e:game.down())
        root.bind("<p>",lambda e:game.pause())        

        while True:
            if not game.is_pause(): game.next()
            root.update()   # update the graphic
            time.sleep(0.25)  # wait few second (simulation)
            if game.is_game_over(): break
        
        root.mainloop() # wait until the window is closed  

if __name__=="__main__":
    main()

