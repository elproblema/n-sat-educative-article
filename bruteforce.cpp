#include "bits/stdc++.h"

using namespace std;

const int N = 9;
const int N_sq = 3;

int table[N][N];

bool able_to_fit(int i, int j, int val) {
    for (int j_it = 0; j_it < N; ++j_it) {
        if (table[i][j_it] == val) return false;
    }
    for (int i_it = 0; i_it < N; ++i_it) {
        if (table[i_it][j] == val) return false;
    }
    for (int i_it = i - i % N_sq; i_it < (i / N_sq + 1) * N_sq; ++i_it) {
        for (int j_it = j - j % N_sq; j_it < (j / N_sq + 1) * N_sq; ++j_it) {
            if (table[i_it][j_it] == val) return false;
        }
    }
    return true;
}

bool gen_table(int i, int j) {
    if (i == N) return true;
    if (j == N) return gen_table(i + 1, 0);
    if (table[i][j] == -1) {
        vector<int> vec(N);
        iota(vec.begin(), vec.end(), 0);
        random_shuffle(vec.begin(), vec.end());
        for (int val : vec) {
            if (able_to_fit(i, j, val)) {
                table[i][j] = val;
                if (gen_table(i, j + 1)) return true;
            }
        }
        table[i][j] = -1;
    } else if (gen_table(i, j + 1)) return true;
    return false;
}

int main() {
    long double start_time = clock();
    //
    srand(time(0));
    freopen("input.txt", "r", stdin);
    char ch;
    int i = 0, j = 0;
    while (cin >> ch && i < N) {
        if (ch == '.') table[i][j] = -1;
        else if (ch > '0' && ch <= '9') table[i][j] = ch - '1';
        else continue;
        ++j;
        i += j / N;
        j %= N;
    }
    //
    if (gen_table(0, 0)) {
        cout << "Successfully solved\n";
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                cout << table[r][c] + 1 << " ";
            }
            cout << "\n";
        }
    } else {
        cout << "Error occurred\n";
    }
    //
    long double end_time = clock();
    cout << (end_time - start_time) / CLOCKS_PER_SEC << "\n";
}