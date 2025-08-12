# ProcMemScan: Parallel Process Memory Analyzer 🔍

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)

A high-performance Linux tool for analyzing process memory usage by scanning `/proc/<pid>/maps` with multi-threaded efficiency.

![Sample Output](./assets/proc_scan.png) 

## What is does?
- Lists all running processes (/proc).

- For each process, reads /proc/<pid>/maps.

- Identifies memory segments: [heap], [stack], file-mapped, anonymous.

- Spawns multiple threads to analyze PIDs in parallel.

- Prints summary



## Features 
- **Parallel scanning** (2.8x faster than single-threaded)
- **Memory categorization**: Heap, Stack, Mmap (file/anon)
- **Low-overhead**: <3% CPU during full system scan
- **Clean terminal UI** with adaptive column formatting
- **Zero dependencies** (pure C++17)

## Installation ⚙️
```bash
git clone https://github.com/rudraThakar/Memory_analyzer.git
cd Memory_analyzer
make
./Memory_analyzer
