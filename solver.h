#ifndef SOLVER_H
#define SOLVER_H

#include "simplevector.h"
#include "tile.h"

#include <unordered_map>
#include <deque>

struct IntVectorHasher {
    std::size_t operator()(const std::vector<int>& v) const {
        std::size_t h = 0;
        for (unsigned int i = 0; i < v.size(); i++) {
            h = (h * 773 + v[i]);
        }
        return h;
    }
};

struct CharArrHasher {
    std::size_t operator()(const char* v) const {
        std::size_t h = 0;
        while (*v != 0) {
            h = (h * 773 + *v);
            v++;
        }
        return h;
    }
};

static int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

enum SolverType {
    DFS,
    AStar,
    BranchAndBound,
    IDAStar
};

class Solver
{
public:
    virtual std::vector<int> solve(std::vector<int>)=0;
private:
    std::unordered_map<std::vector<int>, std::vector<int>, IntVectorHasher> stateToPath;
};

#endif // SOLVER_H
