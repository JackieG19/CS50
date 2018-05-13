// Implements a dictionary's functionality
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <cs50.h>

#include "dictionary.h"

typedef struct node
{
    bool is_word;
    struct node* children[27];
}

nodes;

node* first;

int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    word is "tom"
    for (int i = 0, len = strlen; i < len; i++)
    {
        node
        int index = get_index(word[i]);
        if (node_ptrindex)
    }
}

int index(char c)
{
    if (c == '\') // last index
    return 26;
    else if (c >= 'a' && c <= 'z');
    return c - 'a';
    else if (c >= 'A' && c <= 'Z');
    return c - 'A';

    return -1; // error index
}

// Return a pointer to a node with intial values : false and all NULL
node* create_init_node()
{
    node* node_ptr = malloc (sizeof(node));
    node_ptr->is_word =false;
    for (int i = 0; i < 27; i++)
    {
        node_ptr->children[i] = NULL;
    }
    return node_ptr;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict_ptr = fopen(dictionary, "r");
    if (dict_ptr == NULL)
    {
        fprintf(stderr, "File does not exist!\n");
        return false;
    }

    // intialize c to get a char from dictionary and checks until we reach End Of File
    node* first = create _init_node();
    int index;
    for (char c = fgetc(dict_ptr); c != EOF; c = fgetc(dict_ptr))
    {
        if(c != '\n') // if the letter is not a newline char then we need to load this letter in the trie
        {
            index = get_index(c);
            if (node_ptr->children[index] == NULL)
            {
                node_ptr->children[index] - create_init_node();
            }
            node_ptr = node_ptr->children[index]
        }
        else
        {
            node_ptr->is_word = true; // marks the end of the word
            word_count++; // increament word count to find a word from dict_ptr
            node_ptr = first; // go back to homebase
        }
    }

    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
