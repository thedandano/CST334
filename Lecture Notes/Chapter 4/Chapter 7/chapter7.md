# Chapter 7: Scheduling

- By now low-level **mechanisms** of running processes (e.g., context switching) should be clear

- We have yet to understand the high-level **policies** that an OS scheduler employs

- We will present  a series of **scheduling policies** which are sometimes called **disciplines**

- The origins of scheduling predate computer systems; early approaches were taken from the field of operations management and applied to computers

--

## THE CRUX: HOW TO DEVELOP SCHEDULING POLICY

- How to develop a framework?

- What are key assumptions?

- What metrics are important?

- What basic approaches have been used in earlier computer systems

--

## 7.1 Workload Assumptions

- Before getting into the range of possible policies, let us first make a number of assumptions about the process running in the system, sometimes collectively called the **workload**

- Determining the workload is a critical part of  building policies

- The more you know about the workload, the more fine-tuned your  policy will be

- The workload assumptions we make here are mostly unrealistic

- We will work to what will culminate to a **fully-operational scheduling discipline**

- The following assumptions, or **jobs**, are running in the sysem:

1. Each job runs for the same amount of time 

2. All jobs arrive at the same time 

3. Once started, each job runs to completion

4. All jobs only use the CPU (i.e., they perform no I/O)

5. The run-time of each job is known 

- We said many of these assuptions were unrealistic, but just as some animals are more qual than others in the Animal Farm, some assumptions are more unrealistic than others in this chapter 

- In particular, it might bother you that the run-time of each job is known

- This would make the schedule omniscent, which, although it would be great (probably), its not very likely to happen

## 7.2 Scheduling Metrics 

- Beyond making workload assumptions, we also need one more thing to enable us to compare different scheduling policies: a **scheduling metric**

- A mtric is something used to _measure_ somehting, and there are a number og them in terms of scheduling 

- For now we will only have a single metric called the **turnaround time**

- Turnarounf = completion - arrival 

- We assume that the jobs arrive at the same time therefore arrival = 0 ; hence turnaround = completion 

- Turnaround is a **performance** metric 

- Another metric of interest is **fairness** as measured for example by **Jain's Fairness INDEX**

- Performance and fairness are often at odds in scheduling; a scheduler for example may optimize performance but at the cost of preventing a few jobs from running, thus decresing fairness

- This conundrum shows us that life isn't perfect

## 7.3 First In, First Out (FIFO)

- The most bsic algorithm we can implement is known as FIFO or sometimes called FIRST COME FIRST SERVE

- FIFO has a number of positive properties: it is clearly simple

FIFO has its limitations when one job, suppose A, runs for 100 seconds and queued jobs B and C only run for 10

- The analogy here is a grocery store when fuckers ahead of you have a ton of shit in their fucking cart and you just want to checkout with a jug of water for the day...**convoy effect**

## 7.4 Shortest Job First (SJF)

- It turns out that very simple approaches to solve this problem is the SJF: the new scheduling discipline.

- SJF is an **optimal** scheduling algorithm

--

### ASIDE: PREEMPTIVE SCHEDULERS

- In the older batch computing days, a number of **non-preemptive** schedulers were devloped

- Such systems would run each job to completion before considering whether to run a new job

- Virtually all modern schedulers are **preemptive**, and quote illing to stop one process from running another

- This implied that the shceduler employs the mechanisms learned about previously

- In particular, the scheduler can perform **context switch**, stopping one running process temporarily an resuming (or starting another)

--

- Thus we arrive upon a good approach to scheduling with SJF, but our assumptions are still fairly unrealistic

- Lets relax another assumption, assume that jobs can arrive at any time instead of all at once

## 7.5 Shortest Time-To-Completion First (STCF)

- To address this concern, we need to relax assumption 3 (that jobs must run to completion), so lets do that

- We need some machinery within the scheduler itself

- As you might have guessed, given our previous discussion about timer interrupts and context switching, the scheduler can certainly do something else when B and C arrive

- The scheduler can **preempt** job A and decide to run another jon, perhaps continuing A later

- SJF by our definition is a **non-preemptive** scheduler

- Thus suffers from the problems described above

- Fortunately, there is a scheduler which does excatly that: add preemption to SJF known as the **Shortest Time-to-Completion First (STCF)** or **Preemptive Shortest Job First (PSJF)** scheduler

- Anytime a jon enters the system, the STCF scheduler determines which of the remaining jobs (including the new job) has the least time left, and schedules that one

