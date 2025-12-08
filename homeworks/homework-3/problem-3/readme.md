# HW2 – Parallel Rasterization
**Prepared & Supported by:** Sina Hakimzadeh  
**Due Date:** December 18, 2025

## Overview

The earliest and most fundamental application of GPUs was accelerating the rendering of on-screen images to achieve smoother, more realistic visual output. In this assignment, you will implement a GPU-based program capable of drawing various geometric shapes using CUDA and the parallel programming techniques introduced in class. The primary goal is to strengthen your foundational CUDA programming skills rather than to provide a comprehensive introduction to modern rasterization pipelines or highly optimized rendering methods.

## Line Drawing Algorithm

Screens consist of discrete pixels, while geometric curves are defined in continuous space. To approximate any continuous curve using pixels, we evaluate how close each pixel center is to the ideal mathematical shape and activate it if this distance is sufficiently small.

A line expressed in implicit form is:

$$
ax + by + c = 0
$$

For a pixel center $(x_0, y_0)$, the perpendicular distance to the line is:

$$
d = \frac{|a x_0 + b y_0 + c|}{\sqrt{a^2 + b^2}}
$$

In a sequential implementation, we iterate through the relevant pixel region, compute this distance, and activate the pixel if $d < 0.5$.

## Circle Drawing Algorithm

The same distance-based idea extends naturally to circles.
A circle centered at $(h, k)$ with radius $r$ is defined by:

$$
(x - h)^2 + (y - k)^2 = r^2
$$

To determine how close a pixel $(x_0, y_0)$ is to the circle boundary:

$$
d = \left| \sqrt{(x_0 - h)^2 + (y_0 - k)^2} - r \right|
$$

This $d$ represents how far the pixel is from the ideal radius.
Using the same threshold idea as in line drawing, we activate the pixel if $d < 0.5$.
Because of circular symmetry, the search can be limited to the bounding square $[h-r,,h+r] \times [k-r,,k+r]$.

## Ellipse Drawing Algorithm

Ellipses follow exactly the same principle but use a stretched geometry.
For an ellipse centered at $(h, k)$ with radii $a$ (horizontal) and $b$ (vertical):

$$
\frac{(x - h)^2}{a^2} + \frac{(y - k)^2}{b^2} = 1
$$

For a pixel center $(x_0, y_0)$, compute:

$$
E = \frac{(x_0 - h)^2}{a^2} + \frac{(y_0 - k)^2}{b^2}
$$

Points on the exact boundary satisfy $E = 1$, so we define:

$$
d = |E - 1|
$$

If $d$ is below a small threshold (e.g., $0.05$–$0.1$), the pixel is considered part of the ellipse boundary.
The search region is the bounding rectangle $[h-a,,h+a] \times [k-b,,k+b]$.

## Summary

Lines, circles, and ellipses all follow the **same conceptual framework**:

* Define the geometric object mathematically.
* Compute a distance-like measure for each pixel that indicates how close it is to the ideal curve.
* Activate the pixel if this distance is within an acceptable tolerance.

This unified distance-based approach allows you to implement these shapes easily in both sequential and parallel (CUDA) environments, and it provides a clear conceptual bridge between continuous mathematics and discrete rasterization.

## Tasks

### Shape Specification Format

For this assignment, each shape is specified using the following formats:

* **Line:** parameters (a, b, c) for the implicit equation ax + by + c = 0, plus a **thickness** parameter t.
* **Circle:** center (h, k), radius r, and a **thickness** parameter t.
* **Ellipse:** center (h, k), radii (a, b), and a **thickness** parameter t.

The thickness parameter t controls how wide the boundary of the shape appears. For example:

* Lines activate pixels where the computed distance d is less than t.
* Circles activate pixels where the absolute difference between the pixel radius and r is less than t.
* Ellipses activate pixels where the absolute difference between E and 1 is less than t.

