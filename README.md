# Traveling Salesman Problem Solver
time complexity O(n^2*2^n)

compile with -std=c++14

### To get the tour
```cpp
// instantiate a solver with distance matrix m and a start node
tspSolver<n> solver{m, start};
solver.getTour(true)   // for printing the result
```

### To get the min cost
```cpp
// instantiate a solver with distance matrix m and a start node
tspSolver<n> solver{m, start};
solver.getTour(false);
std::cout << solver.getMinCost() << std::endl;
```
