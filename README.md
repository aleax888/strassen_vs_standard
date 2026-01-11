# Merge Sort VS. Insertion Sort

This project benchmarks and compares the performance of **Merge Sort** and **Insertion Sort**.  
It is designed to measure execution time, analyze scalability, and visualize how both algorithms behave as the input size grows.

The project uses a **high-performance C++ benchmarking engine** to generate accurate timing data and a **Python plotting pipeline** to transform those results into clear and readable charts.

---

## 🚀 How to Run

This project is composed of **two main parts**:

1. A **C++ benchmarking program** that builds and runs sorting benchmarks.
    1. `make`
    2. `./build/exe`
2. A **Python plotting system** that generates graphs from the benchmark results.  
   1. `chmod +x run_plotting.sh`
   2. `./run_plotting.sh
`

Both parts must be executed in order.

---

## Dependencies

#### 1. C++ Benchmark Program

Dependencies:

- **g++** (with C++17 support)
- **make**
- A Linux or WSL environment

#### 2. Python Plotting System

Dependencies:

- python 3
- pip
- pandas
- matplotlib

---

## Folder structure

```
├── build/                       (created by Make)
│   ├── *.o
│   └── exe
│
├── outputs/
│   └── plots/                   (generated charts)
│
├── src/
│   ├── benchmark/
│   │   ├── *.cpp
│   │   ├── *.h
│   │   └── main.cpp
│   │
│   └── plotting/
│       ├── *.py
│       └── venv/                (created automatically)
│
├── tabuldated_values/
│   ├── brief_benchmark/         
│   └── full_benchmark/          
│
├── makefile
└── run_plotting.sh
```

---


```
 ███████████   ███                         ███████   
▒▒███▒▒▒▒▒███ ▒▒▒                        ███▒▒▒▒▒███ 
 ▒███    ▒███ ████   ███████            ███     ▒▒███
 ▒██████████ ▒▒███  ███▒▒███ ██████████▒███      ▒███
 ▒███▒▒▒▒▒███ ▒███ ▒███ ▒███▒▒▒▒▒▒▒▒▒▒ ▒███      ▒███
 ▒███    ▒███ ▒███ ▒███ ▒███           ▒▒███     ███ 
 ███████████  █████▒▒███████            ▒▒▒███████▒  
▒▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒  ▒▒▒▒▒███              ▒▒▒▒▒▒▒    
                    ███ ▒███                         
                   ▒▒██████                          
                    ▒▒▒▒▒▒                           
```