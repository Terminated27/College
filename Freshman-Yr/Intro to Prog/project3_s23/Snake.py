from tkinter import *
from Grid import Grid
from Pixel import Pixel
import time
#AidanChin  AidanCarey

### complete class Snake
class Snake(Grid):
    def __init__(self, root, obstacles, fruit, nrow, ncol, scale):
        super().__init__(root, nrow, ncol, scale)
        super().set_nrows(nrow)
        super().set_ncols(ncol)
        super().set_root(root)
        super().set_scale(scale)

        self.sturn = {}
        self.vector = [0, 1]
        self.obstacles = obstacles
        self.fruitnum = fruit
        
        self.fruit(self.fruitnum)
        self.obs(self.obstacles)
        
        self._pause = True

        self.slen = [[self.nrows//2, self.ncols//2,self.vector],
                     [self.nrows//2, self.ncols//2-1,self.vector],
                     [self.nrows//2, self.ncols//2-2,self.vector],
                     [self.nrows//2, self.ncols//2-3,self.vector]]

        self._game_over = False

        self.snake = []

        count = 0
        for part in self.slen: #make the  snake
            
            i, j = part[0], part[1]
            if count == 0:
                segment = Pixel(self.canvas, i, j, self.ncols, self.nrows, scale, 4)
            else:
                segment = Pixel(self.canvas, i, j, self.ncols, self.nrows, scale, 5)
            count = count + 1
            self.snake.append(segment)
            
    def fruit(self, fruit):
        super().random_pixels(fruit, 1)
        
    def obs(self, obs):
        super().random_pixels(obs, 3)
    def add_slen(self, i, j, vector):
        pix = [i, j, vector]
        self.slen.append(pix)
        
    def is_pause(self):
        return self._pause

    def pause(self):
        self._pause = not self._pause
        
    def next(self):
        sij = []
        for k in range(len(self.slen)):
            sij.append(tuple((self.slen[k][0], self.slen[k][1])))
            if sij[k] in self.sturn:
                turn = self.sturn[sij[k]]  # get the turn value for the current position
                if turn == -1:
                    self.slen[k][2] = [0, 1]  # change direction to right
                    del self.sturn[sij[k]]  # remove the turn from the grid
                elif turn == -2:
                    self.slen[k][2] = [-1, 0]  # change direction to up
                    del self.sturn[sij[k]]
                elif turn == -3:
                    self.slen[k][2] = [0, -1]  # change direction to left
                    del self.sturn[sij[k]]
                elif turn == -4:
                    self.slen[k][2] = [1, 0]  # change direction to down
                    del self.sturn[sij[k]]
            self.slen[k][0] += self.slen[k][2][0]  # update row coordinate
            self.slen[k][1] += self.slen[k][2][1]  # update column coordinate

        last_pixel = self.slen[-1]
        last_coords = [last_pixel[0], last_pixel[0]] 
        self.matrix[last_coords[0], last_coords[1]] = max(
            self.matrix[last_coords[0], last_coords[1]], 0
        )
        new_head_coords = [self.slen[0][0], self.slen[0][1]]
        if self.matrix[new_head_coords[0], new_head_coords[1]] == 3:
            self.slen.insert(0, Pixel(self.canvas, new_head_coords[0], new_head_coords[1], 
                                        self.nrows, self.ncols, self.scale, 6, self.slen[0][2])) # grow snake
            self.delxy(new_head_coords[1] * self.scale, new_head_coords[0] * self.scale) #move snake head
            self.fruitnum -= 1
        self.reset()            
        
        self.is_game_over()
        if self._game_over:
            if self.fruitnum == 0:
                print("YOU WON")
            else:
                print("GAME OVER")


        
    def is_game_over(self):
        if self.matrix[self.slen[0][0], self.slen[0][1]] == 1 or self.fruitnum == 0:
            self._game_over = True
        

# -1 to signal an allowed right turn, -2 an up turn, -3 a left turn and -4 a down       
    def right(self):
        if self.vector != [0, 1] or [0, -1]:
            self.vector = [0, 1]
            self.sturn[self.slen[0][0], self.slen[0][1]] = -1

    def left(self):
        if self.vector != [0, 1] or [0, -1]:
            self.vector = [0, -1]
            self.sturn[self.slen[0][0], self.slen[0][1]] = -3
    def down(self):
        if self.vector != [1, 0] or [-1, 0]:
            self.vector = [0, 1]
            self.sturn[self.slen[0][0], self.slen[0][1]] = -4
    def up(self):
        if self.vector != [1, 0] or [-1, 0]:
            self.vector = [0, -1]   
            self.sturn[self.slen[0][0], self.slen[0][1]] = -2    

        
    
        


#########################################################
############# Main code #################################
#########################################################
    

  
def main(): 
        
        ##### create a window, canvas 
        root = Tk() # instantiate a tkinter window
        #python = Snake(root,20,20) #20 obstacles, and 20 fruits
        python = Snake(root,5,5,25,25,30) # 5 obstacles/fruits, 25 row, 25 column, 30 scale
        
        
        ####### Tkinter binding mouse actions
        root.bind("<Right>",lambda e:python.right())
        root.bind("<Left>",lambda e:python.left())
        root.bind("<Up>",lambda e:python.up())
        root.bind("<Down>",lambda e:python.down())
        root.bind("<p>",lambda e:python.pause())
        
        while True:
            if not python.is_pause(): python.next()
            root.update()
            time.sleep(0.15)  # wait few second (simulation)
            if python.is_game_over(): break
            
        
        root.mainloop() # wait until the window is closed
        

if __name__=="__main__":
    main()

