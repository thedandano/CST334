# Chapter 4: The Abstraction: The Process

- One of the most fundamental abstractions that the OS provides to users is the **process**

- A **process** is a **running program**

- The program itself is a lifeless thing, just instructions waiting to come to life.  The OS takes these bytes and get them running, transforming the program into something useful.

--

## How to provide the illusion of many cpus

- Although there are only a few physical CPUS available, how can the OS provide the illusion of nearly-endless supply of said CPUs?

--

- The OS creates this isllution by **virtualizing** the CPU

- By running one process, then stopping it and running another, the OS can promote the illusion that many virtual CPUs exist when in fact there is only one physical CPU (or a few).

- This basic technique is known as **time sharing** of the CPU, allowing users to run as many concurrent processes as they would like; the potential cost is performance, as each will run more slowly if the SPUs must be shared.

- To implement cirtualization of the CPU, and to implement it well, the OS  will need both some low-level machinery as well as some high-level intelligence 

- We call the low-level machinery **mechanisms**; mechanisms are low-level methods or protocols that implement a needed piece of functionality.

- e.g. we will learn later how to implement **context switch** which gives the OS the ability to stop running one program and start running another on a given CPU

- This **time-sharing** mechanism is employed by all modern OSes.

--

## TIP: USE TIME SHARING (AND SPACE SHARING)

- **Time-sharing** is a bsic technique used by an OS to share a resource.

- By allowing the resource to be used for a little while by one entity, and then a little while by many

- The counterpart of time sharing is **spae sharing**, where a resource is divided  (in space) among those who with to use it

- e.g. disk space is naturally a spaceshared resource, once a block is assigned to a file, it is normally not assigned to another file until the user deletes the original file.

--

- On top of these mechanisms resides some of the intelligence in the OS, in the form of **policies**

- Policies are algorithms for making some kind of decision within the OS

- E.G. given a number of possible rograms to run on a CPU, which program should the OS run?

- A **scheduling policy** in the OS will make this decision, likely using historical information (e.g., which program has run more over the last minute?), workload knowledge (e.g., what types of programs are run), and perfoormance metrics (e.g., is the system optimizing for interactive performance, or throughput?) to make its decision.

## 4.1 The Abstraction: A Process

- The abstraction provided by the OS of a running program is something we will call a **process**

- A process is simply a running program

- We can summarize a process by taking an inventory of the different pieces of the system it accesses or affects during the course of its execution

- To understand what constitutes a process, we thus have to understand its **machine state**: what a program can read or update when it is running.

- At any given time, what parts of the machine are important to the execution of this program?

- One obvious component of machine state that comprises a process is its _memory_.

- Instructions lie in memory; the data that the running programs reads and writes sit in memory as well

- Thus, the memory that the process can address (called its **address space**) is part of the process.

- Also part of the process' machine state are _registers_; many instructions explicitly read or update registers and thus clearly they are important to the execution of the process

- Note that there some particularly special registers that form part of this machine state.

- 