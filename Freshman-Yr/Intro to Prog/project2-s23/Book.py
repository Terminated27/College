class Book:
    ## to complete
    def __init__ (self,title,author,ref,price):
        self.title = title
        self.author = author
        self.price = price
        self.ref = ref
    def __str__ (self):
        return f"Title: {self.title}; Author: {self.author}; (Ref: {self.ref}; Price: ${self.price})"




def main():
    book1=Book("A Brief History of Time","Stephen Hawking",10.17,"GV5N32M9")
    print(book1)

if __name__=="__main__":
    main()
