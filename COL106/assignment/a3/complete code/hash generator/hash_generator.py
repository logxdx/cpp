import random
import string

def generate_ifsc_account_strings(n):
    ifsc_account_strings = set()
    
    while len(ifsc_account_strings) < n:
        ifsc_char = ''.join(random.choices(string.ascii_uppercase, k=4))
        ifsc_dig = ''.join(random.choices(string.digits, k=7))
        ifsc = ifsc_char+ifsc_dig
        account_number = ''.join(random.choices(string.digits, k=10))
        ifsc_account_strings.add(f"{ifsc}_{account_number}")
    
    return list(ifsc_account_strings)

k = int(input("Number of id's : "))
unique_strings = generate_ifsc_account_strings(k)
with open("E:/CODE/C++/COL106/assignment/a3/complete code/hash generator/hash2.txt", 'w+') as f:
    for i, string in enumerate(unique_strings, 1):
        f.write(string+"\n")

