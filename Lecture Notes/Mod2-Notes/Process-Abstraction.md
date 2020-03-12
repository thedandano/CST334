# Process Abstraction

---

## Motivation

- A key roll of processes is the balancing act of processor demands and system performance

---

## What is a Process?

- The OSes primary objective is to provide an arena where user programs can do their thang (i.e., run)

- An OS must provide a **_framework_** (i.e., file management) as well as an **_interface_** to these framework provisions

- When in an arena with multiprogramming going on, the OS must keep other programs from conflicting with each other

- This babysitting arrangement by the OS in accords to access the services the OS has to offer is known as a **process**

- A process is an algorithmic procedure of executing instructions within a confined, babysat arena (i.e., octogon)

- The arena must include:

1. An address space (Protected, Boi!!!)

   - Memory locations storing machinecode directions (required to process)

   - A Data Area

      - Global Variable Holder

   - Stack Area

      - Stack Frames (to hold local variables)

2. CPU Registers

   - So the process can do shit quick like maff n stuff (add, sub)

      - Doing shit quick without accessessing memory

      - Accessing memory slows shit down

3. Ability to invoke system calls

   - OS does the process a solid with these system calls

- The babysitting aren is known as a **process context**

