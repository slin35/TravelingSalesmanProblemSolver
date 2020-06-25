#ifndef _TSP_SOLVER_H_
#define _TSP_SOLVER_H_

#include <vector>
#include <bitset>
#include <iostream>
#include <limits>
#include <algorithm>

template<int n>
class tspSolver {
    using Matrix = std::vector<std::vector<int>>;

    public:
        tspSolver(const Matrix& distMatrix, int start) : distMatrix{distMatrix}, start{start} {
            if (n > 32)
                throw "sry matrix too large for time complexity of O(n^2*2^n)";
            if (n != distMatrix[0].size())
                throw "invalid matrix dimention, must comformed to n x n";

            memo.resize(n);
            for (int i = 0; i < n; i++) {
                memo[i].resize(1 << n);
            }
        }

        std::vector<int> getTour(bool printable) {
            // setup
            for (int i = 0; i < n; i++) {
                if (i == start)
                    continue;
                memo[i][1 << start | 1 << i] = distMatrix[start][i];
            }

            for (int r = 3; r <= n; r++) {
                subset.clear();
                generateCombinations(r, 0, 0);
                // loop through combinations
                for (int idx = 0; idx < subset.size(); idx++) {
                    if (notIn(start, subset[idx]))
                        continue;
                    for (int next = 0; next < n; next++) {
                        if (next == start || notIn(next, subset[idx]))
                            continue;
                        int state = subset[idx] ^ (1 << next);
                        int minDistance = std::numeric_limits<int>::max();

                        for (int end = 0; end < n; end++) {
                            if (end == start || end == next || notIn(end, subset[idx]))
                                continue;
                            int newDistance = memo[end][state] + memo[end][next];
                            if (newDistance < minDistance)
                                minDistance = newDistance;
                            memo[next][subset[idx]] = minDistance;
                        }
                    }
                }
            }

            findOptimalTour();
            std::reverse(tour.begin(), tour.end());

            if (printable) {
                for (int i : tour)
                    std::cout<< i << " ";
                std::cout << std::endl;
            }

            

            return tour;
        }

        void findOptimalTour() {
            int last = start;
            int state = (1 << n) - 1;

            tour.push_back(start);
            for (int i = 1; i < n; i++) {
                int index = -1;
                for (int j = 0; j < n; j++) {
                    if (j == start || notIn(j, state))
                        continue;
                    if (index == -1)
                        index = j;

                    int prevDist = memo[index][state] + distMatrix[index][last];
                    int newDist = memo[j][state] + distMatrix[j][last];

                    if (newDist < prevDist)
                        index = j;

                }
                tour.push_back(index);
                state = state ^ (1 << index);
                last = index;
            }

            tour.push_back(start);
        }

        int getMinCost() {
            int end = (1 << n) - 1;

            for (int i = 0; i < n; i++) {
                if (i == start)
                    continue;
                int tourCost = memo[i][end] + distMatrix[i][start];
                if (tourCost < minTourCost) {
                    minTourCost = tourCost;
                }
            }

            return minTourCost;
        }

        void generateCombinations(int size, int val, int i) {
            if (i == size) {
                subset.push_back(val);
                return;
            }

            val &= ~(1UL << i);
            generateCombinations(size, val, i + 1);
            val |= 1UL << i;
            generateCombinations(size, val, i + 1);
        }

        bool notIn(int i, int value) {
            return ((1 << i) & value) == 0;
        }

    private:
        Matrix distMatrix, memo;
        std::vector<int> tour, subset;
        int start, minTourCost{std::numeric_limits<int>::max()};
};

#endif
