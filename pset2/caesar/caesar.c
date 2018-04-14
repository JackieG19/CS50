#include<stdio.h>
#include<cs50.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    if (argc != 2) // by default, argc will be 2 because ./caesar is the first argument
    {
        printf("Error: Enter a postive number\n");
        return 1; // stops progress
    }
    int key = atoi(argv[1]);
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        char ciphertext;

        if (isalpha(plaintext[i]))
        {
            // int begin = 0; // beginning of the alphabet
            // int end = 0; // the end of the alpabet

            if (isupper(plaintext[i])) // uppercae letters
            {
                // begin = 'A';
                // end = 'Z';
                ciphertext = plaintext[i] + key;
                printf("%c", ciphertext);

            }

            else if (islower(plaintext[i])) // lowercase letters
            {
                // begin = 'a';
                // end = 'z';
                ciphertext = plaintext[i] + key;
                printf("%c", ciphertext);
            }
        }
    }
    printf("\n");
}