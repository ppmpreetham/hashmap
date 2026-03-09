# HashMap

Hashmap implemented using linear probing and FNV-1 hash function.

```
                 PROGRAM
                    │
     ┌──────────────┼──────────────┐
     │              │              │
     ▼              ▼              ▼
  mapSet()       mapGet()       mapDelete()
     │              │              │
     │              │              │
     │              ▼              ▼
     │          findEntry()    findEntry()
     │              │              │
     │              │              │
     │              ▼              ▼
     │         compareKey()    compareKey()
     │
     │
     ▼
findEntry()
     │
     ▼
compareKey()
```

## Hashing:

### FNV-1 Hash Function

```
hash = 2166136261
for each byte:
    hash ^= byte
    hash *= 16777619
```

## Entry Lookup:

```python
start_index = hash & (capacity - 1)

loop:
    entry = entries[index]

    if entry empty
        return entry

    if keys match
        return entry

    index = (index + 1) & (capacity - 1)
```

## Resizing:

```
Before
------
[ A ][ B ][ C ][   ][ D ]

After Resize
------------
[   ][ A ][   ][ B ][ C ][   ][ D ][   ]
```

## All Methods:

### Insert

`mapSet()`

1. compute hash
2. find slot using probing
3. insert or overwrite

Average: O(1)
Worst: O(n)

```
mapSet()
 ├── growMap()
 │    ├── malloc()
 │    ├── memset()
 │    ├── findEntry()
 │    │    └── compareKey()
 │    └── free()
 │
 └── findEntry()
      └── compareKey()
```

## Lookup

`mapGet()`

Steps:

1. compute hash
2. probe until:
   key found
   OR empty bucket

If empty bucket reached: key not present

```
mapGet()
 └── findEntry()
      └── compareKey()
```

## Delete

`mapDelete()`

Deletion does not clear the slot, but changes it to:
`NULL : TOMBSTONE` because removing it entirely would break probe chains.

```
Before
A → B → C

After Delete B
A → NULL : TOMBSTONE → C
```

```
mapDelete()
└── findEntry()
└── compareKey()
```
