#include "stdint.h"
#include "string.h"
#include "models/keyspace2.h"

#define PRIMES_SIZE 32

const int PRIMES[PRIMES_SIZE] = {
        2, 3, 5, 7, 11, 13, 17, 19,
        23, 29, 31, 37, 41, 43, 47, 53,
        59, 61, 67, 71, 73, 79, 83, 89,
        97, 101, 103, 107, 109, 113, 127, 131
};

uint64_t hash1(char *str) {
    uint64_t hash = 0;
    for (int i = 0; i < strlen(str); i++)
        hash += PRIMES[i] * str[i];
    return hash;
}

uint64_t hash2(char *str, size_t size) {
    uint64_t hash = 1;
    int seed = 0;
    for (int i = 0; i < strlen(str); i++) {
        srand(seed + str[i]);
        seed = rand() % PRIMES_SIZE;
        if (size % PRIMES[seed] != 0)
            hash *= PRIMES[seed];
    }
    return hash;
}

int searchEmptyPosition(KeySpace2 *this, char *key) {
    int size = this->size;
    uint64_t h1 = hash1(key), h2 = hash2(key, size);
    int hash = 0, viewed = -1;
    do {
        viewed++;
        hash = (int) ((h1 + viewed * h2) % size);
    } while (viewed < size && this->busy[hash] == 1);
    if (viewed < size)
        return hash;
    return -1;
}

int searchItemPosition(KeySpace2 *this, char *key) {
    int size = this->size;
    uint64_t h1 = hash1(key), h2 = hash2(key, size);
    int hash = 0, viewed = -1;
    do {
        viewed++;
        hash = (int) ((h1 + viewed * h2) % size);
    } while (viewed < size && (this->busy[hash] == 0 || strcmp(this->items[hash]->key2, key) != 0));
    if (viewed < size)
        return hash;
    return -1;
}

KeySpace2 *keySpace2Init(size_t size) {
    KeySpace2 *this = malloc(sizeof(KeySpace2));
    this->items = calloc(size, sizeof(Item *));
    this->busy = calloc(size, sizeof(int));
    this->size = size;
    this->used = 0;
    return this;
}

int keySpace2CanInsert(KeySpace2 *this) {
    return this->used < this->size;
}

int keySpace2Select(KeySpace2 *this, Item **dest, char *key) {
    int pos = searchItemPosition(this, key);
    if (pos != -1) {
        *dest = this->items[pos];
        return 1;
    }
    return 0;
}

void keySpace2Insert(KeySpace2 *this, Item *item) {
    int pos = searchEmptyPosition(this, item->key2);
    this->items[pos] = item;
    this->busy[pos] = 1;
    this->used++;
}

void keySpace2Drop(KeySpace2 *this, char *key) {
    int pos = searchItemPosition(this, key);
    if (pos != -1) {
        this->busy[pos] = 0;
        this->used--;
    }
}

void keySpace2Free(KeySpace2 *this) {
    free(this->items);
    free(this->busy);
    free(this);
}