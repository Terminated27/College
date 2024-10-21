from song import Song
from binary_search_tree import BinarySearchTree
from stack import Stack


class MyPlayer:
    def __init__(self):
        """
        initializes parameters in MyPlayer
        songList is a list
        is_sorted is boolean
        yearMemory is Dict
        playHistory is Stack
        :return:
        nothing
        """
        self.songList = []
        self.is_sorted = False
        self.yearMemory = {}
        self.playHistory = Stack()
        # TODO: Modify the above attribute for Task 6

    def loadLibrary(self, filename): # load library into songList, putting them into the song object
        """
        Loads a library from the given filename into the songList, creating Song objects for each song.
        Args:
            filename (str): The name of the file to load the library from.
        """

        with open(filename,'r') as file:
            data = file.read().replace('\n','|')
        params = list(data.split('|'))
        for i in range(len(params)//5):
            self.songList.append(Song( params[i*5], params[1+(i*5)], params[(i*5)+2], params[i*5+3], params[i*5+4]))

    def quickSort(self):
        """
        sorts the list of songs by publish year
        :return:
        nothing
        """
        self.quickSortHelper(self.songList,0,len(self.songList)-1)
        
        
        # TODO: Sort your songList here...
        self.is_sorted = True
        
        
    def quickSortHelper(self, alist, first, last):
        '''
        splits the list into 1 len lists in order,
        combines the lists
        '''
        if first < last:
            splitpoint = self.partition(alist, first, last)
            
            self.quickSortHelper(alist, first, splitpoint-1)
            self.quickSortHelper(alist, splitpoint + 1, last)

    def partition(self, alist, first, last):
        '''
        partitions the lists into sorted values until len 1 list
        
        returns 
        
        the number out of place in the list
        '''
        
        pivotvalue = self.songList[first].year
        
        leftmark = first + 1
        rightmark = last
        
        while True:
            while leftmark <= rightmark and alist[leftmark].year <= pivotvalue:
                leftmark = leftmark + 1
            
            while alist[rightmark].year >= pivotvalue and rightmark >= leftmark:
                rightmark  = rightmark - 1      

            if rightmark < leftmark:
                break
            else:
                temp = alist[leftmark]
                alist[leftmark] = alist[rightmark]
                alist[rightmark] = temp
                
        temp = alist[first]
        alist[first] = alist[rightmark]
        alist[rightmark] = temp
        
        return rightmark

    def playSong(self, title):
        """
        finds and prints out details of song desired to be found
        :param title:
        is the title that the song needs to match to be considered found
        :return:
        a string describing the song being played
        """
        for i in self.songList:
            if i.song_title == title:
                i.play()
                self.playHistory.push(i)
                


    def getLastPlayed(self):
        """
        finds the last played song
        :return:
        returns details of the last played song
        """
        
        return self.playHistory.peek()

    def buildYearMemory(self):
        """
        builds data structure in hashtable( dict ) full of songs, by year published
        :return:
        nothing
        """
        for i in self.songList:
            if i.year not in self.yearMemory:
                self.yearMemory[i.year] = BinarySearchTree()
        for i in self.songList:
            if i.year in self.yearMemory:
                self.yearMemory[i.year].put(i.song_title, i)


    def getYearMemory(self, year, title):
        """
        gets the song by the year it was published from binary search
        :param year:
        it is the year of publish for the song, used to find key in dict
        :param title:
        it is title of the song, used to find place in binary search tree
        :return:
        """
        the_song = None
        steps = 0  # Number of steps used to search for the song
        the_song, steps = self.yearMemory[year].get(title, steps)

        
            


        # TODO: Search for the song, note, you are NOT allowed to use self.songList in this method
        # TODO: You can assume self.buildYearMemory is already called, no need to call it here

        # Do not modify the return line, assign proper values for
        # steps and song above
        return {"steps": steps, "song": the_song}

    def getSong(self, year, title):
        """
        uses linear search to find song in songlist
        :param year:
        year song published, used to verify correct song title
        :param title:
        title of song, used to find the song details from list
        :return:
        """
        
        steps = 0  # Number of steps used to search for the song
        the_song = None
        for i in self.songList:
            steps += 1
            if i.song_title == title and i.year == year:
                the_song = i
                break



        # TODO: Search for the song, Note, you are NOT allowed to use self.yearMemory in this method

        # Do not modify the return line, assign proper values for
        # steps and song above
        return {"steps": steps, "song": the_song}


# NO MORE TESTING CODE BELOW!
# TO TEST YOUR CODE, MODIFY test_my_player.py