- Thus, in our ex, STCF would preempt A and run B and C ti completion; only when they are finished would A's remaining time be scheduled

- STCF is provably optimal; given that STF is optimal if all jobs arrice at the same time, you should probably be able to see the intuition behind the optimality of STCF

## 7.6 A New Metric: Response Time

- If we knew job lengths, that jobs only used the CPU, and out only metric was turnaround time, STCF would be a great policy

- The introduction of time-shared machines changes all of that

- Now users would sit at a terminal and demand interactive performance from the system as well

- Thus a new metric was born: **response time**

- We define response time as the time from when the job arrives in a system to the firs ttime it is scheduled: RESPONSE = FIRSTRUN - ARRIVAL

- For example, if we had the schedule above (with A arriving at time 0, and B and C at time 10), the reponse time of each job is as follows: 0 for job A, 0 for time B, and 10 for C (avg 3.33)

- STCF and related disciplines are not particularly good for response time 

- If 3 jobs arrive at thre same time, the 3rd job has to wait for the previous 2 jobs to run _in their entirety_ before being scheduled just one

- While great for turnaround time, this approach is quite bad for response time and interactivity

- How do we build a scheduler that is sensitive to response time?

## 7.7 Round Robin 

- To solve this problem we will introduce a new scheduling algorithm clasically referred to as **Round-Robin** (**RR**)

- The basic idea is simple instead of running jobs to completion, RR runs a job for a **time slice** sometimes called a **scheduling quantum** and then switches to the next job in the run queue

- It repeatedly does so until the jobs are finished

- For this reason, rr IS SOMETIMES CALL **TIME-SLICING**

- Note that the length of a time slice must be a multiple of the timer-interrupt period

- Thus if the timer interrupts every 10 ms, the time slice could be 10, 20, or any other multiple of 10 ms

- To undertand RR in more detail, lets look at another example

- Assume 3 jobs arrive and wish to run for 5 seconds.

- RR with time slice  has an average response time of (0+1+2)/3 = 1

- SJF has a response time of (0 + 5 + 10)/3 = 5

- However making the time slice too short is bad

- THE COST OF CONTEXT SWITCHING WILL DOMINATE OVERALL PERFORMANCE

- This deciding on the length of the time slice presents a trade-off to a system designer, making it long enough to **amortize** the cost of switching without making it so long that the system is no longer responsive

--

### TIP: AMORTIZING CAN REDUCE COSTS 

- The general technique of **amortization**  is comonly used in systems when there is a foxed cost to some operation

- By performing the operation less, the total cost is less 

- If time slice is 10ms, and context-switch cost is 1ms, roughly 10% of time spend context switching is tus wasted

- If we want to amotize the cost, we can increase the time slice, e.g., 100ms

- In this case less than 1% of time is spent context switching and thus the cost of time-slicing has been amortized 

--

- Note that the cost of context switching does not arise solely from the OS actions of saving and restoring a few registers

- When a program runs there is a flush of state is flushed from CPU caches, TLBs, branch predictors, and other on-chip hardware 

- New state relevant to the currently running job is brought into play

- RR is agreat scheduler if repsonse time was our only metric 

- What about turnaround time?

- RR makes for the worst policy if turnaround time were the only metric 

- RR is stretching out each job as long as it can, by only running each job for a short bit before moving to the next

- RR is fair, however a **trade-off** is required

- RR evenly divides the CPU among active processes on a small time scale, will perform poorly on metrics such as turnaround time

- We have discussed two types of schedulers: SJF and STCF

- Optimizes turnaround but is bad for resposne time 

- RR optimizes response time but is bad for turnaround 

--

### TIP: OVERLAP ENABLES HIGHER UTILIZATION

- When posible, **overlap** operations to maximize the utilization of systems

- Overlap is useful in many different domains, including when performing disk I/O or sending messages to remore machines

- In either case, starting the operation and then switching to other work is a good idea, and imporves the overall utilization and efficieny of the system

## 7.8 INCORPORATING I/O

- A scheduler has a decision to make when a job initiates an I/O request, because the currently-running job won't be using the CPU during the I/O; it is **blocked** waiting for I/0 completion

- The scheduler also has to make a decision when the I/O completes

- When that occurs, an interrupt is raised, and the OS runs and moves the process that issues the I/O from blocked back to the ready state

- A scheduler incorporates I/O using **overlap** by treating each CPU burst as a job, the scheduler makes sure processes that are "interactive" get run frequently

- Those interactive jobs performing I/O, other CPU-intensive jobs run, thus better utilization of the processor

