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

- One obvious component of machine state that comprises a process is its _memory_

- Instructions lie in memory; the data that the running programs reads and writes sit in memory as well

- Thus, the memory that the process can address (called its **address space**) is part of the process.

- Also part of the process' machine state are _registers_; many instructions explicitly read or update registers and thus clearly they are important to the execution of the process

- Note that there some particularly special registers that form part of this machine state.

- e.g., the **program counter(PC)** sometimes called the **instruction pointer** or **IP** tells us which instruction of the program is currently being executed; similarly a **stack pointer** and associated **frame pointer** are used to manage the stack for function parameters, local variables, and return addresses.

- Finally, programs often access persistent storage devices too.

- Such I/O _information_ might include a list of the files the process currently has open.

## 4.2 Process API

- Though we defer discussion of a real process API until a subsequent chapter, we first give some idea of what must be included in any interface of an operating system.

- These APIs, in some form, are available on any modern operating system 

1. **Create**
   - An operating system must include some method to create new processes.

   - When you type a command into the shell, or double-click on an application icon, the OS is invooked to create a new process to run a program you have indicated

2. **Destroy**

   - As there is an interface for process creation, systems also provide an interface to destroy processes forcefully.

   - Many processes will run and just exit by themselves when complete

   - When they don't, however, the user mau wish to kill them, and thus an interface to halt a runwaway process is quite useful

3. **Wait**

   - Sometimes it is useful to wait for a process to stop running; thus some kind of waiting interface is often provided

4. **Miscellaneous Control**

   - Other than killing or waiting for a process, there are sometimes other controls that are possible 

   - e.g., most OS provide some kind of method to suspend a process (stop it from running for a while) and then resume it (continue it running)

5. **Status**

   - There are usually interfaces to get some status information about a process as well, such as how long it has run for, or what state it is in.

