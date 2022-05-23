#include "stdint.h"
#include "string.h"

#include "handlers/item.h"
#include "handlers/keyspace2.h"
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

KeySpace2 *keySpace2Init(size_t size) {
    return NULL;
}

Item *keySpace2Select(KeySpace2 *this, char *key) {
    return NULL;
}

int keySpace2CanInsert(KeySpace2 *this) {
    return 0;
}

void keySpace2Insert(KeySpace2 *this, Item *item) {}

void keySpace2Drop(KeySpace2 *this, char *key) {}

void keySpace2Free(KeySpace2 *this) {}
