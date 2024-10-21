"""
Aidan Chin 9/18/2023 Advanced Programming HW1 Q1

converts the number of seconds into days, hours, minutes, seconds.
E.g., for the input 100000 seconds the output is 1 day, 3 hours, 46 minutes, 40 seconds.
"""
class Hw1Q1:
    'converts time from seconds into a more readable format'
    @staticmethod
    def timeConvert(input_second):
        minutes = input_second // 60
        seconds = input_second % 60
        hours = minutes // 60
        minutes = minutes % 60
        days = hours // 24
        hours = hours % 24

        output = ""
        if days > 0:
            output += f"{days} day{'s' if days > 1 else ''}"
            if hours == minutes == seconds == 0:
                return output
            output +=", "
        if hours > 0:
            output += f"{hours} hour{'s' if hours > 1 else ''}"
            if minutes == seconds == 0:
                return output
            output +=", "
        if minutes > 0:
            output += f"{minutes} minute{'s' if minutes > 1 else ''}"
            output +=", "
            if seconds == 0:
                return output
        output += f"{seconds} second{'s' if seconds > 1 else ''}"
        return output
    "checks to make sure the input is valid, to prevent errors"
    @staticmethod
    def intCheck():
        while True:
            user_input = input("Enter time in seconds to be converted: ")
            if user_input.isdigit():
                user_input = int(user_input)
                if user_input > 0:
                    return user_input  # Return the validated integer
                else:
                    print("Please enter a positive integer.")
            else:
                print("Invalid input. Please enter a positive integer.")


if __name__ == "__main__":
    Hw1Q1.timeConvert()
"""uns code and computes answer
input_second = Hw1Q1.intCheck()
output = Hw1Q1.timeConvert(input_second)
print(output)"""