This enables comparison of visual quality and allows students to observe how increasing thickness affects GPU workload and utilization.

These parameters will be passed from the CPU to your shape-dispatch function, which must launch the correct CUDA kernel.
For this assignment, each shape is specified using the following parameter formats:

* **Line:** coefficients $(a, b, c)$ representing the implicit equation $ax + by + c = 0$.
* **Circle:** center $(h, k)$ and radius $r$.
* **Ellipse:** center $(h, k)$ and radii $(a, b)$.

These parameters will be passed from the CPU to your shape-dispatch function, which must launch the correct CUDA kernel.

### Frame Generation Simplicity

To keep this assignment focused on CUDA fundamentals and avoid external dependencies such as OpenGL, your program will rasterize **one static frame** per execution. The resulting $N 	imes N$ raster is written to an image file by the provided `draw_shape` function.
This homework does *not* require animation, real-time rendering, or interactive windows.

### Coordinate System and Data Representation

1. You are given a screen of resolution $N \times N$. The value of $N$ is defined in the provided starter code.
2. You must represent the screen as a **1D integer array** of size $N \times N$:

   ```c
   int arr[N * N];
   ```

   Each entry of this array corresponds to a single pixel on the screen.
3. The screen coordinate system is **centered**:

   * The middle of the screen is considered $(0, 0)$.
   * Coordinates range approximately from $-N/2$ to $N/2 + 1$ in both $x$ and $y$ directions (follow the exact convention described in the provided code/comments).
4. Each pixel is **black-and-white**:

   * Use one value (e.g., `0`) for background (off).
   * Use another value (e.g., `1`) for foreground (on, part of the shape).
     Check the provided code to match whatever convention `draw_shape` expects.

You are responsible for mapping between:

* array indices in `arr` (e.g., `arr[row * N + col]`), and
* the corresponding screen-space coordinates $(x, y)$ used in the distance formulas above.

### CUDA Kernels for Shape Rasterization

Your main programming task is to implement **CUDA kernels** that fill the $N \times N$ array using the distance-based rasterization rules for:

1. Line
2. Circle
3. Ellipse

Requirements:

1. **Three kernels (or one parametrized kernel)**
   Implement CUDA kernels that can:

   * Compute, in parallel, whether each pixel belongs to the given line, circle, or ellipse.
   * Write the corresponding black/white value into `arr`.

   A common design is:

   * One kernel for each shape (e.g., `line_kernel`, `circle_kernel`, `ellipse_kernel`), or
   * A single kernel that receives a "shape type" flag and corresponding parameters.

2. **Shape parameters as input**
   On the CPU side, write a function (e.g., `rasterize_shape(...)`) that:

   * Takes as input:

     * The shape type (line / circle / ellipse).
     * The shape parameters (e.g., two endpoints for a line, center and radius for a circle, etc.).
   * Based on the shape type, launches the appropriate CUDA kernel with the correct parameters and grid/block configuration.

3. **Distance-based decision per pixel**
   In each kernel:

   * Map the thread ID(s) to pixel indices $(i, j)$ and then to coordinates $(x_0, y_0)$ using the centered coordinate system.
   * Compute the distance-like measure $d$ using the formulas described in the algorithm sections.
   * If $d$ is below the chosen threshold, write the foreground value (shape pixel) into `arr`; otherwise, write the background value.

4. **Memory management**
   On the host side:

   * Allocate device memory for the array.
   * Copy necessary parameters to the device if needed.
   * Launch the kernel(s).
   * Copy the resulting `arr` back from device to host.

### Integration with the Provided Visualization Function

A CPU-side function is provided in the assignment directory:

```c
void draw_shape(int arr[N * N]);
```

You **must not modify** the implementation of this function.

Your code should:

1. Initialize and clear `arr` on the host.
2. Call your CUDA-based rasterization function to fill `arr` according to the chosen shape and its parameters.
3. After the GPU computation completes and the data is copied back to the host, call:

   ```c
   draw_shape(arr);
   ```

