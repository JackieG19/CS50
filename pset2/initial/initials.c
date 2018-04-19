/*
i'd say sort your import alphabetically.
looks good.
*/


#include<stdio.h>
#include<cs50.h>
#include <string.h>
#include<ctype.h>

int main(void)
{
    string name;
    do
    {
        name = get_string(); // using get_string for input
    }
    while (!name);

    printf("%c", toupper(name[0])); // first initial in uppercae

    for (int i = 1; i < strlen(name); i++)
    {
        if (!isalpha(name[i])) // if space between string...
        {
            printf("%c", toupper(name[i + 1])); //...prints next letters in uppercase
        }
    }
    printf("\n");
    return 0;
}

/*NOTES

initials:
- first letter
- letters following space
- capitalize intitials
- toupper function
*/
