/*
i think you have to do <<not isalpha()>> instead of <<isalpha()>> u have now.
it's recommended to use <<return 0 or return someNum>>  when using int main()
if (key < 0) -- good call. I'd do  if (key <= 0).
*/



#include<stdio.h>
#include<cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    string plaintext;

    if (argc != 2) // by default, argc will be 2 because ./caesar is the first argument
    {
        printf("Error\n");
        return 1; // stops progress, value of 1 returns error
    }
    int key = atoi(argv[1]);

    if (key < 0)
    {
        printf("Enter positive number after filename \n");
        return 1;
    }

    plaintext = get_string("plaintext: "); // string variable user input
    printf("ciphertext: ");
    char ciphertext; // looks text by charaters

    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        ciphertext = plaintext[i];

        if (isupper(plaintext[i])) // uppercase letters
        {
            ciphertext = (((plaintext[i] + key) - 65) % 26) + 65;
        }

        if (islower(plaintext[i])) // lowercase letters
        {
            ciphertext = (((plaintext[i] + key) - 97) % 26) + 97;
        }

        if (isalpha(plaintext[i]))
        {
            plaintext[i] = ciphertext;
        }

        printf("%c", ciphertext);
    }

    printf("\n");
}
