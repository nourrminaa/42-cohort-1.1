# push_swap

*This project was developed as part of the 42 curriculum by **nmina** and **szaarour**.*

---

## Description

**push_swap** is an algorithmic sorting project that focuses on sorting a stack of integers using only two stacks (`a` and `b`) and a strictly limited set of allowed operations.

The goal is to output the **shortest possible sequence of operations** that sorts the input stack in ascending order. To achieve this, the program implements **four distinct sorting strategies**, each with a different time complexity, and dynamically selects the most efficient one based on input disorder.

The project also includes:
- A **disorder metric** to determine how unsorted the input is
- An **adaptive algorithm** that selects the optimal strategy automatically
- A **benchmark mode** (`--bench`) to analyze performance and operation counts

---

## Allowed Operations

Only the following operations are permitted:

| Operation | Description |
|---------|-------------|
| `sa`, `sb` | Swap the first two elements of stack `a` / `b` |
| `pa`, `pb` | Push the top element from one stack to the other |
| `ra`, `rb` | Rotate stack up (first element becomes last) |
| `rra`, `rrb` | Reverse rotate stack down (last element becomes first) |
| `ss`, `rr`, `rrr` | Perform the corresponding operation on both stacks |

All operations are implemented in `instructions.c` and `operations.c`.

---

## Sorting Strategies

Four sorting strategies are available and selectable via command-line flags:

| Strategy | Flag | Complexity | Use Case |
|--------|------|------------|---------|
| Simple | `--simple` | O(n²) | Small or nearly sorted inputs |
| Medium | `--medium` | O(n√n) | Moderately disordered inputs |
| Complex | `--complex` | O(n log n) | Large, random inputs |
| Adaptive | `--adaptive` | Varies | Chooses strategy based on disorder (default) |

---

## Disorder Metric

Before sorting, the program computes a **disorder value** between `0` and `1`:

```c
disorder = (number of inverted pairs) / (total possible pairs)
```


- `0` means the stack is already sorted
- `1` means the stack is completely reversed

This metric is used by the adaptive algorithm to select the most appropriate sorting strategy.

---

## Algorithm Details

### Simple Strategy – Insertion Sort (O(n²))

- Repeatedly finds the smallest element in stack `a`
- Rotates it to the top and pushes it to stack `b`
- Once `a` is empty, pushes everything back from `b` to `a`

Efficient for small input sizes but not suitable for large stacks.

---

### Medium Strategy – Bucket Sort (O(n√n))

- Divides the value range into `√n` buckets
- Pushes elements from `a` to `b` based on bucket ranges
- Uses rotations to optimize pushes
- Pushes elements back from `b` to `a` in sorted order

Balances efficiency and simplicity for medium-sized inputs.

---

### Complex Strategy – Radix Sort (O(n log n))

- Indexes stack values based on their sorted order
- Uses Quick Sort under the hood to index values
- Technically, it is sorting the indexes
- Repeats for all indexes and repushes from `b` after each pass

Provides consistent performance for large inputs.

---

### Adaptive Strategy

The adaptive strategy selects an algorithm based on disorder:

| Disorder Range | Selected Strategy |
|---------------|------------------|
| `< 0.2` | Insertion Sort |
| `< 0.5` | Bucket Sort |
| `≥ 0.5` | Radix Sort |

This approach minimizes operations while maintaining scalability.

---

## Compilation & Usage

### Compile

```bash
make
```

### Run

```bash
./push_swap 3 2 5 1 4
```

### Select Strategy

```bash
./push_swap --simple 3 2 5 1 4
./push_swap --medium 3 2 5 1 4
./push_swap --complex 3 2 5 1 4
./push_swap --adaptive 3 2 5 1 4
```

### Benchmark Mode

```bash
./push_swap --bench 3 2 5 1 4 2> bench.txt
```

Outputs disorder value, chosen strategy, and operation count to `stderr`.

---

## Checker

### Give Executable Permissions to the Checker

```bash
chmod +x checker_name
```

### Run the Checker

```bash
./push_swap 5 4 3 2 1 | ./checker_name 5 4 3 2 1
```

### Expected Output

```nginx
OK
```

---

## AI Usage

AI was used for:

- Algorithm explanation and validation  
- README structuring and organization  
- Debugging and understanding `valgrind` outputs

All code was written, tested, and reviewed manually by both contributors.

---

## Contributors

### nmina
- Designed validation logic 
- Handled error management for invalid input, duplicates, and overflows
- Developed stack operation helpers
- Implemented adaptive algorithm selection      

### szaarour
- Developed input parsing 
- Implemented radix sort logic for large input sizes  
- Implemented the bucket sort strategy
- Built benchmarking utilities to measure operation counts and performance   

Both contributors actively participated in debugging, extensive testing across edge cases, performance optimization, and project documentation.

---

**Authors:** Serena Zaarour, Nour Mina <br>
**Intra:** szaarour, nmina <br>
**Cohort:** 1.1  
**42 Campus:** Beirut  
**Milestone:** 1  

---

