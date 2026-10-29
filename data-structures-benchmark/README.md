# Linked List vs. Hash Table Benchmark

C++ implementations of a sorted doubly linked list and a hash table with separate chaining, benchmarked against each other on the same insert / delete / retrieve workloads.

## Overview

This project implements two ways to store records keyed by a 9-digit ID: a sorted doubly linked list and a hash table with 10,007 buckets and separate chaining. Both are driven by the same command file of inserts, deletes, and retrievals and timed with `clock()`. At 60,000 operations the linked list took 3.62 s and the hash table 0.012 s, about 300x faster, and the gap grew with input size.

## Project structure

```
data-structures-benchmark/
├── README.md
├── .gitignore
├── gen_input.py            # generates random benchmark input files
├── linked-list/
│   ├── DLL.h               # Node struct + DLL class declaration
│   ├── DLL.cpp             # sorted doubly linked list implementation
│   ├── main.cpp            # benchmark driver
│   └── test.cpp            # small functional test
├── hash-table/
│   ├── node.h              # templated singly linked list node
│   ├── SLL.h               # templated singly linked list (the buckets)
│   ├── hashTable.h         # templated hash table, separate chaining
│   ├── main.cpp            # benchmark driver
│   └── test.cpp            # compile/instantiation smoke test
└── docs/
    ├── linkedlist-pseudocode.pdf
    └── hash-pseudocode.pdf
```

## Build and run

Requires `g++` with C++17 support (MinGW on Windows, or any Linux/macOS/WSL setup).

```bash
# linked list
cd linked-list
g++ -std=c++17 -O2 -Wall -Wextra main.cpp DLL.cpp -o list_bench

# hash table
cd ../hash-table
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o hash_bench
```

Generate an input file, then pass it to either program:

```bash
python gen_input.py 60000 > input_60000.txt

./linked-list/list_bench input_60000.txt
./hash-table/hash_bench input_60000.txt
```

On Windows PowerShell, use `.\linked-list\list_bench.exe` and generate the input with
`python gen_input.py 60000 | Out-File -Encoding ascii input_60000.txt` (a plain `>` writes UTF-16, which the programs can't read).

To build the small tests (separate from the benchmarks, since each has its own `main`):

```bash
cd linked-list
g++ -std=c++17 test.cpp DLL.cpp -o test_list && ./test_list
```

Both benchmarks print the number of valid insertions, deletions, and retrievals, the final item count, and the elapsed time. On the same input the counts from the two programs should match.

## Input format

A plain text file, one command per line:

```
<op> <SSN> <FIRST> <LAST>
```

| Field | Meaning |
|-------|---------|
| `op` | `i` insert, `d` delete, `r` retrieve |
| `SSN` | 9-digit ID, used as the key |
| `FIRST` `LAST` | two whitespace-free name tokens |

Example:

```
i 545309496 JANNET THOMURE
i 912741495 LIZABETH HOSNER
r 545309496 JANNET THOMURE
d 912741495 LIZABETH HOSNER
```

Behavior:
- An insert of a key that already exists is rejected and not counted.
- A delete or retrieve is counted only if the key is present.
- Any other `op` prints `Unknown command`.

`gen_input.py N [seed]` writes N random commands (about 60% inserts, 20% deletes, 20% retrievals of existing keys). All data is randomly generated; no real SSNs are used.

## Results

Measured on [AMD Ryzen 7 5800X / 16 GB RAM / Windows 10], g++ 14.2.0, flags `-std=c++17 -O2`. Each time is the median of 3 runs, measured with `clock()`. Timing includes reading and parsing the input file for both programs.

| Operations (N) | Linked list (s) | Hash table (s) | Hash table speedup |
|---------------:|----------------:|---------------:|-------------------:|
| 1,000          | < 0.001         | < 0.001        | not measurable     |
| 10,000         | 0.046           | 0.002          | ~23x               |
| 60,000         | 3.620           | 0.012          | ~300x              |

Both programs reported identical insertion, deletion, retrieval, and final item counts on every input (for example, 36,033 / 11,993 / 11,974 / 24,040 at 60,000 operations).

## Analysis

At 1,000 operations both programs finish in under a millisecond, so `clock()` cannot separate them. At 10,000 operations the hash table is about 23x faster (0.002 s vs. 0.046 s), and at 60,000 operations about 300x faster (0.012 s vs. 3.62 s).

Going from 10,000 to 60,000 operations (6x more work) increased the hash table's time about 6x, consistent with roughly linear growth when chains stay short: the final table held 24,040 items in 10,007 buckets, about 2.4 per bucket. The linked list's time grew about 79x for the same 6x increase. Every operation walks a list whose length grows with the input, so quadratic growth (about 36x) is the expected baseline; the extra growth is plausibly cache effects from chasing pointers through a large list, though I did not profile it.

The hash table's speedup is probably understated: both programs include the time to read and parse the input file, a fixed cost that makes up a large share of the hash table's 12 ms. Other caveats: one machine, a 1 ms timer resolution (so the 10,000-operation ratio is approximate), and randomly generated data.

## Implementation notes

**Sorted doubly linked list (`linked-list/`)**
- Nodes are kept in increasing SSN order. Insert walks the list to find the position (and detect duplicates), so insert, search, and delete are all O(n).
- Doubly linked so a found node can be unlinked without tracking a separate previous pointer.
- The copy constructor builds a deep copy in O(n) using a tail pointer; the destructor frees every node.

**Hash table with separate chaining (`hash-table/`)**
- `HashTable<V>` is a template over an integral key type. The bucket index is `key % tableSize`, with `tableSize = 10007` (a prime) in the benchmark.
- Each bucket is a templated singly linked list (`SLL`). New nodes are added at the head, since bucket order doesn't matter.
- Insert checks the bucket for a duplicate first, so the cost is proportional to the bucket length. With n items in 10,007 buckets, the expected chain length is about n / 10007.
- Memory: `SLL` and `HashTable` have destructors that free all nodes and the bucket array. Copying is deleted to prevent double frees.

## Limitations and future work

- The hash table's size is fixed, so chains grow linearly with n; resizing/rehashing at a load-factor threshold would keep them short.
- Keys must be non-negative integers (negative keys would produce a negative bucket index), and SSNs are parsed as `int`, so they must be 9 digits.
- `clock()` is coarse at small N and includes file parsing time.
- A balanced tree (or `std::unordered_map` / `std::map`) would make a natural third comparison.

## Background

Written for Data Structures at The College of New Jersey, 2026. Starter code and the class interfaces were provided by the instructor; the implementations are my own.