This function will display the resulting black-and-white image so you can visually verify correctness for lines, circles, and ellipses at different positions and sizes.

To help you become familiar with the function interface and ensure everything is working before you begin implementing your CUDA kernels, the assignment directory also includes a **simple test `main.c` and Makefile**. These allow you to quickly compile and run a minimal example that generates an output image using the provided `draw_shape` function. You should run this test setup first to confirm your environment is configured correctly before starting your own development.

## Performance & Profiling Requirements

Although heavy optimization is not required, you must still evaluate how your implementation behaves under different workloads.

### 1. Test Large Resolutions

Run your program with several values of $N$ (e.g., 256, 512, 1024, or larger if your GPU allows). Record how performance changes with size.

### 2. Experiment with CUDA Configurations

Try different block and grid sizes—for example:

* $8 	imes 8$
* $16 	imes 16$
* $32 	imes 32$

Measure the execution time for each configuration.

### 3. Measure GPU Utilization

Use available tools such as:

* `nvidia-smi`
* Nsight Systems
* Nsight Compute

Record observations such as:

* Kernel execution time
* GPU utilization percentage
* How performance scales with N
* Whether certain block sizes perform better

Summaries of these findings must appear in your final submission.

## Deliverables

Your submission must include not just code, but clear **documentation** explaining what you implemented, how you tested it, and what results you observed.

### 1. Code Submission

* All CUDA and C/C++ source files required to build and run your rasterizer.
* Do **not** modify the provided `draw_shape` function.

### 2. Documentation (README or report)

You must write a short but complete documentation describing:

* **Build instructions:** how to compile and run your program, including compiler commands, flags, and any environment requirements.
* **Implementation explanation:** what you implemented, how your kernels are structured, how you handle coordinate mapping, and how the thickness parameter is applied.
* **Design decisions:** any choices you made (e.g., kernel layout, threshold selection, handling of coordinate centering).
* **Performance discussion:** the results of your profiling experiments—how different values of N, thickness t, and block configurations affected runtime and GPU utilization.

### 3. Output Samples

Include sample images generated by your program:

* At least **one line**, **one circle**, and **one ellipse**, each rendered with different parameter settings (e.g., different radii, positions, and thickness values).
* Brief explanations of each output image: what settings you used, and whether the rendering matches your expectations.

These samples and explanations should demonstrate that your kernels work correctly for a variety of shapes and parameters.

### 4. Performance Summary

Provide a concise summary of:

* The values of N you tested.
* Kernel launch configurations you tried.
* Execution times and GPU utilization observations.
* Any trends or conclusions you were able to draw.

This documentation ensures we can understand, reproduce, and evaluate your work.

At minimum, your submission should include:

* **Source code files**

  * CUDA implementation (e.g., `.cu` files).
  * Any additional C/C++ files needed to compile and run your solution.

* **Build instructions**

  * A short `README` describing how to compile and run your program (compiler, flags, and example command).

* **Sample screenshots or description (optional but recommended)**

  * Evidence that your program correctly renders at least:

    * One line,
    * One circle,
    * One ellipse,
      using different parameter settings.

## Ethics & Academic Integrity

This homework must reflect **your own work**. While discussions with classmates about general concepts are encouraged, all submitted code, scripts, reports, and analysis must be authored individually.

* **Do not copy** solutions, scripts, or reports from other students, online sources, or prior years.
* **Do not share** your own completed solutions with others before the submission deadline.
* **Always cite** external sources (papers, documentation, tutorials) if you use them to inform your work.
* **Profiling or performance results must be your own.** Running your program and collecting data on your own machine is part of the assignment; submitting fabricated or borrowed results is considered misconduct.

Violations will be treated as academic dishonesty and handled according to university policy.

> When in doubt: ask questions, collaborate conceptually, but write and submit your **own independent work**.
