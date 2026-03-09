#include "./hash_map.h"

void initMap(Map* map){
    map->capacity = 0;
    map->count = 0;
    map->entries = NULL;
}

void freeMap(Map* map){
    free(map->entries);
    initMap(map);
}