![alt figure 4.1](Figure-4-1.png){#figure4-1}

## 4.3 Process Creation: A little More Detail

- One mystery that we should unmask a bit is how programs are transformed into processes. 

- How does the OS get a program up and running? 

- How does a process creation actually work?

- The first thing an OS must do to run a program is to **load** its code and any static data (e.g., initialized variables) into memory, into the address space of the process

- Programs initially reside on **disk** (or in some modern systems, **flash-based SSDs)** in some kind of **executable format** thus the process of loading a program and static data into memoery requires the OS to read those bytes from disk and place them in memory somewhere; such as Figure 4-1

- In simple, early OS, the loading process is done **eagerly**, i.e., all at once before running the program; modern OSes perform the process **lazily**, i.e., by loading pieces of code or data only as they are needed during program execution

- To truly understand how lazily loading of pieces of code and data works, you will have to understand more about the machinery of **paging** and **swapping**, topics we will cover in the future when we discuss the virtualization of memory

- For now, just remember that before running anything, the OS clearly must do some work to get the important program bits from disk into memory

1. Once the code and static data are loaded into memory, there are a few other things the OS needs to do before running the process

   - Some memory must be allocated for the program's **run-time stack (or just stack)**

   - C programs use the stack for local variables, function parameters, and return addresses; the OS allocates this memory and gives it to the process.

   - The OS will also likely initialize the stack with arguments; specifically, it will fill in the parameters to the `main()` function, i.e., `argc` and the `argv` array

2. The OS may also allocate some memory for the program's **heap**

   - In C programs, the heap is used for explicitly requested dynamically-allocated data; programs reuest such space by calling `malloc()` and free it explicitly by calling `free()`

   - The heap is needed for data structures such as linked lists, hash tables, trees, and other interesting data structures

   - The heap will be small at first, as the program runs, and requests more memory via `malloc()` library API, the OS may get involved and allocate more memory to the process to help satisfy such calls. 

3. The OS will also do some other initialization tasks, particularly as related to I/O

   - e.g., in UNIX systems, each process by default has 2 open **file descriptors**, for std input, output, and error; these descriptors let programs easily read input from the terminal as well as print output to the screen

   - This relates to **persistence** and will be covered later 

4. By loading the code and static data into memory, by creating and initializing a stack, and by doing other work as realted to I/O setup, the OS has now FINALLY set the stage for program execution.

   - It thus has one last task: to start the program running (through a specialized mechanism that we will discuss next chapter(, the OS transfers control of the CPU to the newly-created process, and thus the program begins to execute)

## 4.4 Process States

- Now that we have some idea of what a process is (though we will continue to refine this notion), and roughly how it is created, let us talk about the different **states** a process ca be in at a given time

- The notion that a process can be in one of these states arose in early computer systems

- In a simplified view: a process can be in one of these 3 states

1. **Running**

   - In a running state, a process is running on a processor, meaning it is executing instructions 

2. **Ready**

   - In the ready state, a process is ready to run but for some reason the OS has chosen not to run it at this given moment

3. **Blocked**

   - In the blocked state, a process has performed some kind of operation that makes it not ready to run until some other event takes place

   - A common example: when a process initiates an I/O request to a disk, it becomes blocked and thus some other process can use the processor

![alt figure-4-2](figure-4-2.png)

- If we were to map these states to a graph, we would arrive at the diagram above.

- A process can be moved between the ready and running states at the discretion of the OS

- Being moved from ready to running states means the process has been **scheduled**

- Being moved from running to ready means the process has been **descheduled**

- Once a process has become blocked (e.g., by initiating an I/O operation), the OS will keep it as such until some event occurs (e.g., I/O completion)

- At this point, the process moves to the ready state again (and potentially) immediately to running again, if the OS so decides

- Here is an example of how 2 processes might transition through some of these states.

1. Imagine 2 processes running, each of which only use the CPY (they do no I/O)

   - A trace of the state of each process might look like this figure

   ![alt figure-4-3](figure-4-3.png)

   - In this example, the first process issues an I/O after running for some time

   - At that point, the processes is blocked, giving the other process a chance to run. Figure 4-4 shows a trace of this scenario

   ![alt figure-4-4](figure-4-4.png)

2. More specifically, process(0) initiaties an I/O and becomes blocked waiting for it to complete; processes become blocked, for example, when reading from a disk or waiting for a packet from a network

   - The OS recognizes Process(0) is not using the CPU and starts running Process(1)

   - While Process(1) is running, the I/O completes, moving Process(0) back to _ready_

   - Finally, Process(1) finishes, and Process(0) runs and then is done.

3. Note that there are many decisions the OS must make, even in this simple example

   - First, the system had to decide to run Process(1) while Process(0) issued an I/O

   - Doing so improves resource utilization by keeping the CPU busy

   - Second, the system decided not to switch back to Process(0) when its I/O completed; it is not clear if this is a good decision or not

- These types of decisions are made by the OS **Scheduler**

--

## 4.5 Data Structures

- The OS is a program, and like any program it has some key DS that track various relevant pieces of information 

- To track the state of each process, the OS likely will keep some kind of **process lis** for all processes that are ready, as well as some additional information to track which process is currently running

- The OS must also track, in some way, blocked processes; when an I/O event completes, the PS shouls make sure to wake the correct process and ready it to run again

- Figure 4-5 shos what type of information an OS needs to track about each process in the xv6 kernel

![alt figure-4-5](figure-4-5.png)

- Similar process structures exist in "real" OS such as Linux, Mac OS X, or Windows; look them up and see how much more complex they are

- From the figure, you can see a couple of important pieces of information the OS tracks about the process

- The **register context** will hold, for a stopped process, the contents of its registers

- When a process is stopped, its registers will be saved to this memory location; by restoring these registers (i.e., placing thier values back into the actual physical registers), the OS can resume running the process

- **context switch** technique will be learned in later chapters.

- You can also see from the figure that there are some other states a process can be in, beyond running, ready, and blocked. 

- Sometimes a system willl have an **initial** state that the process is in when it is being created

- Also, a process could be placed in a **final** state where it has exited but has not yet been cleaned up (in UNIX-based systems, this is call the **zombie** state)

- This final state can be useful as it allows other processes (usually the **parent** that created the process) to examine the return code of the process and see if the just-finished process executed successfully (usually, a programs return zero in UNIX-based systems when they have accomplished a task susseccfully, and a non-zero otherwise)

- When finished, the parent will make one final call (e.g., `wait()`) to wait for the completion of the child, and to also indicate to the OS that it can clean up any relevant data structures that referred to the now-extinct process

-- 

### Aside: Data Structures - The Process List

- Operating systems are replete with various important **data structures** that we will discuss in these notes

- The **process list** is the first such structure

- It is one of the simpler ones, but certainly any OS that has the ability to run multiple programs at once will have something akin to this structure in order to keep track of all the running programs in the system

- Sometimes people refer to the individual structure that stores information about a process as a **Process Control Block (PCB)**, a fancy way of talking about a C structure that contains information about each process

--

## Summary

- We have intoduced the most basic abstraction of the OS: the process.

- It is quite simply viewed as a running program 

- With this conceptual view in mind, we will now move on to the nitty-gritty: the low-level mechanisms needed to implement processe, and the higher-level policies required to schedule them in an intelligent

- By combining mechanisms and policies, we will build up our understanding of how an operating system virtualizes the CPU
