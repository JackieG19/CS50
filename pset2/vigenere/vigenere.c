#include<stdio.h>
#include<cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    string plaintext; // var stores user message
    string key = argv[1]; // variable stores key
    int lastchar = 0; // last character examined
    int counter = 0;

    if (argc != 2) // validate arguments
    {
        printf("Usage: ./vigenere k\n");
        return 1; // value of 1 returns error
    }

    for ( int i = 0; i < strlen(key); i++) // make sure keyword is from A-Z
    {
        if (!isalpha(argv[1][i])) // if it is not alphabetical
        {
            printf("Enter an alphabetical chars\n"); // tells the user to enter a letter
            return 1;
        }
    }
    do // loops through as long as message is NULL or empty
    {
        plaintext = get_string("plaintext: "); // get message from user

    }while(plaintext == '\0'); // loop through message and manipulate string

    for (int i = 0, j = strlen(plaintext); i < j; i++)
    {
        if (isalpha(plaintext[i]))
        {
            counter = lastchar % strlen(key); // set counter to modulo length of keyword

            if (islower(plaintext[i])) // preserve lowercase
            {
                if (islower(key[counter]))
                {
                    plaintext[i] = ((plaintext[i] - 'a' + key[counter] - 97) % 26) + 97;
                    printf("%c", plaintext[i]);
                }
                else
                {
                    plaintext[i] = ((plaintext[i] - 'a' + key[counter] - 65) % 26) + 97;
                    printf("%c", plaintext[i]);
                }
            }

            if (isupper(plaintext[i])) // preserve uppercase
            {
                if (islower(key[lastchar]))
                {

                    plaintext[i] = ((plaintext[i] - 'A' + key[counter] - 97) % 26) + 65;
                    printf("%c", plaintext[i]);
                }
                else
                {
                    plaintext[i] = ((plaintext[i] - 'A' + key[counter] - 65) % 26) + 65;
                    printf("%c", plaintext[i]);
                }

            }
            lastchar++; // increment last characters by 1
        }
        else
        {
            printf("%c", plaintext[i]); // print encryted message
        }
    }
    printf("\n");
    return 0;
}