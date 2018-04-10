/*
    Comments by Pascal Laurent
    ==========================
    I like the code. Lots of comments helping other programmers to read and understand the code
    Adding the Note at the top would be more helpful. I would also add comments explaining what
    the program does.
*/
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    do
    {
        // input: heights [0,23] less than 0, more than 23
        height = get_int("enter a height between 0 - 23: ");
    }
    while // (height < 0 && height > 23);
    (height < 0 || height > 23); // combine 2 boolean expression

    for (int i = 0; i < height; i++)
    {
        for (int spaces = 0; spaces < (height - i - 1); spaces++)
        {
            printf(" "); // print space
        }

        for (int hashes = 0; hashes < (i + 2); hashes++)
        {
            printf("#"); // print height
        }

        printf("\n");  // print new line = \n
    }
}


/*NOTES

valid input: height [0 - 23]
invalid input: < 0 - > 23

[ boolean 1 ] [ boolean 2 ] [ boolean 1 && 2 ] [ boolean 1 || 2 ]
    F             F              F                  F
    F             T              F                  T
    T             F              F                  T
    T             T              T                  T

find pattern: nth row = prints how many # and space
*/