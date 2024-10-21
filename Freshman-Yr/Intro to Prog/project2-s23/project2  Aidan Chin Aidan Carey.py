from Inventory import Inventory
###############################
# Team members
# Name1: Aidan Carey
# Name2: Aidan Chin
###############################

# Modules
cart = Inventory(0)
inv = Inventory(0)
inv.initialize()
while True:
    Inventory.display_menu()
    inp = input("Enter Command: ")
    if inp == "": #exit Prog
        print("Goodbye!")
        break
    elif inp == "1": # list inventory
        print(inv)
    elif inp == '2': # Info inventory
        inv.info()
    elif inp == '3': #search inventory
        inv.search(input("Enter a title keyword: "))
    elif inp == '4':
        inv.add()
    elif inp == '5':
        inv.remove_item()
    elif inp =='6':
        percentage = float(input("Enter Inflation %"))
        inv.inflate(percentage)
    elif inp == '7':
        iden = int(input("which item do you want to buy? "))-1
        i = 0
        for Book in inv.list:
            if i == iden:
                print(f'"{Book.title}" added to shopping cart!')
                cart.add(Book)
                break
            i = i+1
    elif inp == '8':
        print("Current shopping cart")
        print(f"{cart}\n")
        cart.info()
        coupon = input("Enter your promotion code if any: ")
        if coupon == "Voyage":
            cart.inflate(-5)
            print("Updated Shopping cart:")
            print(f"{cart}\n")
            cart.info()
        if coupon == "Parfait":
            cart.inflate(-10)
            print("Updated Shopping cart:")
            print(f"{cart}\n")
            cart.info()
        input("Enter your credit card number: ")
        print("Purchase done!..Enjoy you new books")
