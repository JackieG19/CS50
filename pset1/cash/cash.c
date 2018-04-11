//reviewed by LP (1 suggestion)

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;
    int coins = 0;
    int cents; // LP in my code I don't haave this i added int in the conversion
    do
    {
        dollars = get_float("Change owed: "); // ex. 0.32
    }
    while (dollars < 0);

    cents = round(dollars * 100); // converts $ into cents

    while (cents >= 25) // ex. 32 cent into 25 cent = yes = 1 coin
    {
        cents -= 25;
        coins++;
    }

    while (cents >= 10) // ex. 7 cent into 10 cent = no
    {
        cents -= 10;
        coins++;
    }
    while (cents >= 5) // ex. 7 cent into 5 cent = yes = 1 coin
    {
        cents -= 5;
        coins++;
    }
    while (cents >= 1) // ex. 2 cent into 1 cent = yes = 2 coin
    {
        cents -= 1;
        coins++;
    }
    printf("%i\n", coins); // ex. 0.32 = 4 coins
}

/*NOTES

input = value in $
convert $ into cent; $1 = 100 cent
round the amount = %

32c % 25c = 1 yes = 32c-25c = 7c
7c % 25c = no, 7c%10c = no
7c % 5c = 1 yes = 7c-5c = 2c
2c % 25c = no, 2c % 25c = no, 2c % 10c = no
2c % 1c = 2 yes = 2c-1c = 1c-1c = 0
*/