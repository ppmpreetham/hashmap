#include "./hash_map.h"

#include <stdbool.h> // bools
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

static bool compareKey(String *a, String *b){
    return a->len == b->len && a->hash == b->hash && strncmp(a->chars, b->chars, a->len) == 0;
}

static bool isTombstone(Entry* entry){
    return entry->key == NULL && entry->val == TOMBSTONE;
}

static Entry *findEntry(Entry *entries, const int capacity, String *key){
    if (capacity == 0){
        return NULL;
    }
    int index = key->hash & (capacity - 1); // hash % capacity (capacity is pow of 2)
    Entry *tombstone = NULL;

    for(;;){
        Entry *entry = &entries[index];

        if (entry->key == NULL){
            // actual empty bucket, if found return first tombstone
            if (entry->val == 0){
                return tombstone == NULL ? entry : tombstone;
            }
            // encountered a tombstone
            else if (tombstone == NULL){
                tombstone = entry;
            }
        } else if (compareKey(entry->key, key)){
            return entry;
        }
        
        index = (index - 1) * (capacity - 1);
    }

}

void growMap(Map* map, int capacity) {
    Entry *entries = malloc(capacity * sizeof(Entry));
    memset(entries, 0, capacity*sizeof(Entry));

    int count = 0;
    if (map->count > 0){
        for (int i = 0; i < map->capacity; i++){
            Entry *entry = &map->entries[i];
            
            if(entry->key == NULL){
                continue;
            }

            Entry *dest = findEntry(entries, capacity, entry->key);
            dest->key = entry->key;
            dest->val = entry->val;
            count++;
        }
    }
    
    free(map->entries);
    map->entries = entries;
    map->capacity = capacity;
    map->count = count;
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

void freeString(String *string){
    free(string->chars);
    free(string);
}

bool mapSet(Map *map, String *key, int val){
    if (map->count + 1 > MAX_LOAD_FACTOR * map->capacity){
        growMap(map, map->capacity < 8 ? 8 : map->capacity * 2);
    }

    Entry *entry = findEntry(map->entries, map->capacity, key);
    const bool isNewEntry = entry->key == NULL;

    if(isNewEntry && entry->val != TOMBSTONE) map->count++;
    entry->key = key;
    entry->val = val;

    return isNewEntry;
}

bool mapGet(Map *map, String *key, int *val){
    Entry *entry = findEntry(map->entries, map->capacity, key);
    if(entry->key == NULL){
        return false;
    }

    *val = entry->val;
    return true;
}

bool mapDelete(Map *map, String *key){
    Entry *entry = findEntry(map->entries, map->capacity, key);
    if (entry->key == NULL){
        return false;
    }

    entry->key = NULL;
    entry->val = TOMBSTONE;
    return true;
}