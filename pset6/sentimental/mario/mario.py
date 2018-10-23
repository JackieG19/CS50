import cs50

while True:
    print("Height: ", end = "")
    height = cs50.get_int()
    if height >= 0 and height <= 23:
        break

for i in range(height):
    for j in range(height - i - 1):
        print(" ", end = "")
    for k in range(i+2):
        print("#", end = "")
    print("")

# mario in python