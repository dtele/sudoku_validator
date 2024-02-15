#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <pthread.h>
#include <vector>

#include <base.hpp>

#define REPEAT 1000


using namespace std;


int main() {
    int n, k;

    vector<int> sudoku_temp;
    ifstream fp;
    int token;
    fp.open("sudoku.txt");

    if (fp.is_open()) {
        fp >> k;
        fp >> n;
        while (fp) {
            fp >> token;
            sudoku_temp.push_back(token);
        }
    } else {
        cout << "Create sudoku.txt file using \"py gen.py -n N -t number_of_threads -f sudoku.txt\"";
        exit(0);
    }

    int sudoku[n * n];

    for (int i = 0; i < n * n; i++) {
        sudoku[i] = sudoku_temp.at(i);
    }

    bool valid = true;

    vector<vector<int>> jobs;

    for (const auto& row: get_rows(n, sudoku)) {
        jobs.push_back(row);
    }

    for (const auto& column: get_columns(n, sudoku)) {
        jobs.push_back(column);
    }

    for (const auto& grid: get_grids(n, sudoku)) {
        jobs.push_back(grid);
    }

    const auto start = chrono::high_resolution_clock::now();

    for (int iteration = 0; iteration < REPEAT; iteration++) {
        omp_set_num_threads(k);
#pragma omp parallel shared(n, valid, jobs) default(none)
        {
#pragma omp for
            for (const auto& job: jobs) {
                bool valid_local = validate(n, job);
#pragma omp critical
                {
                    valid &= valid_local;
                }
            }
        }
    }

    const auto end = chrono::high_resolution_clock::now();
    const chrono::duration<double> duration = end - start;

    if (valid) cout << "Valid." << endl;
    else cout << "Invalid." << endl;

    cout << "n: " << n << "\tk: " << k << endl;
    cout << "Time taken: " << duration.count() / REPEAT << " seconds" << endl;
}