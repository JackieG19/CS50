// Implements a dictionary's functional
#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

int wordcount = 0;

typedef struct node //define node struct
{
    char word[LENGTH + 1];
    struct node *next;
}

node;

node *cursor;

node *hashtable[26]; //create hashtable using "node" struct

/*
this function will correct for case, then return an int with
where  the first letter of the word falls in the alphabetically.*/
int hash(const char *word)
{
    int hash = (tolower(word[0]) - 'a');
    return hash;

}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char wordcheck[LENGTH + 1];

    strcpy(wordcheck, word);

    for (int i = 0; i < strlen(wordcheck); i++)
    {
        wordcheck[i] = tolower(wordcheck[i]);
    }

    int hashkey = hash(wordcheck);

    node *head = hashtable[hashkey];

    cursor = head;

    while (cursor != NULL)
    {
        if (strcasecmp(wordcheck, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    return false; //if word is not found in dictionary
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];

    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        fprintf(stderr, "Could not open Dictionary");
        return false;
    }

    /*scan through the dictionary for a string, put that string in the variable "word".*/
    while (fscanf(dict, "%s", word) != EOF) // Execute loop until end of dictionary file
    {
        //malloc a node * for new word
        node *new_node = malloc(sizeof(node));
        new_node->next = NULL;

        //if pointer to node returns NULL...
        if (new_node == NULL)
        {
            unload(); // ...unload dictionary and quit Speller
            return false;
        }

        strcpy(new_node->word, word); //copy word into node

        int hashvalue = hash(word); // gets the value from the hash function for (word)

        //if this bucket in the hashtable array has not been assigned a node yet...
        if (hashtable[hashvalue] == NULL)
        {
            hashtable[hashvalue] = new_node; //...simply add "new_node"
        }

        else // add "new_node" to the list of values stored at this bucket in the array
        {
            // both pointer are pointing to the old "first" node in the list
            new_node->next = hashtable[hashvalue];

            //point hashtable/value to the new node in the list
            hashtable[hashvalue] = new_node;
            // insert it in front of the node that was previously first on the list.
        }

        wordcount++;
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    return wordcount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0, n = 26; i < n; i++)
    {
        cursor = hashtable[i];

        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}