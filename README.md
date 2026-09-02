# SYCL Vector Addition

A C++ project demonstrating parallel vector addition using the SYCL standard via Intel® oneAPI. This project showcases Heterogeneous Parallel Programming by offloading array element computations from the CPU to an accelerator device (GPU), utilizing SYCL buffers, accessors, and parallel execution pipelines.

![Execution Screenshot](asset/screenshot.png)

---

## 🛠️ Prerequisites & Requirements

To build and run this project, you need:
- **Intel® oneAPI Base Toolkit** (includes the `icpx` DPC++/C++ compiler).
- A compatible GPU or CPU runtime for SYCL execution.
- Command Prompt / PowerShell configured with oneAPI environment variables.

---

## 🚀 Building & Running with `icpx`

Follow these step-by-step instructions to compile and execute the project into `sycl.exe` on Windows:

### Step 1: Open Intel oneAPI Command Prompt
Launch the **oneAPI command prompt** or set up the environment variables in your existing terminal by running:

```cmd
"C:\Program Files (x86)\Intel\oneAPI\setvars.bat"
```

### Step 2: Compile the Code
Use the `icpx` compiler (Intel DPC++/C++ Compiler) with SYCL support enabled (`-fsycl`) to compile `sycl.cpp` into `sycl.exe`:

```cmd
icpx -fsycl sycl.cpp -o sycl.exe
```

### Step 3: Execute the Binary
Run the compiled executable from your command line:

```cmd
.\sycl.exe
```

**Expected Output:**
```text
[C++ SYCL] Running vector addition on GPU...
Result c[0] = 3 (Expected: 3.0)
```

---

## 💡 How the Code Works

The program performs parallel element-wise addition of two large arrays (1,000,000 single-precision floating-point numbers) using SYCL abstractions:

1. **Queue Creation (`sycl::queue`):**  
   Instantiates a SYCL execution queue requested for a GPU (`sycl::gpu_selector_v`). The queue encapsulates the target execution context and command dispatching mechanisms.

2. **Data Initialization:**  
   Allocates three standard C++ dynamic arrays (`std::vector<float>`) in host memory (`a`, `b`, and `c`), initializing vector `a` with `1.0f` and vector `b` with `2.0f`.

3. **Buffer Management & Scoped Synchronization:**  
   Wraps host vectors in `sycl::buffer` objects (`buf_a`, `buf_b`, `buf_c`). Buffers manage data ownership and facilitate transparent data transfers between host (CPU) and device (GPU) memory space. When the buffer scope closes, modified data automatically syncs back to the host vector `c`.

4. **Command Group Submission (`q.submit`):**  
   Defines a task graph node via a lambda expression. Accessors (`sycl::accessor`) specify access modes (`read_only` for `a` and `b`, `write_only` for `c`) to enforce dependency tracking and prevent memory race conditions.

5. **Parallel Kernel Execution (`h.parallel_for`):**  
   Dispatches a 1D range kernel (`sycl::range<1>(1000000)`) across GPU execution threads. Each work-item independently computes `acc_c[i] = acc_a[i] + acc_b[i]`, achieving massive parallelism
