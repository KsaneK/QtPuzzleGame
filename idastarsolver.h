#ifndef IDASTARSOLVER_H
#define IDASTARSOLVER_H

#include "solver.h"
#include <vector>
#include <chrono>

struct TimeoutException : public std::exception
{
    const char * what () const throw ()
    {
        return "Nie udało się znaleźć rozwiązanie w przeciągu 10 sekund";
    }
};

class IDAStarSolver : public Solver
{
public:
    IDAStarSolver();
    std::vector<int> solve(std::vector<int> vals);
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> solve_start_timestamp;
    std::unordered_map<long long int, int> WDTABLE;
    int bits;
    int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    int size;
    int manhattan_dist(const char* vals) const;
    static void swap(char *arr, int p1, int p2);
    int dfs(char *state, std::vector<int> *path, int cost, int bound, int hole);
    bool isGoal(const char *state) const;
    void genWDTable(int size);
    unsigned long long encode(const char *state, int boardSize);
    int walking_dist(const char *state) const;
};



#endif // IDASTARSOLVER_H
