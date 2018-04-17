#include<stdio.h>
#include<cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    string plaintext;
// if argument is not equal to 2 OR the first argument is equal to 0
    if (argc != 2 || strlen(argv[1]) == 0)
    {
        printf("Usage: ./vigenere k\n");
        return 1; // stops progress, returns error
    }
    string k = argv[1]; // first argument
    plaintext = get_string("plaintext: "); // string variable user input
    printf("ciphertext: "); // output
    int counter = 0; // value length of the string

    for (int i = 0, length = strlen(plaintext); i < length; i++) //strlen() function calculates the length of input.
    {
        int klength = strlen(k); // grabing the string length of k

        if (isalpha(plaintext[i]))
        {
            int key = k[counter] - 'A';
            if (isupper(plaintext[i]))
            {
                printf("%c", ((plaintext[i] - 'A' + k[key]) % 26) + 'A');
            }

            else
            {
                printf("%c", ((plaintext[i] - 'a' + k[key]) % 26) + 'a');
            }

            key = (key) % klength;
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}