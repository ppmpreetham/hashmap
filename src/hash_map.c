#include "./hash_map.h"

#include <stddef.h> // NULL
#include <stdint.h> // uint32_t, ...
#include <stdlib.h> // mem alloc
#include <string.h> // memset, strdup, strlen

void initMap(Map* map){
    map->capacity = 0;
    map->count = 0;
    map->entries = NULL;
}

void freeMap(Map* map){
    free(map->entries);
    initMap(map);
}

void growMap(Map* map, int capacity){
    Entry *entries = malloc(capacity*sizeof(Entry));
    memset(entries, 0, capacity*sizeof(Entry));

    // TODO: copy and count entries from old table to new one
    
    free(map->entries);
    map->entries = entries;
    map->capacity = capacity;
    map->count = 0;
}

static uint32_t hashString(const char *chars){
    // FNV-1
    uint32_t hash = 2166136261u;
    while (*chars){
        hash = (hash ^ (uint8_t)chars[0]*16777619);
        chars++;
    }

    return hash;
}

String *copyString(const char *chars){
    // heap cuz stack var can't outlive the fn
    String *string = malloc(sizeof(String));
    string->hash = hashString(chars);
    string->len = strlen(chars);
    string->chars = strdup(chars);
    return string;
}