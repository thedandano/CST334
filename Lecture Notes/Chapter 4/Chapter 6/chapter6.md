# Chapter 6 Mechanism: Limited Direct Execution

- In order to virtualize the CPU, the operating stsem needs to somehow share the physical CPU among many jobs running seemingly at the same time

- The basic idea is simple:

1. Run one process for a little while

2. Run another one, and so forth

- By **time sharing** the CPU in this manner, virtualization is achieved

- There are a few challenges, however, in building such virtualiozation machinery 

- The first is _performance_

- How can we implement virtualization without adding excessive overhead to the system?

- The second is _control_: how can we run processes efficiently while retaining control over the CPU?

- Control is particularly important to the OS, as it is in charge of resources

- Without control, a process could simply run forever and take over the machine, or access information that is should not be allowed to access

- Obtaining high performance whiel maintaining control is thus one of the central challenges in building an operating system

--

## THE CRUX: HOW TO EFFICIENTLY VIRTUALIZE THE CPU WITH CONTROL

- The OS must virtualize the CPU in an efficient manner while retaining control over the system

- To do so, both hardware and operating-system support will be required

- The OS will often use a judicious bit of hardware support in order to accomplish its work effectively

--

## 6.1 Basic Technique: Limited Direct Execution

- To make a program run as fast as one might expect, not surprisingly OS developers came up with a technique, which we call **limited direct execution**

- The "direct execution" part of the idea is simple: just run the program directly on the CPU

- Thus, when the OS wishes to start a program running 

1. it creates a process entry for it in a process list 

2. allocates some memory for it 

3. loads the program code into memory (from disk), 

4. locates its entry point (i.e., the `main()` routine or something similar), 

5. jumps to it

6. and starts running the users' code

- The figure shows this basic direct execution protocol (without any limits, yet), using a normal call and return to jump to the program's `main()` and later to get back into the kernel

![alt figure-6-1](figure-6-1.png)

- This approach gives rise to a few problems in our quest to virtualize the CPU

1. The first is simple: if we just run a program, how can the OS make sure the program doesn't do anything that we don't want it to do, while still running it efficiently?

2. The second: when we are running a process, how does the operating system stop it from running a switch to another process, thus implementing the **time sharing** we require to virtualize the CPU?

- In asnwering these questions, we will get a much better sense of waht is needed to virtualize the CPU

- In developing these techniques, we will also see where the "limited" part of the name arises from; without limits on running programs, the OS wouldn't be in control of anything and thus would be "just a library" - A very sad state of affairs for an aspiring operating system

## 6.2 PROBLEM #1: RESTRICTED OPERATIONS

- Direct execution has the obvious advantage of being fast; the program runs natively on the hardware CPU and thus executes as quickly as one would expect.

- Running on the CPU introduces a problem

- What if the process wishes to perform some kind of restricted operation, such as issuing an I/O request to a disk, or gaining access to more system resources such as CPU or memory?

--

### The Crux: How to Perofmr Restricted Operations

- A process must be able to perform I/O and some other restricted operations, but without giving the process complete control over the system

- How can the OS and hardware work together to do so?

--

#### Aside: WHY SYSTEM CALLS LOOK LIKE PROCEDURE CALLS

- You may wonder why a call to a system call such as `open()` or `read()` looks exactly like a typical procedure call in C

- The reason is because it is a procedure call

- Hidden inside the procedure call is the famous trap instruction

- The procedure call into the C library uses an agreed-upon calling convention with the kernelto put arguments to open in well-known locations

- e.g., on the stack, or in specific registers

- The system-call number is placed into a well-known location as well (again, onto the stack or a register)

- Then executes the aforementioned trap instruction 

- The code in the library after the trap unpacks return values and returns control to the program that issued the system call

- Thus, the parts of the C library that make system calls are hand-coded in assembly, as they need to carefully follow convention in order to process arguments and return values correctly

- As well as execute the hardware-specific trap instructino 

- Now you know why you personally don't have to write assembly code to trap into an OS; somebody has already written that assembly for you

--

- Curving permission of a process can be approached in various ways 

- One way would be to let any process do what it wants in terms of I/O and other related operations

- However doing so would prevent the construction of many kinds of systems that are desirable

- e.g., if we wish to build a file system that checks permissions before granting access to a file, we can't simply let any user process issue I/Os to the disk

- If we did, a process could cimply read or write the entire disk and thus all protections would be lost 

- Thus, the approach we take is to introduce a new processor mode, known as **user mode**; code that runs in user mode isrestricted in what it can do

