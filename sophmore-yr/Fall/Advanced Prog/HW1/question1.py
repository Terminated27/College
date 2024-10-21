"""
Aidan Chin 9/18/2023 Advanced Programming HW1 Q1

converts the number of seconds into days, hours, minutes, seconds.
E.g., for the input 100000 seconds the output is 1 day, 3 hours, 46 minutes, 40 seconds.
"""

class Hw1Q1:
    def __init__(self, seconds = 0, minutes = 0, hours = 0, days = 0):
        self.input_second = self.intCheck(seconds)
        self.minutes = int(minutes)
        self.hours = int(hours)
        self.days = int(days)
    
    'converts seconds into days, hours, minutes and seconds using simpleConvert() command'    
    def timeConvert(self, input_second):
        seconds, minutes = self.simpleConvert(input_second, minutes, 60)
        minutes, hours = self.simpleConvert(minutes, hours, 60)
        hours, days = self.simpleConvert(hours, days, 24)
        return f"{days} days, {hours} hours, {minutes} minutes, {seconds} seconds"

    'converts one type of time into another using the ratio between them'
    def simpleConvert(self, con_from, con_to, ratio):
        con_to = con_from // ratio
        con_from = con_from % ratio
        return con_from, con_to
    
    'checks if input is really integer, if not prompts to get integer'
    def intCheck(self, intput, isint = False):
        while not isint:
            try:
                intput = int(intput)
                isint = True
            except Exception:
                intput = input("please enter an integer: ")
                if intput.isdigit() == True:
                    continue
        return intput

'gets input from user and prints out the answer'
input_second = input("Enter a time in seconds to convert into days, hours, minutes, seconds format: ")
time = Hw1Q1(input_second)
print(time.timeConvert())
