#include "tspSolver.h"

int main() {
    std::vector<std::vector<int>> m;
    int n = 6;

    m.resize(n);

    for (int i = 0; i < n; i++) {
        m[i].resize(n);
        for (int j= 0; j < n; j++) {
            m[i][j] = 1000;
        }
    }

    m[5][0] = 10;
    m[1][5] = 12;
    m[4][1] = 2;
    m[2][4] = 4;
    m[3][2] = 6;
    m[0][3] = 8;

    tspSolver<6> solver{m, 0};
    solver.getTour(true);
    solver.getMinCost();

    return 0;
}