//
// Created by ksanek on 11.04.2021.
//

#include "idastarsolver.h"
#include <math.h>
#include <iostream>
#include <vector>
#include <deque>

IDAStarSolver::IDAStarSolver()
{
}

std::vector<int> IDAStarSolver::solve(std::vector<int> vals)
{
    size = sqrt(vals.size());
    genWDTable(size);

    char* input = new char[vals.size()];
    int hole;
    for (unsigned int i = 0; i < vals.size(); i++) {
        input[i] = vals[i] == -1 ? 0 : (char)vals[i] + 1;
        if (vals[i] == -1) hole = i;
    }
    int md = walking_dist(input);
    std::vector<int>* path = new std::vector<int>();
    for (int i = 0; i < 10000; i++) {
        path->clear();
        int cost = dfs(input, path, 0, md, hole);
        if (cost == 100000) {
            for (int i = 0; i < path->size(); i++) {
                int ind = path->at(i);
            }
            return std::vector<int>(*path);
        }
        md = cost;
    }

    return std::vector<int>();
}

int IDAStarSolver::dfs(char* state, std::vector<int>* path, int cost, int bound, int hole) {
    int total_cost = cost + walking_dist(state);
    if (total_cost > bound) return total_cost;
    if (isGoal(state)) {
        std::cout << "GOAL!!!!" << std::endl;
        return 100000;
    }
    int min = 999999;
    for (auto direction : directions) {
        int swapRow = hole / size + direction[0];
        int swapCol = hole % size + direction[1];
        if (0 <= swapRow && swapRow < size && 0 <= swapCol && swapCol < size) {
            int indexToSwap = swapRow * size + swapCol;
            if (!path->empty() && indexToSwap == path->at(path->size() - 1))
                continue;
            swap(state, hole, indexToSwap);
            path->push_back(indexToSwap);
            int r = dfs(state, path, cost + 1, bound, indexToSwap);
            if (r == 100000) return r;
            if (r < min) min = r;
            path->pop_back();
            swap(state, hole, indexToSwap);
        }
    }
    return min;
}

bool IDAStarSolver::isGoal(const char* state) const {
    for (int i = 0; i < size * size - 1; i++) {
        if (state[i] != i + 1) return false;
    }
    return true;
}

void IDAStarSolver::swap(char* arr, int p1, int p2) {
    char tmp = arr[p1];
    arr[p1] = arr[p2];
    arr[p2] = tmp;
}

int IDAStarSolver::walking_dist(const char* state) const {
    long long int wdr = 0;
    long long int wdc = 0;
    int d = 0;
    for (int i = 0; i < size * size; i++) {
        if (state[i] == 0) continue;
        int goalInd = state[i] - 1;
        int row = i / size;
        int col = i % size;
        int goalRow = goalInd / size;
        int goalCol = goalInd % size;
        wdr += (long long int)1 << (bits * (size * row + goalRow));
        wdc += (long long int)1 << (bits * (size * col + goalCol));

        if (row == goalRow)
            for (int j = i + 1; j < size * (row + 1); j++)
                if (state[j] > 0 && (state[j] - 1) / size == goalRow && state[i] > state[j])
                    d += 2;
        if (col == goalCol)
            for (int j = i + size; j < size * size; j += size)
                if (state[j] > 0 && (state[j] - 1) % size == goalCol && state[i] > state[j])
                    d += 2;
    }
    return d + WDTABLE.at(wdr) + WDTABLE.at(wdc);
}

int IDAStarSolver::manhattan_dist(const char *vals) const
{
    int v;
    int row, col, goalRow, goalCol;
    int md = 0;
    for (int i = 0; i < size * size; i++) {
        v = vals[i];
        if (v == 0) continue;
        row = i / size;
        col = i % size;
        goalRow = (v - 1) / size;
        goalCol = (v - 1) % size;
        md += abs(goalRow - row) + abs(goalCol - col);

        if (row == goalRow)
            for (int j = i + 1; j < row * size + size; j++)
                if (v > vals[j] && vals[j] / size == goalRow) {
                    md += 2;
                    break;
                }
        if (col == goalCol)
            for (int j = i + size; j < size * size; j += size)
                if (v > vals[j] && vals[j] % size == goalCol) {
                    md += 2;
                    break;
                }
    }
    return md;
}

void IDAStarSolver::genWDTable(int size) {
    bits = 0;
    int tmp = size;
    while (tmp) { tmp >>= 1; bits++; }
    struct wdnode {
        char *state;
        int cost;
        int e;
    };
    char *goal = new char[size * size];
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            goal[i * size + j] = (i == j) ? size : 0;
    goal[size * size - 1] = size - 1;
    WDTABLE.clear();
    std::deque<struct wdnode*> toVisit;
    struct wdnode* initnode = new struct wdnode;
    initnode->state = goal;
    initnode->cost = 0;
    initnode->e = size - 1;
    toVisit.push_back(initnode);

    while(!toVisit.empty()) {
        struct wdnode* node = toVisit.front();
        toVisit.pop_front();

        unsigned long long encoded = encode(node->state, size);
        if (WDTABLE.find(encoded) != WDTABLE.end()) continue;
        WDTABLE[encoded] = node->cost;

        for (int dir = -1; dir < 2; dir += 2) {
            if (node->e + dir >= 0 && node->e + dir < size) {
                for (int c = 0; c < size; c++) {
                    if (node->state[size * (node->e + dir) + c] > 0) {
                        char *newState = new char[size*size];
                        for (int i = 0; i < size * size; i++)
                            newState[i] = node->state[i];
                        newState[size * (node->e + dir) + c] -= 1;
                        newState[size * node->e + c] += 1;
                        struct wdnode* newNode = new struct wdnode;
                        newNode->state = newState;
                        newNode->cost = node->cost + 1;
                        newNode->e = node->e + dir;
                        toVisit.push_back(newNode);
                    }
                }
            }
        }
        delete[] node->state;
        delete node;
    }
}

unsigned long long IDAStarSolver::encode(const char *state, int boardSize) {
    unsigned long long result = 0;
    for (int i = 0; i < boardSize * boardSize; i++)
        result |= ((unsigned long long)state[i]) << (bits * i);
    return result;
}
