#include<stdio.h>
#include<cs50.h>
#include <string.h>
//#include <ctype.h>


int main(int argc, string argv[])
{
    //argc = 2; // by default, argc will be 2 because ./caesar is the first argument
    //if (!argv[1] || argc > 2)
    if (argc != 2)
    {
        printf("Error: Enter a postive number\n");
        return 1; // stops progress
    }
    //char text;
    //int key = atoi(k); // ./caesar 2, key is a integer
    int key = atoi(argv[1]) % 26;
    //string k = argv[1]; // after ./caesar
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(plaintext[i]))
        {
            int begin = 0; // beginning of the alphabet
            int end = 0; // the end of the alpabet

            if (isupper(plaintext[i])) // uppercae letters
            {
                begin = 'A';
                end = 'Z';
            }

            else if (islower(plaintext[i])) // lowercase letters
            {
                begin = 'a';
                end = 'z';
            }
        }
        // char cipher = text[i] + key;
        // printf("%c", cipher);
        printf("\n");
        return 0;
    }

}