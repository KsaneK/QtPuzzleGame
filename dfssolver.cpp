//#include "dfssolver.h"
//#include <iostream>
//#include <math.h>
//#include <string>


//std::deque<int> DFSSolver::solve(std::vector<int> vals) {
//    int size = sqrt(vals.size());
//    if (size > 4) throw "Maximum size for dfs is 4";

//    long long int goal = (size == 4) ? 0x123456789abcdef0 : 0x1234567800000000;
//    long long int state = 0x0;
//    int hole;
//    for (int i = 0; i < vals.size(); i++) {
//        state <<= 4;
//        state |= vals[i] + 1;
//        if (vals[i] == -1) hole = i;
//    }
//    if (size == 3) state <<= 28;

//    std::cout << std::hex << goal << " " << state << " " << hole << std::endl;
//    std::deque<int>* steps = new std::deque<int>();
//    std::unordered_map<long long int, int>* visited = new std::unordered_map<long long int, int>();
//    std::deque<int>* result = new std::deque<int>();

//    dfs(goal, state, steps, visited, hole, size, result);

//    steps->clear();
//    steps->shrink_to_fit();
//    delete steps;

//    std::deque<int> r(*result);
//    result->clear();
//    result->shrink_to_fit();
//    delete result;
//    return r;

//}

//void DFSSolver::dfs(long long int goal, long long int state, std::deque<int>* steps, std::unordered_map<long long int, int>* visited, int hole, int size, std::deque<int>* result) {
//    if (result->size() > 0 && result->size() < steps->size()) return;
//    auto e = visited->find(state);
//    if (e != visited->end() && e->second <= steps->size()) return;
//    visited->insert(std::pair<long long int, int>(state, steps->size()));
//    if (steps->size() > ((size == 4) ? 80 : 40)) return;

//    if (goal == state) {
//        if (result->size() == 0 || steps->size() < result->size()) {
//            result->clear();
//            for (int i = 0; i < steps->size(); i++)
//                result->push_back(steps->at(i));
//        }
//        std::cout << "Solved with " << steps->size() << " steps." << std::endl;
//        return;
//    }

//    if (hole >= size) {
//        steps->push_back(hole - size);
//        dfs(goal, swapBits(state, hole, hole - size), steps, visited, hole - size, size, result);
//        steps->pop_back();
//    }
//    if (hole < size * (size - 1)) {
//        steps->push_back(hole + size);
//        dfs(goal, swapBits(state, hole, hole + size), steps, visited, hole + size, size, result);
//        steps->pop_back();
//    }
//    if (hole % size > 0) {
//        steps->push_back(hole - 1);
//        dfs(goal, swapBits(state, hole, hole - 1), steps, visited, hole - 1, size, result);
//        steps->pop_back();
//    }
//    if (hole % size < size - 1) {
//        steps->push_back(hole + 1);
//        dfs(goal, swapBits(state, hole, hole + 1), steps, visited, hole + 1, size, result);
//        steps->pop_back();
//    }
//}

//long long int DFSSolver::swapBits(long long val, int p1, int p2) {
//    p1 = 60 - p1 * 4;
//    p2 = 60 - p2 * 4;
//    long long xored = ((val >> p1) & 15) ^ ((val >> p2) & 15);
//    return ((xored << p1) | (xored << p2)) ^ val;
//}
