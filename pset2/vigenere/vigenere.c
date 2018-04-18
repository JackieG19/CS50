#include<stdio.h>
#include<cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    string plaintext;
// if argument is not equal to 2 OR the first argument is equal to 0
    if (argc != 2)
    {
        printf("Usage: ./vigenere k\n");
        return 1; // stops progress, returns error
    }
    string k = argv[1]; // first argument

    plaintext = get_string("plaintext: "); // string variable user input

    printf("ciphertext: "); // output

    int wlength = strlen(plaintext);

    int klength = strlen(k); // grabing the string length of k

    for (int i = 0, counter = 0; i < wlength; i++) //strlen() function calculates the length of input.
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