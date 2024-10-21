###############################
# Team members- Please enter your names here
# Name1: Aidan Chin
# Name2: Aidan Carey
###############################

def display_menu():
    """Display the list of polynomial available tools"""
    print("1-Insert; 2-Remove; 3-Info; 4-Evaluate; 5-Scaling; 6-Derive; 7-Integrate")
    print("8-Summation; 9-Subtract; 10-Multiply; 11-Divide")

def display_list(list_poly):
    for i in range(len(list_poly)):
        print(f"{i+1}: {get_expression(list_poly[i])}")

def get_polynomial():
    # gets the polynomial length and coefficients
    i = 0
    coef = []
    deg = int(input("Degree of polynomial? ")) + 1
    while i < deg:
      coef.append(input("Enter coef. of x^%s: "%(i)))
      i = i + 1
    return coef

def get_expression(p):

    poly = ""
    i = 0
    while i < len(p):
        if p[i] == 0:
            pass
        elif i == 0:
            poly = poly +str(p[i])
        elif (i == 1) & (p[i] > 0):
            poly = poly +("+%sx"%(p[i]))
        elif (i == 1) & (p[i] < 0):
            poly = poly +(f"{p[i]}x")
        elif p[i] < 1:
            poly = poly +("-%sx^%s"%(p[i],i))
        elif p[i] > 1:
            poly = poly +("+%sx^%s"%(p[i],i))
        i = i + 1
    if poly == "":
        poly = "0.0"
    return poly

def del_expression(poly):
    #deletes a polynomial from the list
    if len(poly) == 0:
        print("There are no polynomials to remove.")
        return
    delnum = input("Which polynomial would you like to remove?")
    del poly[int(delnum)-1]
    return poly

def info(poly):

    for i in range(len(poly)):
        odd = 0
        even = 0
        j = 1
        k = 0
        while poly[-1] == 0:
            del(poly[-1])
        degree = len(poly)-1
        while j < len(poly):
            odd = odd + abs(int(poly[j]))
            j = j + 2
        while k < len(poly):
            even = even + abs(int(poly[k]))
            k = k + 2
        if even == 0:
            return f"Degree is {degree} and it is odd"
        if odd == 0:
            return f"Degree is {degree} and it is even"
        elif (odd != 0) & (even != 0):
            return f"Degree is {degree}"
        
def evaluate(coeffs, x):
    value = 0
    for i in range(len(coeffs)):
        value = value + coeffs[i]*(x**i)
    return value

def scale(x1,x2):
    if x2==0.0:
        return [0.0]
    for i in range(len(x1)):
        x1[i]=x1[i]*x2 
    return x1

def derive(p1):
    if len(p1)<=1:
        return [0.0]
    p2=p1
    del p2[0]
    for i in range(len(p2)):
        p2[i]=p2[i]*(i+1)
    return p2

def integrate(coeff, low, up):
    a = 0
    p1 = []
    p2 = []
    for i in range(len(coeff)):
        coeff[i] = coeff[i]/(i+1)
        p1.append(coeff[i]*low**(i+1))
        p2.append(coeff[i]*up**(i+1))
        a = a + p2[i] - p1[i]
    return a
        
def add(pol1,pol2):
    pol3=[]
    if len(pol1) > len(pol2):
        for i in range(len(pol2)):
            pol3.append(pol1[i] + pol2[i])
        pol3.extend(pol1[len(pol2):])
    elif len(pol1) < len(pol2):
        for i in range(len(pol1)):
            pol3.append(pol1[i] + pol2[i])
        pol3.extend(pol2[len(pol1):])
    else:
        for i in range(len(pol2)):
            pol3.append(pol1[i] + pol2[i])
    for i in range(len(pol3)):
        if pol3[-1] == 0.0:
            del(pol3[-1])
        else:
            return pol3

def subtract(pol1,pol2):
    neg=[]
    pol3=[]
    if pol1 == pol2:
        return [0.0]
    for i in range(len(pol2)):
        neg.append(0-pol2[i])
    if len(pol1) > len(neg):
        for i in range(len(neg)):
            pol3.append(pol1[i] + neg[i])
        pol3.extend(pol1[len(neg):])
    elif len(pol1) < len(neg):
        for i in range(len(pol1)):
            pol3.append(pol1[i] + neg[i])
        pol3.extend(neg[len(pol1):])
    else:
        for i in range(len(neg)):
            pol3.append(pol1[i] + neg[i])
    for i in range(len(pol3)):
        if pol3[-1] == 0.0:
            del(pol3[-1])
        else:
            return pol3
        
def multiply(poly1, poly2):
    result = [0] * (len(poly1) + len(poly2) - 1)
    for i in range(len(poly1)):
        for j in range(len(poly2)):
            result[i+j] += poly1[i] * poly2[j]
    while result[-1] == 0:
        if len(result) > 1:
            del(result[-1])
        else:
            return result
    return result
