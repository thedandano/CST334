# Introduction to Operating Systems {#intro}

- An OS is the most important piece of software running on any computer as it manages all the computer's resources - both hardware such as memory, CPU, and storage) and software (such as data, applications, and utility programs)

## Figure 1: Lists the names of all the files in a directory

```#include "apue.h"
#include <dirent.h>

int
main(int arc, char*argc[])
{
   DIR   *dp;
   struct dirent *dirp;

   if (argc != 2) {
      err_quit("usage: ls directory_name");
   }
   if ((dp = opendir(argv[1])) == NULL){
      err_sys("Can't open %s", argv[1]);
   }
   while ((dirp = readdir(dp)) != NULL)
      printf("%s\n", dirp -> d_name);
   closedir(dp);
   exit(0);
}
```

- Without software a computer is useless since it controls the use of the hardware (CPU, memory, disks etc), and makes the computer into a useful tool for its users

- As we saw in the first lecture, the software side of a computer can be divided into programs, libraries, and the operating system

- Each layer hides much of the complexity of the layer below and provides a set of abstract services and concepts ato the layer above.

- For exmaple, the computer's hard disk allows data to be sotred on it in a set of fixed-sized blocks

- The OS hides this complexity and provides the concept of files to the application software

- In turn, an application program such as word processor hides the idea of a file and allows the user to work with documents instead

- The most fundamental of all system  software is the **operating system** as it has tweo main tasks to perform

1. Provide an abstraction layer

- The OS must shield the details of the hardware from the application programs, and thus from the user

- The OS _substitutes_ a set of abstract sevices to the application programs., to **_actuate_** the physical hardware services

- When applications use these abstract services, the operations must be translated into real hardware operations

--

1. Provide an abstraction level

2. Resource Manager

- Finally, the resources in a computer (CPU, MEMORY, DISK SPACE) are l;imited. 

- The OS must act as a resource manager, optimizing the use of the resources provides multiuser or multitasking capabilities, resources must be allocated fairly and equitably amongst numerous competing requests.

## Kernel Mode 

- Because an OS system must hide the computer's hardware, and manage the hardware resources, it needs to prevent the application software fgrom access the hardware directly.

- Without this sort of protection, the OS system would not be able to do its job 

- The computer's CPU provides two modes of operation which enforce this protection.  The OS runs in **kernel mode** also known as supervisor mode or priviliged mode 

- In **kernel mode**, the software has compelte acxcess to the computer's hardware and can control the swuitching between the CPU modes

- **_Interrupts_** are also received in the kernel mode software

## User Mode

- The rest of the software runs in **user mode**

- In this mode, direct access to the hardware is prohinbited, and so is any arbitrary switching to kernel mode

- Any attempts to vioate these restrictions are reported to the kernel mode software: in other words: to the OS itself

- Programs running in user mode are given an **address space** visible only to themselves, which contains enough memory for them to do their job

- **_By having two modes of operation which are enforced by the computer's own hardware, the OS can force application programs to user the OS abstract services.instead of circumventing any resource allocations by direct hardware access_**

## APIs: Interfaces to Programs

- If the software layers hide complexity and replace it with simpler abstractions, how do progframs aces these abstrations?

- Each layer provides an **API** (Application Program Interface) which is the set of functions and commands that it provides

- At the top of the OS are the **system calls**. These are the set of abstract operations that the operating system provides to the applications programs. 

- This interface is generally constant: users cannot change what is in the OS while it is running 

- When executed, a system call provides a controlled transition from user mode to kernel mode 

- Above the system calls are the set of **library routines**

- These are the functiona dn subroutines which are useful for many programs 

- Programs do the work for the user.  Regardless of their type, all programs can use the library routines and the system calls that come with an OS

- In fact, the only way to ask the kernel to do anything is to perform a system call!

## Types of Operating Systems

- Every OS is different, and each is designed to meet a set of goals; however one can generally classify operating systams into the following categories:

1. **Mainframe Operating Systems**

- Runs on mainframes, which provide immense I/O and availability

- They may provide a **batch** environment: jobs are segregated into batches with similar requirements

- Each batch is given to the computer to run

- When jobs with similar system requirements are batched together, this helps to streamline their processing

- **Transaction Processing**

- Where hundreds or thousands of small requests must be performed every second

- User interation is generally lacking in these systems, as the emphasis is on the computer's utilization

- An example mainframe System is IBM's OS/390

--

1. Mainframe Operating Systems

2. **Server Operating Systems**

- Run on servers

- The aim here is to provide services to many users at the same time 

- Services may have applications, file storage, print and other networking operations 

- The emphasis here is _on user response time as well as computer utilization_. 

- Server systsma re usually more general-purpose than the other types of operating systems

- Example multiprogramming systms are Linux, solaris, and windows 2k

--

1. Mainframe Operating Systems

2. Server Operating Systems

3. **Personal Computer Operating System**

- Is designed to provide a good environemnt to a single user at a time 

- User interface elements (Desktops, GUIs, etc) are important here 

- Response time and user experience is often m,ore important than efficient computer utilization

- Windows 7 and Mac OS X are examples.  Linux fits in here, although it can deal with multiple users at the same time

-- 

1. Mainframe OS

2. Server OS

3. PC OS

4. **Real-Time System**

- Desgined to respond to input within certain time constraints

- This input utually comes from external sensors, and not from humans 

- Thus, there is usually little or not user interaction 

- Many embedded systems are also real-time sustems

- An example is the QNX OS

--

1. Mainframe OS

2. Server OS

3. PC OS

4. Real-Time System

5. **Embedded OS**

- Has the OS built into the computer and is used to control external hardware.  

- There is little ot no application software in an embedded system

- PDS, computer built into DVDs, microwaves, and most cars

- Symbian is an example of an embedded operating system

## Design Principles and Concepts

- The services provided by an OS depends on the **concepts** around which the OS was crteated

- This gives each OS a certain _feel_ to the programmers who write programs for it - the set of system calls

- Although each operating system provides its unique set of services, most operate on a few common concepts

### The Process

- Most OS provide the concept of a process

- Here, we need to distinguish between a **program** and a **process**

- A **PROGRAM** is a collection of computer instructions plus some data that resides on a storage medium (e.g. a disk), waiting to be called into action

- A **process** is a program during execution

- It has been loaded into the computer's main memory, and is taking input, manipulating the input, and producing output

- Specifically, a process is an environment for a progrm to run in whic includes:

1. An **address space** which is a set of memory locations which stores the machine code instructions required by process, and the process' variables

- The address space is protected, so that other processes connot interfere 

--

1. Address Space

2. **A set of CPU registers** so that the process can perform some operations quickly (+ -) without having to access memory, which can be slow

--

1. Address Space

2. CPU Registers

3. **Ability to invoke system calls**, so that the process can ontain services from the OS

- _This environment is often known as a processes'_ **context**

## Memory

- Part of every computer's hardwaqre is its main memory

- This is the set of temporary storage locations which can hold machine code instructions and date

- Memory is volatile: when the power is turned off, the contents of main memory are lost

- In current computers, there are usually several GB of memory (e.g. billions of 8-bit storage areas)

- Memory contents can be accessed by reading or writing **memory location**, which has an integer **address** just like the numbers on the letter boxes in a street

- Memory locations often have a hardware protection, allowing or preventing read and writes 

- Uusually a process can only read and write to a specific set of locations that have been given to it by the OS: it's _address space_

- The OS allocates memory to processes as they are created and reclaims the memory once they finish

- Additionally, processes can usually request more memory, as well as relinquish this extra memory if they no longer require it. The operaint system ?????????

