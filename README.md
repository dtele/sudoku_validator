## Sudoku Solution Validator
### Introduction
This assignment (CSD204: Operating Systems) attempts to compare the performance of the threading libraries 
pthread and OpenMP using the problem outlined in "Abraham Silberschatz. 2018. Operating System Concepts. 
10th ed. P-25."

### Problem
For a given N X N sudoku, where N is a square, there will be N rows, N columns and N
grids to be validated as shown below.

Validation Condition:- For a N X N sudoku, the validation condition is:
- Each row contains unique values from [1, N].
- Each column contains unique values from [1, N].
- Each of the nXn sub-grids, contains a unique value from [1, N] where, N = n<sup>2</sup>

For example:- For 4X4 sudoku, you need to check each row, each column and each of
the four 2X2 subgrids have values from 1 to 4.

### Experiments
There are two experiments given in the assignment which are to be performed without considering early termination:
 - In the first experiment, you have to keep the number of threads constant say 16 and compare the performance 
   by varying the size of the sudoku (4X4, 9X9, 16X16, 25X25, 36X36, 49X49 and 64X64).
 - In the second experiment, you have to keep the size of the sudoku constant 25X25 and compare the performance 
   by varying the number of threads from 2 to 32 in multiples of 2.

### Solution
The sudoku validator itself is made purely in C++:
- "base.hpp" contains helper functions to get the rows, 
columns and grids of the sudoku. 
- "nonthreads.cpp", "pthread.cpp", "openmp.cpp" all contain code to call these
functions and implement different multi-threading techniques.

Other tasks implemented in python include: 
- "gen.py" is a CLI application to generate random sudoku solutions for testing. Example usage:
```py gen.py -n 16 -t 4 -f sudoku.txt```
- "experiment.py" calls all other files to perform the experiments outlined above and graph the results.

Each observation taken for the experiments are averaged over 1000 runs to minimize outliers.


### Results
Fig1.(a) Experiment 1
![Fig1.(a) Experiment 1](https://github.com/dtele/sudoku_validator/blob/main/results/exp_1.png?raw=true "Fig1.(a) Experiment 1")
Fig1.(b) Experiment 1 (logarithmic scale)
![Fig1.(b) Experiment 1 (logarithmic scale)](https://github.com/dtele/sudoku_validator/blob/main/results/exp_1_log.png?raw=true "Fig1.(a) Experiment 1 (logarithmic scale)")
Fig2.(a) Experiment 2
![Fig2.(a) Experiment 2](https://github.com/dtele/sudoku_validator/blob/main/results/exp_2.png?raw=true "Fig1.(a) Experiment 2")
Fig2.(b) Experiment 2 (logarithmic scale)
![Fig2.(b) Experiment 2 (logarithmic scale)](https://github.com/dtele/sudoku_validator/blob/main/results/exp_2_log.png?raw=true "Fig1.(a) Experiment 2 (logarithmic scale)")

### Analysis
In Fig.1(a) I observed that while the time taken for non-threaded validation rises as the size of the
sudoku increases, it stays almost constant for both pthread and OpenMP as the overhead to start
and synchronize the threads is very large in comparison. In both Fig.1(a) and Fig.1(b) I saw that the
overhead in pthread is larger compared to OpenMP.

In Fig.2(a) I see that as the number of threads rise, the time increases which is contrary to intuition
but can be explained by the same overhead per thread. In Fig.2(b) it is evident that OpenMP is
optimized better for higher number of threads, but pthread rises very fast as the number of threads,
k, increases.

### Conclusions
It can be concluded that pthread has significantly higher overhead per thread than OpenMP.

It can also be concluded that it is not beneficial to utilize multithreading for such simple tasks in
modern processors, as the overhead to start, synchronize, and collect each thread proves to be
counter productive as the task being multithreaded (checking n numbers) is trivial (can be computed
in O(n))and for a maximum value of n=64, in modern processors with clock speeds reaching 4-5GHz,
can be computed almost instantaneously.