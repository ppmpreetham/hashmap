#include "./hash_map.h"

#include <stdlib.h> // mem alloc
#include <string.h> // memset

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
    free(map->entries);
    map->entries = entries;
    map->capacity = capacity;
    map->count = 0;
}