// Implements a dictionary's functionality
// ./speller dictionaries/small texts/lalaland.txt
// ./speller texts/lalaland.txt

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

const unsigned int N = 1019;

// Hash table
node *table[N];
node *heapSpaceHead;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *temp = table[hash(word)];
    while (temp)
    {
        bool flag = true;
        for (int i = 0;; i++)
        {
            if (toupper(word[i]) != temp->word[i])
            {
                flag = false;
                break;
            }
            if (!word[i])
            {
                break;
            }
        }
        if (flag)
        {
            return true;
        }
        else
        {
            temp = temp->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    while (*word != '\0')
    {
        hash = ((hash << 8) + (toupper(*word))) % N;
        word++;
    }

    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    char c;
    node *heapNodeSpace = (node *) malloc(sizeof(node) * 150000);
    heapSpaceHead = heapNodeSpace;
    heapNodeSpace->next = NULL;
    for (int i = 0; (c = getc(dict)) != -1; i++)
    {
        if (c == '\n')
        {
            heapNodeSpace->word[i] = '\0';
            i = -1;
            unsigned int hashValue = hash(heapNodeSpace->word);
            node *hashNode = table[hashValue];
            if (!hashNode)
            {
                table[hashValue] = heapNodeSpace;
            }
            else
            {
                while (hashNode->next)
                {
                    hashNode = hashNode->next;
                }
                hashNode->next = heapNodeSpace;
            }
            heapNodeSpace++;
            heapNodeSpace->next = NULL;
        }
        else if (i > LENGTH)
        {
            return false;
        }
        else
        {
            heapNodeSpace->word[i] = toupper(c);
        }
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int words = 0;
    for (int i = 0; i < N; i++)
    {
        node *temp = table[i];
        if (temp)
        {
            words++;
            while (temp->next)
            {
                words++;
                temp = temp->next;
            }
        }
    }
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    free(heapSpaceHead);
    return true;
}
