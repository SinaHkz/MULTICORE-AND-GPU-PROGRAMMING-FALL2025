# Homework 2 – Multithreading, Debugging, and Performance

**Instructor:** Sina Hakimzadeh <br>
**Due Date:** November 10, 2025


## Overview

In this homework, you will strengthen your understanding of **multithreaded programming**, **synchronization**, and **performance analysis** using **POSIX Threads (pthreads)**. The homework consists of **two main parts**, each focusing on a different aspect of concurrent programming.


### Part 1 – Bug Hunt: Multithreaded Producer–Consumer System

In this part, you will **analyze and debug** a producer–consumer program that uses multiple threads to share data through a common buffer. Your tasks are to:

* Identify and fix race conditions, deadlocks, and shutdown problems.
* Implement a **graceful consumer shutdown** once all producers finish and the buffer is empty.
* Document your **debugging process**, showing how each issue was found and fixed.

By the end of this part, you will have a versioned debugging journey showing how a faulty multithreaded program evolves into a correct and stable one.


### Part 2 – Estimating π using the Monte Carlo Method

In this part, you will implement and optimize a **Monte Carlo algorithm** to estimate the value of π using **parallel computation**. You will:

* Build both **sequential** and **multithreaded** versions of the algorithm.
* Analyze **performance scaling** with different numbers of threads.
* Experiment with **optimization techniques**, such as:

  * Thread-local counters to minimize contention.
  * Byte-based result arrays for different partitioning strategies.
  * Controlled random seeds for reproducibility.

Finally, you will report and compare the results using tables or charts showing performance, accuracy, and scalability.


## Submission Requirements

Your submission should include the following items:

* **Documentation files:** Detailed technical reports for each part of the homework.
* **Source code:** All code files for both the Bug Hunt and Monte Carlo parts, including any modifications.
* **Versioned source code:** Clearly labeled versions demonstrating your debugging journey for the producer-consumer system.
* **Collected metrics:** Include performance data in CSV or JSON format.



## Academic Integrity
All work must be your own. Profiling results must be collected on your own machine. Cite any references you use.
