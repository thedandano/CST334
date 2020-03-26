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

- The DS used to free memory in the heap is a type of **free list**

- This structure keeps track of which space is free in the heap

- Once a memory is given to a client (application), then it cannot be relocated to a new memory spot 

- library gives out pointers to spots in the heap by applications and no other application can own that spot within the heap -- unless returned by `free()`

- Because no other spot can be claimed by a client within the heap, **compaction** of free space is impossible - which would have been used to combat fragmentation

- However, using segmentation, Compactino could be used in the OS to deal with fragmentation

## 17.2 Low-Level Mechanisms

- When a smaller chunk is asked by a client, a splitting action happens where

**_head -> (addr:0, len:10) -> (addr21, len:9) -> NULL_**

- and with coalesing these merge together, because without it one will have 3 chunks of size 10, and coelesing combines them to 30

- Before the libary hands a chunk, it keeps a little for itself in a header block

- This lets the library know how much to give out to a client with interface:

```C
free(void *ptr)
```

- header keeps the size of what is being requested at minimum

- The `hptr` may also include different pointers to expedite deallocation, a magic number for integrity checks, and more

### Example of a simple header

```C
typedef struct __header_t {
   int size;
   int magic;
} header _t;
```

- When the user decides to call `free(ptr)` then the library uses math to figure out where the header starts:

```C
void free(void *ptr) {
   header_t *hptr = (void *)ptr - sizeof(header_t);
}
```

- After getting the pointer to the header, the library can check the magic number:

```C
assert(hptr->magic == 1234567)
```

- then calculate the size of the freed up region

- NOTE: the size of the free region is the size of the header plus the size of the space allocated to the user

- When a client requests N bytes, it searches for N bytes and the size of the header

## EMBEDDING A FREE LIST

- To manage the heap as a freelist one must:

1. initialize the list

2. the list should have one entry: the size of the heap minus the header

```C
typedef struct __node_t {
   int                size;
   struct __node_t   *next;
} node_t;
```

- This following code initializes the heap and puts the first element of the free list inside that space

- Assume that the heap is built within free space acquired via a call to the system call `mmap()`: NOT the ONLY way to build a heap FYI

```C
// mmap() returns a pointer to a chunk of free space
node_t *head = mmap(NULL, 4096, PROT_READ|PROT_WRITE,
   MAP_ANON|MAP_PRIVATE, -1, 0);
head->size = 4096 - sizeof(node_t);
head->next = NULL;
```

- The list has a single entry of size 4088

- The `head` pointer contains the first address of the range; thus 16KB, and `next`, which is set to NULL which is 0

- Assume that 100 bytes is requested by a client

1. The library will first find a chunk large enough to accomadate the request by the client

2. Since one chunk exists: 4088: this chunk will be chosen

3. The chunk will be split into 2: one to service the request (plus an additional header) plus the remainder of the chunk

- Assuming an 8byte header with magic number: thus upon request of the 100 bytes, the library gives 108 bytes away, returns a pointer to it, stashes the header before the allocated space (for later use when implementing `free()`), and shrinks the free node in the list to 3980 bytes

- Consider three allocated regions, each of 100 bytes (108 with header)

- so 108 * 3 will remove 324 bytes of the heap to allocate space

- the last header size will be the size of the remaining chunk (3764)

## 17.2 Basic Strategies

### Best Fit

- Searches through the free list and find chunks of free memory that are as big or bigger than the requested size

- Returns the one that is the smallest in that group of candidates

- this is called the best fit chunk 

- tries to reduce waste by returning what the user asks

- heavy performance penalty when performing an exhaustive search for the correct free block

### Worst Fit

- Finds the largest chunk and returns the requested amount keeping the remaining large chunk on the free list 

- Tries to leave big chunks free

- A search of the free list is required

- leads to excess frag while having high overheads

### First Fit

- Finds the first block that is big enough and returns what the client asks for

- The remaining chunk is left for more requests

- Advantage is speed, no deep search of free spaces needed

- Disadvantage: creates many small objects on the beginning of free list

- allocation order matters

- address:based ordering: by keeping list ordered by address of free space, merging the chunks becomes easier and fragmentation is reduced

### Next Fit

- Keeps an extra pointer where it was last looking in the list

- splintering?

- similar to first fit: no deep search needed
