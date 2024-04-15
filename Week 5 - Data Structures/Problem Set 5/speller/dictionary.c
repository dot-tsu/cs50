// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Represents number of buckets in hash table
const unsigned int N = 61;

// Represents the number of words in dictionary
unsigned int wordCount = 0;

// Hash table
node *table[N];

bool check(const char *word)
{
    // Hash the word to determine the index in the hash table
    unsigned int index = hash(word);

    // Browse through the linked list in search of the word
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
            return true;
        else
            cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hashValue = 0;
    // Sum the value of the letter and its index in the word
    for (int charIndex = 0; word[charIndex] != '\0'; charIndex++)
    {
        hashValue += charIndex + (toupper(word[charIndex]) - 'A' + 1);
    }
    return hashValue % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Initialize word variable to store each word read from the dictionary
    char word[LENGTH + 1];

    // Read words from the file one at the time
    while (fscanf(file, "%s", word) != EOF)
    {
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            fclose(file);
            return false;
        }

        // Counts the words for size()
        wordCount++;

        // Copy the word into the new node
        strcpy(newNode->word, word);

        // Hash the word to determine the index in the hash table
        unsigned int index = hash(word);

        // Insert the new node at the beginning of the linked list at table[index]
        newNode->next = table[index];
        table[index] = newNode;
    }

    // Close the file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through each bucket in the hash table
    for (int bucketIndex = 0; bucketIndex < N; bucketIndex++)
    {
        // Get the head of the linked list in the current bucket
        node *cursor = table[bucketIndex];

        // Free the nodes in the linked list
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
