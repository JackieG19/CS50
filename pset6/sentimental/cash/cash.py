from cs50 import get_float

while True:
        print("How much change is owed?")
        amount = get_float()
        if amount >= 0:
            break

coins = 0
cents = round(amount * 100) # $1.00

coins += cents // 25
cents %= 25

coins += cents // 10
cents %= 10

coins += cents // 5
cents %= 5

coins += cents

print("number of coins = ", coins)








