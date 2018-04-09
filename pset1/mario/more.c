#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("enter a height between 0 - 23: ");
    }
    while
    (height < 0 || height > 23);

    for (int i = 0; i < height; i++)
    {
        for (int spaces = 0; spaces < (height - i - 1); spaces++)
        {
            printf(" "); // print space on the left side
        }

        for (int hashes = 0; hashes < (i + 1); hashes++)
        {
            printf("#"); // print hashes on the left
        }

        for (int space = 0; space < 2; space++)
        {
            printf(" "); //prints space on the right side
        }

        for (int hash = 0; hash < (i + 1); hash++)
        {
            printf("#"); //prints hashes on the right side
        }

        printf("\n");  // print new line = \n
    }
}