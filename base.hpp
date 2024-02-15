#include <cmath>
#include <vector>


using namespace std;


bool validate(const int n, const vector<int>& row) {
    int heatmap[n];

    for (const int block: row) {
        if (heatmap[block - 1] == 1) return false;
        heatmap[block - 1] = 1;
    }

    return true;
}


vector<vector<int>> get_rows(const int n, int sudoku[]) {
    const int n_square = n * n;
    vector<vector<int>> rows{};

    for (int ix = 0; ix < n_square; ix += n) {
        vector<int> row{};
        for (int offset = 0; offset < n; offset++) {
            row.push_back(sudoku[ix + offset]);
        }
        rows.push_back(row);
    }

    return rows;
}


vector<vector<int>> get_columns(const int n, int sudoku[]) {
    const int n_square = n * n;
    vector<vector<int>> columns{};

    for (int ix = 0; ix < n; ix++) {
        vector<int> column{};
        for (int offset = 0; offset < n_square; offset += n) {
            column.push_back(sudoku[ix + offset]);
        }
        columns.push_back(column);
    }

    return columns;
}


vector<vector<int>> get_grids(const int n, int sudoku[]) {
    const int sqrt_n = (int) sqrt(n);
    const int n_square = n * n;
    vector<vector<int>> grids{};
    vector<int> indices{};
    vector<int> offsets{};

    for (int ix = 0; ix < n_square; ix += n * sqrt_n) {
        for (int offset = 0; offset < n; offset += sqrt_n) {
            indices.push_back(ix + offset);
            offsets.push_back((ix + offset) / sqrt_n);
        }
    }

    for (const int index : indices) {
        vector<int> grid{};
        for (const int offset : offsets) {
            grid.push_back(sudoku[index + offset]);
        }
        grids.push_back(grid);
    }

    return grids;
}