- For example, when running in user mode, a process can't issue I/O requests; doing so would result in the processor raising an exception; the os WOULD THEN LIKELY KILL THE PROCESS

- In contract, to user mode is **kernel mode**, which the operating system (or kernel) runs in 

- In this mode, code that runs can do what it likes, including privileged operations such as issuing I/O requests and executing all types of restricted instructions

- We are still left with the challenge however: what should a user process do when it wishes to perform some kind of privileged operation, such as reading from disk?

- To enable this, virtually all modern hardware provides the ability for user programs to perform a **system call**

- Pioneered on the ancient Atlas machine, system calls allow the kernel to carefully expose certain key pieces of functionality to user programs, such as accessessing the file system, creating and destroying processes, communicating with other processes, and allocating more memory

- Most OSes provide a few hundred calls; early UNIX systems exposed a more concise subset or around 20 calls

--

### TIP: USE PROTECTED CONTROL TRANSFER

- The hardware assists the OS by providing different modes of execution

- In **user mode**, applications do not have full access to hardware resources 

- In **kernel mode**, the OS has access to the full resources of the machine

- Special instructions to **trap** into the kernel and **return-from-trap** back to user-mode programs are also provided, as well as instructions that allow the OS to tell the hardware where the **trap table** resides in memory

--

- To execute a system call, a program must execute a special **trap** instruction

- This instruction simultaneously jumps into the kernel and raises the privege level to kernel mode

- Once in kernel mode, the system can now perform whatever privileged operations are needed (if allowed), and thus do the required work for the calling process

- When finished, the OS calls a special **return-from-trap** instruction that returns into the calling user program while simultaneously reducing the priviledge level back to user mode

- The hardware needs to be a bit careful when executing a trap, in that it must make sure to save enough of the caller's registers in order to be able to return coorectly when the OS issues the return-from-trap instruction

- on x86 for example, the processor will push the program counter, flags, and a few other registers onto a per-process **kernel stack**

- The return-from-trap will pop these values off the stack and resume execution of the user-mode program

- Other hardware systems use different conventions, but the basic concepts are similiar across all platforms 

- How does the trap know which code to run inside the OS?

- Since the calling process can't specify an address to jump to(as you would with a procedure call),  because this would allow the program to jump anywhere into the kernel - which is a bad idea 

- Thus the kernel must carefully control what code executes upon a trap 

- The kernel does so by setting up a **trap table** at boot time

- When the machine boots up, it does so in privileged (kernel) mode, and thus is free to configure machine hardware as need be 

- One of the first things the OS does is to tell the hardware what code to run when certain exceptional events occur

- e.g., what code should run when a hard0disk interrupt takes place, and when a keyboard interrupt occurs, or when a program makes a system call?

- The OS informs the hardware of the locations of these **trap handlers**, usually with a _special instruction_.

- Once the hardware is informed, it remembers the location of these handlers until the machine is next rebooted, and thus the hardware knows what to do (what code to jump to) when system calls and other exceptional events take place.

- To specify the exact system call, a **system-call number** is usually assigned to each system call

- The user code is thus responsible for placing the desired system-call number in a register or at a specified location on the stack

- The OS, when handling the system call inside the trap handler, examines this number, ensures it is valid, and, if so, executes the code

- This level of indirectino serves as a form of **protection**

- User code cannot specify an exact address to jump to, but rather must request a particular service via number 

- Being able to execute the instruction to tell the hardware where the trap tables are is a powerful capability

- Thus, it is also a **priviledged** operation

- If you try to execute this instruction in user mode, the hardware won't let you, and you can probably guess what will happen..adios!

- What horrible things could you do to a system if you could install your own trap table?  Could you take over the machine?

- The timeline (with time increasing downward, in figure 6-2) sums up the protocol.

![alt figure-6-2](figure-6-2.png)

- We assume each process has a kernel stack where registers (including general purpose registers and the program counter) are saved to and restored from (by the hardware) when transitioning into and out of the kernel

- There are teo phases in the LDE protocol

1. Boot Time: the kernel initializes the trap table, and the CPU remembers its location for subsequent use

   - The kernel does so via a privileged instruction (all privileged instructions are highlighted in bold)

2. When running a process: the kernel sets up a few things (e.g., allocating a node on the process list, allocating memory) before using a return-from-trap instruction to start the execution of the process

- This switches the CPU to user mode and begins running the process

- When the process wishes to issue a system call, it traps back into the OS, which handles it and once again returns control via a return-from-trap to the process

