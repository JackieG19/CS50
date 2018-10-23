from cs50 import get_string
import sys

if len(sys.argv) == 2:
    key = int(sys.argv[1])
    plaintext = get_string("plaintext: ")

    # for(ct = 0; ct => pt.length; ct++)
    for ciphertext in range(len(plaintext)):
        if plaintext[ciphertext].isupper():
            print (chr(((ord(plaintext[ciphertext]) - 65) + key) % 26 + 65), end="")

        elif plaintext[ciphertext].isalpha():
            print (chr(((ord(plaintext[ciphertext]) - 97) + key) % 26 + 97), end="")

        else:
            print(ciphertext, end="")

    print()