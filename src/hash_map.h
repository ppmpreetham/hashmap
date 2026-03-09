#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdint.h>

typedef struct {
    char *chars;
    uint32_t hash;
    int len;
} String;

typedef struct {
    String *key;
    int value;
} Entry;

typedef struct {
    Entry *entries;
    int count;
    int capacity;
} Map;

void initMap(Map *map);
void freeMap(Map *map);
void growMap(Map *map, int capacity);

#endif