from cs50 import get_int, get_string
import re

while True:
    cn = get_string("Number: ")
    if not re.search("\D", cn):
        break

cn = str(cn)[::-1]
sum = 0
for i in range(len(cn)):
    if i % 2 == 1:
        sum += 2*int(cn[i]) % 10
        sum += int(2*int(cn[i])/10)
    else:
        sum += int(cn[i])
if sum % 10 != 0:
    print("INVALID")
    quit()
if cn[-1] == "3" and (cn[-2] == "4" or cn[-2] == "7") and len(cn) == 15:
    print("AMEX")
elif cn[-1] == "5" and int(cn[-2]) >= 1 and int(cn[-2]) <= 5 and len(cn) == 16:
    print("MASTERCARD")
elif cn[-1] == "4" and (len(cn) == 13 or len(cn) == 16):
    print("VISA")
else:
    print("INVALID")
