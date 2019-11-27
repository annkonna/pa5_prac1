Synchronization: Practice 1
===

This practice will test your understanding of synchronization primitives, concurrent control flows, and the POSIX mutex and condition variable APIs. It will use techniques you have previously seen in PA5.

For this practice, you will implement a synchronization barrier (sometimes called a checkpoint). A synchronization barrier blocks the logical control flows that reach a certain point until a specified number of flows have reached that point. It is used to ensure, for example, that a set of threads are all ready to perform their duties before any thread begins operation. 

The structure of a barrier is very similar to the structure of a semaphore, but in reverse. Whereas all threads reaching a semaphore may proceed immediately until its count is equal to zero, all threads reaching a barrier are blocked until its count is reached. You will implement a barrier using a Pthread mutex and condition variable. 

Given Code
---

You are given two files barrier.h and barrier.c. They implement a synchronization barrier as describe above, except that they do not implement the critical wait operation that blocks threads until all threads have arrived. You should read the comments in these files, as they will help you understand the code you have been given and how to implement your solution. 

The barrier in this project embodied by a struct Barrier, is initialized with an integer count greater than zero at creation time. Once it has been created, threads can wait on it using barrier_wait(). Unitl there are as many threads waiting on the barrier as the integer provided at creation time, waiting threads will block. WHen the final thread arrives, all waiting threads will be immediately released (and the final arriving thread will continue without blocking).

Requirements
---

You must implement the barrier_wait() function in src/barrier.c using the data structures and interface provided to you. 

The barrier_wait() function has the following semantics:

- The number of threads waiting on the barrier (nwaiting) must be incremented, and compared against the number of threads the barrier is configured to wait for (nthreads)
- If nthread == nwaiting, the barrier condition has been met, and all threads should be released.
- Otherwise, the current thread should block until some thread satisfies that condition. 

You must use lock to protect the state of the barrier, and barrier as the condition variable on which the waiting threads block. 

Your barrier implementation does not have to operate more than once. Once a barrier has released its threads, its work is done.

Building the Project
---

The default make target builds the project.

Verification
---

Running the program (./barrier) should output whether your program passed the test.

