# Traveling Salesman Problem Solver
compile with -std=c++14

### To get the tour
```cpp
// instanciate a solver with distance matrix m and a start node
tspSolver<6> solver{m, start};
solver.getTour(true)   // for printing the result
```

### To get the min cost
```cpp
// instanciate a solver with distance matrix m and a start node
tspSolver<6> solver{m, start};
std::cout << solver.getTour(false) << std::endl;
```