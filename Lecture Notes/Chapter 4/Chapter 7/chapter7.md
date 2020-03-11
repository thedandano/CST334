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

- 