#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <vector>

#include <base.hpp>

#define REPEAT 1000


using namespace std;


struct JobData {
    vector<vector<int>> rows{};
    int n{};
    bool* valid{};
};


void* validate_job(void* arg) {
    auto* job = static_cast<JobData*> (arg);

    for (const auto& row: job->rows) {
        *job->valid &= validate(job->n, row);
    }

    pthread_exit(nullptr);
    return nullptr;
}


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
    bool valid = true;
    vector<vector<int>> jobs;

    for (int i = 0; i < n * n; i++) {
        sudoku[i] = sudoku_temp.at(i);
    }

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

    pthread_t threads[k];
    JobData job_data[jobs.size()];
    const int jobs_per_thread = (int) jobs.size() / k;

    for (int iteration = 0; iteration < REPEAT; iteration++) {
        for (int i = 0; i < k && i < jobs.size(); ++i) {
            if (jobs.size() > k) {
                if (i == k - 1) job_data[i].rows = vector<vector<int>> (jobs.begin() + i * jobs_per_thread, jobs.end());
                else job_data[i].rows = vector<vector<int>> (jobs.begin() + i * jobs_per_thread, jobs.begin() + (i + 1) * jobs_per_thread);
            } else {
                vector<vector<int>> temp = {jobs[i]};
                job_data[i].rows = temp;
            }
            job_data[i].n = n;
            job_data[i].valid = &valid;

            pthread_create(&threads[i], nullptr, validate_job, (void*)&job_data[i]);
        }

        for (const auto thread: threads) {
            pthread_join(thread, nullptr);
        }
    }

    const auto end = chrono::high_resolution_clock::now();
    const chrono::duration<double> duration = end - start;

    if (valid) cout << "Valid." << endl;
    else cout << "Invalid." << endl;

    cout << "n: " << n << "\tk: " << k << endl;
    cout << "Time taken: " << duration.count() / REPEAT << " seconds" << endl;
}
