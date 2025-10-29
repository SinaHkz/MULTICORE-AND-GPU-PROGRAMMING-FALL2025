# HW2 – Estimating Pi using Monte Carlo Method with Pthreads

**Prepared & Supported by:** Sina Hakimzadeh <br>
**Due Date:** November 10, 2025


## Overview

This assignment introduces **multithreaded programming** using POSIX threads (**pthreads**) through the implementation of the **Monte Carlo algorithm** to estimate the value of π (pi). The Monte Carlo approach utilizes random sampling to approximate mathematical results and, when parallelized, can leverage multiple CPU cores to enhance both performance and accuracy.

You will implement both **sequential** and **parallel** versions of the algorithm, explore synchronization strategies, and analyze how multithreading affects performance and accuracy.


## Background: Monte Carlo Estimation of π

Consider a 2D coordinate plane containing a square of side length `2r`, centered at `(0,0)`. A circle of radius `r` is inscribed within this square, also centered at `(0,0)`. To estimate π, we randomly generate points inside the square and check how many fall within the circle.

The probability that a randomly chosen point lies inside the circle is given by:

$$ P = \frac{\text{Area of Circle}}{\text{Area of Square}} = \frac{\pi r^2}{4r^2} = \frac{\pi}{4} $$

Hence, π can be estimated as:

$$ \pi \approx 4 \times \frac{\text{Points Inside Circle}}{\text{Total Points Generated}} $$

By increasing the number of random samples (and utilizing multiple threads), the estimate becomes more accurate.


## Tasks

### 1. Sequential Implementation

Implement a **single-threaded** version of the Monte Carlo algorithm to estimate π. Use random number generation to simulate the placement of points and count how many fall inside the circle.

### 2. Parallel Implementation with Pthreads

* Create a **multithreaded version** using the POSIX Threads library.
* Each thread should independently generate a subset of random points and count how many lie inside the circle.

### 3. Thread Management and Performance Exploration

* Experiment with different numbers of threads (e.g., 1, 2, 4, 8, 16) to observe performance scaling.
* Compare total execution times and accuracy for each configuration.
* Discuss how CPU utilization and thread scheduling impact results.

### 4. Optimization and Advanced Experimentation

Implement and test **multiple versions** of your algorithm to improve performance. Possible directions include:

* Using **thread-local counters** to reduce contention.
* Using a **byte-based result array** to store sampling outcomes, and evaluating performance under both static and dynamic partitioning strategies.
* Exploring **random seed control** to ensure reproducibility.

Document how each modification affects performance and correctness.

### 5. Profiling and Performance Analysis

* Use the skills acquired in the first assignment to measure various performance metrics.
* Do not spend too much time intensively profiling the program; simply comparing the different implementations will be sufficient.
* Present your findings in tables or charts showing the relationship between:

  * Number of threads
  * Execution time
  * Estimated value of π
  * Speedup and efficiency metrics
  * etc


## Deliverables

1. **Source Code**

   * `pi_seq.c`: Sequential implementation.
   * `pi_pthread.c`: Multithreaded implementation.
   * Additional versions demonstrating optimization attempts.

2. **Performance Report**

   * Description of methodology and algorithm design.
   * Tables and plots of results.
   * Discussion of thread scalability, accuracy, and race condition handling.
   * Explanation of optimization approaches and their impact.


## Recommendations

* Use the `rand()` or `drand48()` function for random point generation.
* Protect shared variables (like the total count) using mutexes or atomic operations.
* Consider using **thread-local storage** for better scalability.
* Ensure reproducibility by controlling random seeds per thread.
* Comment code thoroughly and justify design decisions in your report.


## Ethics & Academic Integrity

This homework must reflect **your own work**. While discussions with classmates about general concepts are encouraged, all submitted code, scripts, reports, and analysis must be authored individually.  

- **Do not copy** solutions, scripts, or reports from other students, online sources, or prior years.  
- **Do not share** your own completed solutions with others before the submission deadline.  
- **Always cite** external sources (papers, documentation, tutorials) if you use them to inform your work.  
- **Profiling results must be your own.** Running the provided program and collecting data on your own machine is part of the assignment; submitting fabricated or borrowed results is considered misconduct.  

Violations will be treated as academic dishonesty and handled according to university policy.  

> When in doubt: ask questions, collaborate conceptually, but write and submit your **own independent work**.

