# Homework 3 – CUDA Programming
**Due Date:** December 18, 2025 

This homework contains **three separate CUDA problems**. Below is a simplified summary of what each task requires.



## Problem 1 – Block‑Based Image Coloring

* You generate an **N×N RGB image** using CUDA.
* Each **block** chooses one random color, and all threads in that block fill their pixels with it.
* First use a simple setup (`1 thread per block`, `N×N` blocks).
* Then test **different block sizes** (static + dynamic tiling).
* Submit: your code + a few output images.



## Problem 2 – Masked Computation & Divergence

You compute:

* `B[i] = A[i] * 10` if `A[i]` is even
* `B[i] = A[i]` if `A[i]` is odd

### Part 1

* Implement using a normal `if/else`.
* Profile the kernel and explain **warp divergence**.

### Part 2

* Fix divergence by changing **indexing**, not the math:

  * Blocks handle only **even** or only **odd** indices.
* Compare performance with Part 1.

### Part 3

* Test multiple **block sizes** and measure time.

Submit: baseline + improved kernel, brief explanation, profiling results.



## Problem 3 – Parallel Rasterization

You draw **lines, circles, and ellipses** into an `N×N` black‑and‑white image.

* Implement CUDA kernels for each shape (or one unified kernel).
* Use **distance formulas** + a **thickness parameter**.
* Convert thread indices → pixel coordinates → draw.
* Call the provided `draw_shape()` to generate the final image.
* Test different resolutions and block sizes; briefly report performance.

Submit: code + small report + sample images.



## Final Submission Checklist

* Code for all 3 problems
* Simple documentation for each problem
* Required images and profiling tables

Keep the write‑ups short—just explain what you did and show your results.

## Academic Integrity
All work must be your own. Profiling results must be collected on your own machine. Cite any references you use.
