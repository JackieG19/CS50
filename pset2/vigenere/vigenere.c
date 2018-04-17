#include<stdio.h>
#include<cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    string plaintext;

    if (argc != 2 || strlen(argv[1]) == 0)
    {
        printf("Usage: ./vigenere k\n");
        return 1; // stops progress, value of 1 returns error
    }
    string k = argv[1];

    // if (!isalpha(k[counter]) // if it is no an alphabet
    // {
    //     printf("Error \n");
    //     return 1;
    // }

    plaintext = get_string("plaintext: "); // string variable user input
    printf("ciphertext: ");
    int counter = 0;
    //char ciphertext; // looks text by charaters

    for (int i = 0, length = strlen(plaintext); i < length; i++) //scramble mah eggs
    {
        int klength = 0;

        if (isalpha(plaintext[i]))
        {
            int key = k[counter] - 'A';
            if (isupper(plaintext[i])) //support for upper case
            {
                printf("%c", ((plaintext[i] - 'A' + key) % 26) + 'A');
            }

            else // if it's not upper it's lower....
            {
                printf("%c", ((plaintext[i] - 'a' + key) % 26) + 'a');
            }

            counter = (counter + 1) % klength; // kick/push k
        }
        else
        {
            printf("%c", plaintext[i]); //for all others
        }
    }
    printf("\n");
}