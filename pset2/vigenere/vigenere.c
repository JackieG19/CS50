/*
I'd put  wlength and klength vars into for loop declaration since u r not using them anywhere else in ur program.
like this: for (int i = 0, counter = 0, wlength = strlen(plaintext), klength = strlen(k); i < wlength; i++)
but it is a matter of taste.

return something from int main()

*/


#include<stdio.h>
#include<cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    string plaintext;
    string k = argv[1]; // first argument

    if (argc != 2) // if argument is not equal to 2
    {
        printf("Usage: ./vigenere k\n");
        return 1; // stops progress, returns error
    }
    {
        for (int i = 0, key = strlen(k); i < key; i++)// if key is valid will pass through
        {
            if (!isalpha(k[i])) // if not, will not pass and show error
            {
                printf("Error\n");
                return 1;
            }
        }
    }

    plaintext = get_string("plaintext: "); // string variable user input

    printf("ciphertext: "); // output

    int wlength = strlen(plaintext);

    int klength = strlen(k); // grabing the string length of k

    for (int i = 0, counter = 0; i < wlength; i++) // calculates the length of input.
    {
        int keyword = tolower(k[counter % klength]) - 'a'; // tracks occurrences of a character in the input

        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                printf("%c", (((plaintext[i] - 'A') + keyword) % 26) + 'A');
                counter++;
            }

            else
            {
                printf("%c", (((plaintext[i] - 'a') + keyword) % 26) + 'a');
                counter++;
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}
