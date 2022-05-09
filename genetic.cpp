#pragma GCC optimization("Ofast")
#include "bits/stdc++.h"

using namespace std;

const int N = 9;
const int N_sq = 3;
const int fertility = 5;
const int population = 500;
const int generations = 500;

int input[N][N];
int start_table[N][N];

struct sudoku {
    vector<vector<int>> table;

    sudoku() {
        table.assign(9, vector<int>(9));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                table[i][j] = start_table[i][j];
            }
        }
    }

    int f() const {
        int res = 0;
        for (int j = 0; j < N; ++j) {
            for (int i1 = 0; i1 < N; ++i1) {
                for (int i2 = i1 + 1; i2 < N; ++i2) {
                    res += table[i1][j] == table[i2][j];
                }
            }
        }
        for (int sq = 0; sq < N; ++sq) {
            int i_st = sq / N_sq * N_sq, j_st = sq % N_sq * N_sq;
            for (int f = 0; f < N; ++f) {
                for (int s = f + 1; s < N; ++s) {
                    res += table[i_st + f / N_sq][j_st + f % N_sq] == table[i_st + s / N_sq][j_st + s % N_sq];
                }
            }
        }
        return res;
    }

    void random_fill() {
        for (int i = 0; i < 9; ++i) {
            vector<int> used(9);
            for (int j = 0; j < 9; ++j) if (input[i][j]) used[table[i][j]] = 1;
            vector<int> perm;
            for (int j = 0; j < 9; ++j) if (!used[j]) perm.push_back(j);
            random_shuffle(perm.begin(), perm.end());
            int ptr = 0;
            for (int j = 0; j < 9; ++j) {
                if (!input[i][j]) table[i][j] = perm[ptr], ptr++;
            }
        }
    }

    sudoku gen_new() {
       sudoku new_sudoku;
       for (int i = 0; i < N; ++i) {
           for (int j = 0; j < N; ++j) {
               new_sudoku.table[i][j] = table[i][j];
           }
       }
       int i, j1, j2;
       do {
           i = rand() % N;
           j1 = rand() % N, j2 = rand() % N;
       } while (input[i][j1] || input[i][j2]);
       swap(new_sudoku.table[i][j1], new_sudoku.table[i][j2]);
       return new_sudoku;
    }
};

sudoku natural_selection() {
    vector<sudoku> parents(population);
    for (auto &i : parents) i.random_fill();
    vector<sudoku> children;
    for (int i = 0; i < generations; ++i) {
        for (auto s : parents) {
            children.push_back(s);
            for (int j = 0; j < fertility; ++j) children.push_back(s.gen_new());
        }
        sort(children.begin(), children.end(), [&](const sudoku &a, const sudoku &b) {
           return a.f() < b.f();
        });
        children.resize(population);
        swap(parents, children);
        children.clear();
    }
    return parents[0];
}

int main() {
    long double start_time = clock();
    //
    srand(time(0));
    freopen("input.txt", "r", stdin);
    char ch;
    int r = 0, c = 0;
    while (cin >> ch && r < N) {
        if (ch == '.') start_table[r][c] = -1;
        else if (ch > '0' && ch <= '9') start_table[r][c] = ch - '1', input[r][c] = 1;
        else continue;
        ++c;
        r += c / N;
        c %= N;
    }
    //
    sudoku answer = natural_selection();
    cout << "f(answer) := " << answer.f() << "\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << answer.table[i][j] + 1 << " ";
        }
        cout << "\n";
    }
    //
    long double end_time = clock();
    cout << (end_time - start_time) / CLOCKS_PER_SEC << "\n";
}