- The process then completes its work and returns from `main()`; this usually will return into some stub code which will properly exit the program (say, by calling `exit()` system call, which traps into the OS)

- At this point, the OS cleans up and we are done

## 6.3 Problem #2: Switching Between Processes

- The next problem with direct execution is achieving a switch between processes

- Switching between processes should be simple, right?

- The OS should just decide to stop one process and start another

- It gets tricky when a process is running on the CPU: by definition this means the OS is _not running_

- If the OS is not running, how can it do anything at all? It can't!

### HOW TO REGAIN CONTROL OF THE CPU SO THAT IT CAN SWITCH BETWEEN PROCESSES?

### A cooperative Approach: wait for system calls

- One approach that some systems have taken in the past is known as the **cooperative** approach

- In this style, the OS trusts the processes of the system to behave reasonably

- Processes that run for too long are assumed to periodically give up the CPU so that the OS can decide to run some other task.

- How does a friendly process give up the CPU in this utopian world?

- Most processes as it turns out transfer control of the CPU to the OS quite frequently by making **system calls** e.g., to open a file, to read a file, to send a message to another machine, or to create a new process

- Systems like this often include an explicit **yield** system call, which does nothing except to transfer control to the OS so it can run other processes 

- Applications also transfer control to the OS when they do something illegal

- For example, if an application divides by zero, or tries to access memory that it shouldn't be able to access, it will generate a **trap** to the OS

- The OS will then have control of the CPU again (and likely terminate the offending process)

- Thus, in a cooperative scheduling system, the OS regains control of the CPU by waiting for a system call or an illegal operation of some kind to take place

- You might also be thinking: isn't this passive approach less thn ideal?

- What happens is a process ends up being an infinite loop, and never makes a system call?

### A non-cooperative approach: the os takes control

- Without some additional help from the hardware, it turns out the OS can't do much at all when a process refuses to make system calls (or mistakes) and thus return control to the OS

- In fact, in the sooperative approach, your only recourse when a process gets stuck in an infinite loop, is to resort to rebooting

- How to gain control without cooperation?

- A **TIP** is to use the **timer interrupt** ... it gives the OS ability to run again on a CPU even if processes act in a non-copperative fashion

- Thus this hardware feature is essential in helping the OS maintain control of the machine

- The answer turns out to be simple and was discovered by a number of people building computer systems many years ago:

- a **timer interrupt**: a timer device can be programmed to raise an interrupt every so many ms

- When the interrupt is raised, the currently running process is halted, and a pre-configured **interrup handler** in the OS runs 

- At this point, the OS has regained control of the CPU and thus can do what is pleases 

- Stop the current process and start a different one 

- The OS must inform the hardware of which code to run when the timer interrupt occurs

- Thus, at boot time, the OS does exactly that. 

- Second, also during bott sequence, the OS must start a timer - which is a priviledged operation 

- Once the timer begins the OS can feel safe in that control will eventually be returned to it 

- The OS is free to run user programs 

- The timer can also be turned off (privi Op) something we will discuss in concurrency

- The hardware has some responsibility when an interrupt occurs, in particular to save enough of the state of the program that was running when the interrupt occurred such that a subsequent return-from-trap instruction will be able to resume the runnign program correctly

- This set of actions is quote similar to the behavior of the hardware during an explicit system-call trap into the kernel, with various registers this getting saved (e.g., onto a kernel stack)

- And thus easily restored by the return-from-trap instruction

## Saving and Restoring Context

- Now that the OS has regained control, whether by force or cooperation, a decision has to be made

- Whether to continue running the currently-running process or switch to a different one

- This decision is made by part of the OS known as the **scheduler**

- If the decision is made to dwitch, the OS then executes a low-level piece of code which re refer to as a **context switch**

A context-switch is conceptually simple: all the OS has to do is save a few register values for the currently-executing process (onto its kernel stack, for example)

- And restore a few for the soon-to-be-executing process (from its kernel stack)

- By doing so, the OS thus ensures that when the return-from-trap instructino is finally exexuted, instead of returning to the process that was running,, the system resumes execution of another process 

- To save the context of the currently-running process, the OS will execute some low-level assembly xode to save the general purpose registers, PC, as well as the kernel stack pointer of the currently-running process, and then restore said registers, PC, and switch to the kernel stack to the soon-to-be executing process

- By switching stacks, the kernel enters the call to the switch code in the context of one process (the one that was interrupted) and returns in the context of another (coming soon one)

- When the OS finally executes a return-from-trap instructin, the soon to be executing process becomes the currently-running process

- Thus the context switch is complete 

- 
