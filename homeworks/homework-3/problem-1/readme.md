# Introduction to CUDA: Block-Based Image Coloring
**Prepared & Supported by:**  Raha Rahmanian  
**Due date:** December 18, 2025

## Objective


The objective of this homework is to help you become familiar with CUDA programming by writing a simple program that uses fundamental CUDA concepts and functions. In this assignment, you will generate and color an N × N image matrix using a block-based (tiled) approach inspired by CUDA’s execution model. Additionally, this homework is designed to give you hands-on experience with copying data between CPU and GPU memory, initializing threads, and managing thread and block execution, so that you gain a practical introduction to how CUDA handles parallel computation.

This assignment will also give you understanding of how tiling works in CUDA and **how different block configurations affect workload distribution**. By visualizing the output, you will clearly see how block size and layout influence which portions of the matrix are handled together, helping you build intuition about how CUDA schedules work across blocks and threads.

## Part 1 - Baseline Implementation
1. Initialize an N×N matrix on the CPU.
    -  The matrix must be created using the Pixel structure provided in the header file.
    - Each Pixel contains three unsigned char values representing the red (r), green (g), and blue (b) color channels.
2. Allocate memory for the matrix on the GPU.
3. Copy the matrix data **from CPU memory to GPU memory**.
4. Launch a CUDA kernel such that:
   - A single random RGB color is generated **per block**.
   - All **threads inside the same block** write the **same RGB color** to their corresponding matrix elements.
   - Different blocks must generate and use different random colors, resulting in visible color tiles in the output image.
    - For this part of the homework you must use the tiling configuration below:
        - Each block contains exactly one thread.
        - Each thread is responsible for coloring a single pixel in the matrix (So you need NxN blocks).
        - CUDA block setup example:
      
            ```c
            myKernel<<<N*N, 1>>>(deviceMatrix, N);
            ```
          
5. Copy the modified matrix data from GPU memory back to CPU memory.
6. Use the provided color(matrix,N) function from the color_the_matrix.h file to visualize. This function will save the resulting image as "output.bmp" in the same folder.
### Note

Your program must work for **any N**, for example:

```c
#define N 1000
```

You must **not assume N is divisible by your block dimensions**.



## Part 2 - Block size experiments
In the second part of this assignment, you are required to experiment with different block sizes and observe how block configuration affects the generated image.

**Required Experiments**:

You only need to submit three images: one using a static block size and two using dynamic block sizes (with strategy of your choice).
### 1. Static Block Size Example:
```c
#define BLOCK_X 32
#define BLOCK_Y 32
```
### 2. Dynamic Block Sizes Based on N:
Examples of valid strategies:

Example Tiling Strategies

**Strategy A — One row per block**
- Block size: `1 × N`
- Number of blocks: `N`

Visual:
```
████████
████████
████████
```

Each row has its own color.



**Strategy B — One column per block**
- Block size: `N × 1`
- Number of blocks: `N`


**Strategy C — Square tiling based on N**

```c
int blocksPerDim = sqrt(N);   // or any logic you justify
```
Then:
```c
blockWidth  = N / blocksPerDim;
blockHeight = N / blocksPerDim;
```

Deliverables:
  - Your program.
  - The block sizes and tiling strategy you used + Screenshots of the output images for each configuration.

