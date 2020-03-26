# Chapter 18: Paging; and introduction

- The OS has two methods for space-managing 

1. Segmentation: chop shit up into variable-sized pieces

   - Problem: fragmentation - allocating gets harder over time

2. Paging: chop shit up into fixed-sized pieces

   - Don't break up code, heap, stack

   - fixed-sized units called a **page**

- Physical memory is seen as fized-sized slots: **page frames**

- Each frame can have one virtual-memory page

---

## THE CRUX: HOW TO VIRTUALIZE MEMORY WITH PAGES?

1. How can we virtualize memory with pages, to avoid segmentation?

2. Basic techniques?

3. Minimize space and time?

---

## 18.1 A simple example and overview 

- Suppose an address space of 64 bytes, with 4 pages (16*4): virtual pages 0, 1, 2, 3

- Physical memory will have 8 page frames making up 128-byte physical memory

- Pages can be place in different spots of physical memory

- One of the most important aspects of paging is flexibility

- system supports abstraction of an address space regardless of how a process uses the space

- Second advantage of paging is simplicity: the OS can maintain a free list of all free pages

- OS tracks each virtual page of the address space placed in physical memory on a data structure known as a **page table**

- The **page table** stores **address translations** for each v.page of the address space: allowing to see where in physical memory the v.page lives

- New process begins: a new page table is used

- This process is performing a memory access

```assembly
movl <virtual address>, %eax
```

- To translate virtual address to physical memory:

1. Split it up into 2 components:

   - VPN: VIRTUAL PAGE NUMBER
   - OFFSET

- The virtual address is 64 bytes: thus 6 bits needed for virtual address: 2^6 = 64

va5 va4 va3 va2 va1 va0

- va5 is the highest-order bit and va0 is the lowest-order bit

- The page size of 16 bytes is known: thus:

VPN [va5, va4] && OFFSET[va3, va2, va1, va0]

- The page size is 16 bytes in a 64-byte address

- Top two bits of the address select 4 pages: 16 bytes

- The remaining bits tell us which byte of the page we are interested in, 4 bits in this case; we call this the offset

- When a process generates a virtual address, the OS and the hardware combine to translate to a meaningful physical address

- Suppose the load above was to virtual address 21:

```assembly
movl 21, %eax
```

- Turn 21 to binary `010101`

- VPN[0,1] && OFFSET[0101]

- Thus the virtual address 21 is on the 5th 0101th byte of the virtual page 01

- The physical frame number, or PFN, is sometimes called the physical page number, or PPN

## 18.3 What's Actually in the page table?

- The page table is just a data structure that is used to map virtual page numbers tp physical page numbers

- in a page table entry, there are a number of different bits

- a valid bit commonly indicates whether a certain translation is valid

- all of the unused space in between will have invalid bits

- protection bits are there to indicate whether the page could be read from, written to, or executed from

- Accessing a page in a way that is not allowed yields a trap to the OS

- swapping allows the OS to free up physical memory by moving rarely-used pages to disk

- a dirty bit indicates whether the page has been modified since it was brought to memory

- a reference bit (accessed bit) used to track popularity of use --> knowledge needed for page replacement

- present bit indicates whether this page is in physical memory or on a disk

## 18.4 Paging: Also Too Slow

- With page tables in memory, we already know that they might be too big

```assembly
movl 21, %eax
```

- Examine the explivit reference to address 21

- The hardware will perform the translation for us

- To fetch data, the system must translate 21 --> 117

- Before fetching data from address 117, the syste, must first fetch the correct page table entry (PTE) from the process's page table, perform the translation, then load the data from physical memory

- The hardware must know where the page table is from the currently running process

- ASSUME: a single page-table base register contains the physical address of the stsrting location of the page table

- To find the location of the desired PTE, the hardware will thus perform the following:

```C
VPN = (virtualAddress & VPN_MASK) >> SHIFT
PTEAddr = PageTableBaseRegister + (VPN * sizeof(PTE))
```

- In our example, the VPN_MASK would be set to 0x30 (hex 30, or binary 110000) which picks out the VPN bits from the full virtual address; `SHIFT` is set to 4 (the number of bits in the offset), such that we move the VPN bits down to form the correct integer

- Paging requires one to perform one extra memory reference in order to first fetch the translation from the page table 