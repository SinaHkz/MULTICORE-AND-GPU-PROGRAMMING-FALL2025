# HW2 – Bug Hunt: Multithreaded Producer-Consumer System

**Prepared & Supported by:** Sina Hakimzadeh <br>
**Due Date:** November 10, 2025


## Overview

In this assignment, you will analyze and debug a multithreaded producer-consumer system implemented using POSIX Threads (pthreads). The code provided simulates a shared buffer accessed concurrently by multiple producer and consumer threads. Your task is to identify potential problems in synchronization, race conditions, thread termination, and performance.

### Using the Makefile

This assignment code includes a simple **Makefile** to compile and manage the Producer–Consumer program.

* **`make`** — Compiles the program and generates the executable named `producer_consumer`.
* **`make run`** — Builds (if needed) and then runs the program automatically.
* **`make clean`** — Removes the compiled executable to start fresh.
* **`make rebuild`** — Cleans and then recompiles everything from scratch.


## Tasks

### 1. Bug Identification and Debugging Process

* **Examine the given code carefully** to locate synchronization and logic errors.
* **Run the program under various configurations** (different numbers of producers, consumers, and buffer sizes) to reproduce race conditions, deadlocks, or performance issues.
* **Document each issue found** with:

  * The observed symptom (e.g., deadlock, data loss, premature termination, etc.)
  * The root cause (technical explanation)
  * The debugging approach used (e.g., adding logs, using tools like `valgrind`, `gdb`, or thread sanitizer)
  * The implemented fix
* **Progressive Versioning:**

  * Treat each identified issue as a version checkpoint.
  * For each version:

    1. Document the issue found.
    2. Describe how it was discovered.
    3. Present the fix and reasoning.
    4. Provide the updated code version.

By the end, you should have a **series of versions** showing your debugging journey from the initial faulty program to a correct and stable solution.


### 2. Implementing Graceful Consumer Shutdown

* Modify the code to allow all consumers to exit cleanly **after all producers have finished producing and the buffer is empty**.
* **Do not change the consumer loop structure** (`while (1)` must remain intact).
* Ensure that your fix works correctly under different timing and scheduling scenarios.

## Deliverables

1. **Technical Report**

   * Introduction & problem description
   * Identified bugs and debugging methodology
   * Solutions with explanations
   * Shutdown mechanism design & correctness reasoning

2. **Versioned Source Code Files**

   * Each version labeled clearly (e.g., `v1_initial.c`, `v2_fixed_mutex.c`, `v3_shutdown.c`, etc.)
   * Each version should compile and demonstrate the documented change.



## Ethics & Academic Integrity

This homework must reflect **your own work**. While discussions with classmates about general concepts are encouraged, all submitted code, scripts, reports, and analysis must be authored individually.  

- **Do not copy** solutions, scripts, or reports from other students, online sources, or prior years.  
- **Do not share** your own completed solutions with others before the submission deadline.  
- **Always cite** external sources (papers, documentation, tutorials) if you use them to inform your work.  
- **Profiling results must be your own.** Running the provided program and collecting data on your own machine is part of the assignment; submitting fabricated or borrowed results is considered misconduct.  

Violations will be treated as academic dishonesty and handled according to university policy.  

> When in doubt: ask questions, collaborate conceptually, but write and submit your **own independent work**.
