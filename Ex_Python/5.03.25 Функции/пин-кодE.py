#пин-код Е
import math
def check_pin(pinUser):
    el1, el2, el3 = pinUser
    for i in range(2, int(int(pinUser[0])(0.5)) + 1):
        if int(pinUser[0]) % i == 0:
            return "Некорректен"
    if (pinUser[1] != pinUser[1][::-1]) or (int(math.log2(int(pinUser[2]))) != math.log2(int(pinUser[2]))):
        return "Некорректен"
    return "Корректен"

pinUser = input().split("-")
print(check_pin(pinUser))
