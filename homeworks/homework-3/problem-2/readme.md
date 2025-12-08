# HW3-Masked Computation
**Prepared & Supported by:**  Raha Rahmanian  
**Due date:** December 18, 2025
## Problem Overview
In this assignment, you will implement a CUDA kernel that applies a simple conditional transformation to an input array and investigate how GPU execution behavior and block size affects performance.
## Task

You are given an input array **A** of size **N** (chosen at runtime).
Compute the output array **B** as:

    B[i] = A[i] * 10   if A[i] is even
    B[i] = A[i]        if A[i] is odd



## Part 1 - Baseline Implementation

1.  Allocate **A** on the host and fill it with values.
2.  Allocate device arrays and copy **A** to the GPU.
3.  Launch **exactly one kernel** that computes `B[i]` using a normal
    `if/else` branch.
4.  Copy the result back.
5.  Identify the issue that is caused when you use this approach. 
6.  Profile using `nvprof` (or Nsight) and explain:
      -   What happens at the warp level when threads take different
        branches
      -   Explain how it effects performance 



## Part 2 - Eliminating the issue
Rewrite the GPU kernel so that the previous issue is eliminated without changing the mathematical operation.
You should change only the **indexing strategy**, not the computation itself.

Map threads such that each block processes either: 
  - **only
even indices**, or
  - **only odd indices**


1. Profile again and compare your results to Part 1.
2. Explain why the new indexing avoids the issue.



## Part 3 - Block Size Performance Comparison

Evaluate how **different block sizes** affect performance **only for the second
version** of your kernel.

Tip: - Choose a **large** N so timing differences are
measurable
1. Test **multiple block sizes of your choice**
2. Record execution time for each block size using `nvprof` or Nsight
3. Compare performance across block sizes

Deliverables: 
- your program for parts 1 and 2.
- Documentation: All of the required results, profiles, explanations and comparisons using plots.
