#include<stdio.h>
#include<cs50.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    if (argc != 2) // by default, argc will be 2 because ./caesar is the first argument
    {
        printf("Error: Enter a postive number\n");
        return 1; // stops progress, value of 1 returns error
    }
    int key = atoi(argv[1]);
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        char ciphertext;

        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i])) // uppercae letters
            {
                ciphertext = ((plaintext[i] - 65 + key) % 26) + 65; //- 'A' + key) % 26) + 'A';
                printf("%c", ciphertext);
            }

            else if (islower(plaintext[i])) // lowercase letters
            {
                ciphertext = ((plaintext[i] - 97 + key) % 26) + 97; // - 'a' + key) % 26) + 'a';
                printf("%c", ciphertext);
            }
        }
    }
    printf("\n");
}