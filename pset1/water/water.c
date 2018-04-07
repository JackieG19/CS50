#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int minutes;
    int bottles = 12 ;

    do
    {
        minutes = get_int("minutes: ");
        bottles = minutes * 12;
    }
    while (minutes < 0);
    {
        //minutes++;
        //bottles = get_int();
        printf("minutes: %i\n", minutes);
        printf("bottles: %i\n", bottles);
    }

}
// printf("bottles per minutes: 12\n");
// int bottles = 12;
// printf("minutes: \n");
// int minutes = get_int();
// int result = minutes * bottles;
// printf("%i :total bottles\n", result);

// NOTE
/*
1 min = 12 bottles = 1x12 = 12
2 min = 24 bottles = 2x12 = 24
5 mn = 60 bottles = 5x12 = 60
the pattern: 12 x minutes = total bottles
*/
