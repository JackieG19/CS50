#include<stdio.h>
#include<cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    string plaintext;

    if (argc != 2 || strlen(argv[1]) == 0) // by default, argc will be 2 because ./caesar is the first argument
    {
        printf("Usage: ./vigenere k\n");
        return 1; // stops progress, value of 1 returns error
    }
    int key = (argv[1]);
    int klength = strlen(k);

    // if (key < 0)
    // {
    //     printf("Enter positive number after filename \n");
    //     return 1;
    // }

    plaintext = get_string("plaintext: "); // string variable user input
    printf("ciphertext: ");
    char ciphertext;
    int counter = 0;

    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        ciphertext = plaintext[i];

        if (isupper(plaintext[i])) // uppercase letters
        {
            ciphertext = (((plaintext[i] + key) - 65) % 26) + 65;// key counter
        }

        if (islower(plaintext[i])) // lowercase letters
        {
            ciphertext = (((plaintext[i] + key) - 97) % 26) + 97;
        }

        if (isalpha(plaintext[i])) // skip num when hashing
        {
            plaintext[i] = ciphertext;
        }

        printf("%c", ciphertext);
    }

    printf("\n");
}