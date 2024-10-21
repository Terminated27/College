from tkinter import *
from Pixel import Pixel
import numpy as np
import random, time
#AidanChin AidanCarey


class Grid:

    def __init__(self, root, nrows, ncols, scale):
        self.set_nrows(nrows)
        self.set_ncols(ncols)
        self.set_scale(scale)
        self.set_root(root)

        self.__canvas = Canvas(self.__root,width=self.__ncols*scale,height=self.__nrows*self.__scale,bg="black") # create a canvas width*height
        self.__canvas.pack()
        self.__matrix = np.zeros((nrows,ncols), dtype=int) #make matrix for color of pixel @ each point
        self.__pix = np.empty_like(self.__matrix) #store the ID of each pixel, make more convienient to delete/ edit
        self.make_rows()
        
    def get_canvas(self):
        return self.__canvas
    def get_pix(self):
        return self.__pix
    
    def get_matrix(self):
        return self.__matrix
    
    def add_matrix(self, i, j, c):
        self.matrix[i, j] = c
        
        
    def set_nrows(self, nrows):
        self.__nrows = nrows
        
    def get_nrows(self):
        return self.__nrows
    
    def set_ncols(self, ncols):
        self.__ncols = ncols
        
    def get_ncols(self):
        return self.__ncols
    
    def set_scale(self, scale):
        self.__scale = scale
    
    def get_scale(self):
        return self.__scale
    
    def set_root(self, root):
        self.__root = root
        
    def get_root(self):
        return self.__root
    
    
    def make_rows(self):
        for i in range(self.__nrows): #plot using gray color
            for j in range(self.__ncols):
                w,x= j * self.__scale, i * self.__scale
                y,z= w * self.__scale, x * self.__scale
                self.__canvas.create_rectangle(w,x,y + self.__scale,z + self.__scale,outline='gray')

    def addij(self,i,j,c):
        if c > 0:
            pix = Pixel(self.__canvas, i, j, self.__nrows, self.__ncols, self.__scale, c)
            self.__pix[i, j] = pix.tag
            self.__matrix[i, j] = c

    def random_pixels(self,pixel_number,color):
        for _ in range(pixel_number):
            i=random.randint(0, self.__nrows-1) 
            j=random.randint(0, self.__ncols-1)
            self.addij(i, j, color)
        
    def addxy(self, x, y, c = 1):
        i = int(y / self.__scale)
        j = int(x / self.__scale)
        print("insert", y, x, j, i, self.__matrix[i, j])
        self.addij(i, j, c)

    def delij(self,i,j):
        if self.__matrix[i, j] != 0:
            self.__matrix[i, j] = 0
            self.reset()
        else:
            self.flush_row(i)
            
    def delxy(self, x, y):
        i = int(y / self.__scale)
        j = int(x / self.__scale)
        print("delete", y, x, j, i, self.__matrix[i, j])
        self.delij(i, j)

    def reset(self):
        self.__canvas.delete("all")
        self.make_rows()
        for i in range(self.__nrows):
            for j in range(self.__ncols):
                if self.__matrix[i, j] != 0:
                    self.addij(i, j, self.__matrix[i, j])


    def flush_row(self, i):
        pixs = []
        pixs.append(Pixel(self.__canvas, i, 0, self.__nrows, self.__ncols, self.__scale, 7, [0, 1]))
        pixs.append(Pixel(self.__canvas, i, self.__ncols - 1, self.__nrows, self.__ncols, self.__scale, 7, [0, -1]))

        print("Starting coords")
        for p in pixs:
            print(p)

        for _ in range(self.__ncols // 2):
            for p in pixs:
                p.next()  # move the pixel
            self.__root.update()  # update the graphic
            time.sleep(0.05)  # wait in seconds (simulation)

        print("Ending coords")
        for p in pixs:
            print(p)
            p.delete()

        for k in range(i - 1, -1, -1):
            for l in range(self.__ncols):
                self.__matrix[k + 1, l] = self.__matrix[k, l]
        self.__matrix[0, :] = 0
        self.reset()




            
            
            
    nrows = property(get_nrows, set_nrows)
    ncols = property(get_ncols, set_ncols)
    scale = property(get_scale, set_scale)
    root = property(get_root, set_root)
    pix = property(get_pix)
    matrix = property(get_matrix, add_matrix)
    canvas = property(get_canvas)


### To complete






#########################################################
############# Main code #################################
#########################################################


def main(): 
        
    ##### create a window, canvas 
    root = Tk()                # instantiate a tkinter window
    mesh = Grid(root,50,30,20) # instantiate a Grid object
    mesh.random_pixels(25,1)   # generate 25 random (white) pixels in the Grid

        
    ####### Tkinter binding mouse actions
    root.bind("<Button-1>",lambda e:mesh.addxy(e.x,e.y))
    root.bind("<Button-3>",lambda e:mesh.delxy(e.x,e.y))
    
    
        

    root.mainloop() # wait until the window is closed


if __name__=="__main__":
    main()

