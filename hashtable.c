#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include <assert.h>
#include <stdbool.h>

const int BUCKET_COUNT = 1024;
struct Binding
{
    const char *key;
    int value;
    struct Binding *next;
};
struct HashTable
{
    struct Binding *buckets[1024];
};

struct HashTable *create()
{
    struct HashTable *table;
    table = (struct HashTable *)calloc(1, sizeof(struct HashTable));
    return table;
}

unsigned int hash(const char *x)
{
    int i;
    unsigned int h = 0U;
    for (i = 0; x[i] != '\0'; i++)
        h = h * 65599 + (unsigned char)x[i];
    return h % 1024;
}

bool add(struct HashTable *table, const char *key, int value)
{
    struct Binding *node = (struct Binding *)malloc(sizeof(struct Binding));
    struct Binding *p;
    int hashed = hash(key);
    for (p = table->buckets[hashed]; p != NULL; p = p->next)
    {
        if (strcmp(p->key, key) == 0)
        {
            p->value = value;
            return false;
        }
    }
    node->key = key;
    node->value = value;
    node->next = table->buckets[hashed];
    table->buckets[hashed] = node;
    return true;
}

struct Binding *find(struct HashTable *table, const char *key)
{
    struct Binding *node;
    int hashed = hash(key);
    for (node = table->buckets[hashed]; node != NULL; node = node->next)
    {
        if (strcmp(node->key, key) == 0)
        {
            return node;
        }
    }
    return NULL;
}

bool remove(struct HashTable *table, const char *key)
{
    struct Binding *node;
    struct Binding *temp;
    int hashed = hash(key);
    for (node = table->buckets[hashed]; node != NULL; node = node->next)
    {
        if (strcmp(node->key, key) == 0)
        {
            temp->next = node->next;
            node->next = temp;
            return true;
        }
        temp = node;
    }
    return false;
}

void delete_table(struct HashTable *table)
{
    struct Binding *node;
    struct Binding *nodenxt;
    int b;
    for (b = 0; b < BUCKET_COUNT; b++)
        for (node = table->buckets[b]; node != NULL; node = nodenxt)
        {
            nodenxt = node;
            // free(node);
        }
    // free(table);
}