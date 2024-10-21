import math
'''
Aidan Chin 9/18/2023 Advanced Programming HW1 Q2

solves the monomial for x in the form ax - 2b = c and solves a polynomial for x in the form √(ax + 2b) = c 

'''





class Polynomial():
    def __init__ (self, a, b, c):
        
        self.a = self.intCheck(a, 'a')
        self.b = self.intCheck(b, 'b')
        self.c = self.intCheck(c, 'c')
        
    'solves monomial for inputs in form ax-2b=c'
    def monSolve(self):
        return (self.c-2*self.b) / self.a
        
    'solves polynomial for inputs in the form sqrt(ax+2b)=c'
    def polySolve(self):
        return (math.sqrt(self.c)-2*self.b) /  self.a
        
    'checks if input is really integer, if not prompts to get integer'
    def intCheck(self, intput, intname, isint = False):
        while not isint:
            try:
                intput = int(intput)
                isint = True
            except Exception:
                intput = input(f"please enter an integer value for {intname} : ")
                if intput.isdigit() == True:
                    continue
        return intput
    
a = input("input value of a: ")
b = input("input value of b: ")
c = input("input value of c: ")
function = Polynomial(a, b, c)
print(f"value of x in monomial form ax-2b=c, {function.a}x-2*{function.b}={function.c}")
print(function.monSolve())

print(f'value of x in polynomial form √(ax + 2b) = c, √({function.a}x + 2*{function.b}) = {function.c}')
print(function.polySolve())

