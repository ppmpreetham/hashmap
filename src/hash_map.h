#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_LOAD_FACTOR 0.75
#define TOMBSTONE -1

typedef struct {
    char *chars;
    uint32_t hash;
    int len;
} String;

typedef struct {
    String *key;
    int val;
} Entry;

typedef struct {
    Entry *entries;
    int count;
    int capacity;
} Map;

void initMap(Map *map);
void freeMap(Map *map);
void growMap(Map *map, int capacity);

String *copyString(const char *chars);
void freeString(String *string);

bool mapSet(Map *map, String *key, int val);
bool mapGet(Map *map, String *key, int *val);

bool mapDelete(Map *map, String *key);

#endif