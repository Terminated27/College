from Book import Book

class Inventory:
    def __init__ (self,list = []):
        self.list = []
    def initialize(self):
        #fills inventory object with a set of 10 books
        self.list.append(Book("A Brief History of Time", "S. Hawking", "GV5N32M9", 10.17))
        self.list.append(Book("The Alchemist", "P. Coelho", ' TR3FL0EW', 6.99))
        self.list.append(Book('Thus Spoke Zarathustra', ' F. Nietzsche',  'F2O9PIE9', 7.81))
        self.list.append(Book('Jonathan Livingston Seagull', ' R. Bach', ' R399CED1', 6.97))
        self.list.append(Book('The Time Machine', 'H. G. Wells', '6Y9OPL87', 5.95))
        self.list.append(Book('Introduction to Programming in Python','R. Sedgewick', '5T3RRO90', 69.99))
        self.list.append(Book('Atoms of Silence', 'H. Reeves','3W2TB162',28.02))
        self.list.append(Book('2001: A Space Odyssey', 'A. C. Clarke', 'TU2RL012', 8.99))
        self.list.append(Book('20,000 Leagues under the Sea', 'J. Verne', 'JI2PL986', 5.99))
        self.list.append(Book(' Les Miserables', 'V. Hugo', 'VC5CE249', 9.98))
    def __str__ (self):
        #printout of all books 
        out = ""
        for i in range (len(self.list)):
            out += f"{i+1} - {self.list[i]}\n"
        return out
    def display_menu():
        print("Welcome to Bestmedia")
        print("====================\n-------------------------------------------------------")
        print("1-List Inventory; 2-Info Inventory; 3-Search Inventory") 
        print("4-Add Item; 5-Remove Item; 6-Inflation; 7-Shop; 8-Check-out")
    def info(self, tot=0):
        #find total number of all books
        print(f"#Items: {len(self.list)}") 
        #find total cost of all books
        for Book in self.list:
            tot = tot + float(Book.price) 
        print(f"Total price ${tot}") 
        #find most expensive book
        high = 0
        for Book in self.list:
            if high <= float(Book.price): #in book thing again
                high = float(Book.price)
        print(f"Most expensive item at ${high}")
    def search(self, keyword):
        # create list of books that match the keyword
        results = []
        i = 0
        for Book in self.list:
            if keyword.lower() in Book.title.lower():
                results.append(f"{i+1} - {self.list[i]}")
            i=i+1
        if len(results) == 0:
            print("No book found!")
        else:
            for i in range(len(results)):
                print(results[i])

    def add(self,book = None):
        if book == None:
            title=input("Enter Title: ")
            author=input("Enter Author Name: ")
            price=input("Enter Price: ")
            ref=input("Enter Reference: ")
            self.list.append(Book(title,author,ref,price))
        else:
            self.list.append(book)

    def remove_item(self):
        item_number = int(input("which item do you want to delete: "))
        del self.list[item_number-1]
      
    def inflate(self, percentage):
        for Book in self.list:
            Book.price *=(1+float(percentage) / 100)
