#include "bits/stdc++.h"
#include <minisat/core/Solver.h>

using namespace std;
using namespace Minisat;

const int N = 9;
const int N_sq = 3;

Var get_var(int i, int j, int k) {
    return i * N * N + j * N + k;
}

void exactly_one_true(Solver &solver, vec<Lit> &vars) {
    solver.addClause(vars);
    for (int i = 0; i < vars.size(); ++i) {
        for (int j = i + 1; j < vars.size(); ++j) {
            solver.addClause(~vars[i], ~vars[j]);
        }
    }
}

void rows_constraints(Solver &solver) {
    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            vec<Lit> row;
            for (int j = 0; j < N; ++j) row.push(mkLit(get_var(i, j, k)));
            exactly_one_true(solver, row);
        }
    }
}

void column_constraints(Solver &solver) {
    for (int j = 0; j < N; ++j) {
        for (int k = 0; k < N; ++k) {
            vec<Lit> col;
            for (int i = 0; i < N; ++i) col.push(mkLit(get_var(i, j, k)));
            exactly_one_true(solver, col);
        }
    }
}

void cell_constraints(Solver &solver) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            vec<Lit> cell;
            for (int k = 0; k < N; ++k) cell.push(mkLit(get_var(i, j, k)));
            exactly_one_true(solver, cell);
        }
    }
}

void square_constraints(Solver &solver) {
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; i += N_sq) {
            for (int j = 0; j < N; j += N_sq) {
                vec<Lit> sq;
                for (int i_3 = i; i_3 < i + N_sq; ++i_3) {
                    for (int j_3 = j; j_3 < j + N_sq; ++j_3) {
                        sq.push(mkLit(get_var(i_3, j_3, k)));
                    }
                }
                exactly_one_true(solver, sq);
            }
        }
    }
}

void set_cell(Solver &solver, int i, int j, int k) {
    solver.addClause(mkLit(get_var(i, j, k)));
}


int main() {
    freopen("input.txt", "r", stdin);
    long double start_time = clock();
    Solver solver;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                solver.newVar();
            }
        }
    }
    rows_constraints(solver);
    column_constraints(solver);
    cell_constraints(solver);
    square_constraints(solver);
    char ch;
    int r = 0, c = 0;
    while (cin >> ch && r < N) {
        if (ch == '.');
        else if (ch > '0' && ch <= '9') set_cell(solver, r, c, ch - '1');
        else continue;
        ++c;
        r += c / N;
        c %= N;
    }
    if (solver.solve()) {
        cout << "Successfully solved\n";
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    if (solver.modelValue(get_var(i, j, k)) == l_True) {
                        cout << k + 1 << " ";
                        break;
                    }
                }
            }
            cout << "\n";
        }
    } else {
        cout << "Error occured\n";
    }
    long double end_time = clock();
    cout << (end_time - start_time) / CLOCKS_PER_SEC << "\n";
}
