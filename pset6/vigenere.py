from cs50 import get_string
import sys

if len(sys.argv) > 2 or not sys.argv[1].isalpha():
    sys.exit(1)

plaintext = get_string("plaintext: ")

