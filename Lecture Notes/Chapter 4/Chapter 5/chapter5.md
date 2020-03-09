# Chapter 5: Interlude: Process API 

--

## Aside: Interludes

- Interludes will cover more practical aspects of systems, including a particular focus on OS APIs and how to use them

--

- We will discuss process creation in UNIX systems

- UNIX presents one of the most intriguing ways to create a new process with a pair of system calls: `fork()` and `exec()`

- A third routine, `wait()` can be used by a process wishing to wait for a process it has created to complete

- We not present these interfaces in more detail, with a new cimple examples to motivate us:

--

## CRUX: HOW TO CREATE AND CONTROL PROCESSES 

- What interfaces should the OS present for process creation and control?

- How should these interfaces be designed to eneable ease of use as well as utility?

--

## The `fork()` System Call

- The `fork()` system call is used to create a new process.

- Be forewarned: it is certainly the strangest routine to call

- More specifically, you have a running program whose code looks like what you see in Figure 5.1

- Examine the code, type it in and run it 

![alt figure-5-1](figure-5-1.png)

- When it first started running, the process prints out hellow world message 

- Included in that message is its **process identifier**, also known as **PID**

- The process has a PID of 29146; in UNIX systems, the PID is used to name the process if one wants to do something with the process, such as for example, stop it from running

- The process calls the `fork()` system call, which the OS provides as a way to create a new process

- The _odd part_: the process that is created is an (almost) _exact copy of the calling process_

- That means that to the OS, it now looks like there are two copies of the program `p1` running, and both are about to return from the `fork()` system call

- The newly-created process (called the **child**, in contrast to the creating **parent**) doesn't start running at `main()`

- Rather, the newly-created process just _comes to life_ as if it had called `fork()` itself

- The child isn't an _exact_ copy

- Specifically, although the child now has its own copy of the address space (i.e., its own private memory), its own registers, its own PC, and so forth...

- The value it returns to the caller of `fork()` is different

- While the parent receives the PID of the newly-created child, the child receives a return code of `0`

- This difference is useful because it is simple then to write the code that handles the two difference cases

- You might also have noticed: the output of `p1.c` is not **deterministic**

- When the child process is crated, there are now teo active processes in the system that we care about: the parent and the child

- Assuming we are running on a system with a single CPU, then either the child or the parent might run at that point 

- In the following example, the parent did and thus printed out it message first. However in other cases, the opposite might happen, such as the output trace shown below Figure 5-2

![alt figure-5-2](figure-5-2.png)

![alt figure-5-2-1](figure-5-2-1.png)

- The CPU **scheduler** determines which process runs at a given moment in time 

- Whichever process is chooses to run first remains a mystery due to its complexity

- This **non-determinism** leads to some interesting problems, particularly the **multi-threaded programs**

- Hence, we will see this again when dealing with **concurrency**

--

## 5.2 The `wait()` System Call

- Sometimes it is useful for a parent to wait for a child process to finish what it has been doing 

- This task is accoplished with the `wait()` system call (or its more complete sibling `waitpid()`) - See **Figure5.2**

- In this example (`p2.c`) the parent process calls `wait()` to delay its execution until the child finishes executing

- When the child is done, `wait()` returns to the parent

- Adding a `wait()` call to the code above makes the output deterministic

- If the parent runs first, it will immediately call `wait()`; this system call won't return until the child has run and exited

- Even when the parent runs first, it waits for the child to finish running, then `wait()` returns, and then the parent prints its message 

--

## 5.3 Finally, The `exec()` System Call

- 