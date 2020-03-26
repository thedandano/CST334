# Free-Space Management

- Memory fundamentals that not only malloc library but the OS can use (for managing address space processes); a fundamental called **free-space management**

- Memory management is easy whenn doing **paging** you keep a list of fixed memory units and disperse them FIFO

- Not all units are made the same when applying `malloc()` or `free()` and especially not when OS manages physical memory during **segmentation** to **_implement virtual memory_**

- **External fragmentation** is free space chopped up into different size shards and requesting memory fails when memory size requested isn't a contiguos whole

---

## CRUX: HOW TO MANAGE FREE SPACE

1. how should free space be managed, when requests are of variable size?

2. how can fragmentation be minimized?

3. what are time and space overheads of different solutions?

---

## 17.1 ASSUMPTIONS

- In

```C
void *malloc(size_t size)
```

1. the `size` parameter is the number of bytes requested by an application

   - hands back a pointer `void *` to a region of that size or greater 

- The complement:

```C
void free(void *ptr)
```

1. takes a pointer and frees the chunk

- Notice that the size of what is to be freed is not expressed to the library

- The library must figure out how large a chunk when handed a pointer

- The space that this library manages is known as the **heap**

