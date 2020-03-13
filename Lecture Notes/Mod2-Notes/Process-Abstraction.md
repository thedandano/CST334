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

---

## The Process Environment

- The OS ensures no conflict among processes in main memory

- Bro, so like, is main memory the arena???

- OS keeps processes from seeing each other and from seeing the OS....wtf!

- Them processes are in prison! High risk isolation prison!

- Putting a process in prison is done by running its machine code in user mode

- User mode is prison mode

- In prison mode, some machine instructions are cut off, memory areas not owned by a process are restricted, access to all hardware is denied by the CPU

---

## System Calls

- So how does a process get that solid from the OS (i.e., use its services like read froma file and move the mouse)

- The process gets its solid with the **TRAP** instruction

- The trap instruction pushes the job from the prisoner to the OS

- The process places instructions in the CPU, and tells the OS what is wants

- This procedure of gaining services from the OS is called a **system call**

- Each OS has it's own set of **system calls** and the set of these calls is known as the OSes API

---

## Layout of a Process

- Memory Map is another word for **address space**

- Memory map allows the stack to grow one direction and the data area to grow in another direction: in other words, the prisoner can have access to more main memory environment than the OS initially allocated

- Areas above or below the process' memory are invalid due to OSes protections boi!!!

- Those other areas are off limits because thats where other processes exist

---

## Process Models

- Sometimes a process can't do much because another process has the CPU (at the front desk) or it is waiting for a drug deal (I/O) (e.g., blocked)

- On an **embedded system** there is only one prisoner in the yard (one process in memory)

- The prisoner is either running or waiting for a drug deal(I/O), or in line to shoot his horse (polling); which is wasteful for the CPU resources

- A **batch** system may have many process (known as jobs) loaded into main memory. Think many prisoners.

- Although there are many prisoners in the yard, only one is selected at any time

- Once that prisoner does what he does in the yard, (job runs to completion) before the next prisoner can step in

- Polling, or waiting in line to get a slap of some horse, is used by the OS to detect the completion of the drug deal (I/O)

- It is important to note that drug dealing devices like disks, tape drives, modems, network cards, keyboards, etc. are at least 1000 times slower than main memory and 1,000,000 times slower than the CPU (front desk of prison)

- While the system is polling a device for the completion of in or output, the CPU is doing no useful work

- To reduce the waste of the front desk's time by having a druggie wait in line for his slap, on some batch systems, the prisoners **run to block**

- Instead of waiting for a drug deal (I/O), the OS blocks the prisoner (puts it to sleep), selecting another prisoner to do his thing

- When a drug deal is done, the OS finds the sleeping prisoner who requested a drug deal, and unblocks it into ready state, as the prisoner can now execute more instructions

- An **interrupt** from the hardware (drug dealer) tells the OS that the drug deal is done

- There can be more than one prisoner in ready state, and more tha one prisoner in blocked state 

- Since we are considering only one CPU, there can only be one prisoner in running state (in the yard)

- **Run to block** is not suitable
