//#include "iddfssolver.h"
//#include <iostream>
//#include <math.h>

//IDDFSSolver::IDDFSSolver() {}


//std::deque<int> IDDFSSolver::solve(std::vector<int> vals) {
////    int size = sqrt(vals.size());
////    std::deque<int>* input = new std::deque<int>(vals);
////    std::deque<int>* goal = new std::deque<int>();
////    for (int i = 0; i < size * size - 1; i++) goal->push_back(i);
////    goal->push_back(-1);
//////    std::vector<int>* steps = new std::vector<int>();
////    std::unordered_set<std::vector<int>, IntVectorHasher>* visited;

////    int maxDepth;
////    if (size == 3) maxDepth = 40;
////    if (size == 4) maxDepth = 80;
////    if (size == 5) maxDepth = 208;

////    std::deque<int>* solved;
////    int holeInd = -1;
////    for (int i = 0; i < vals.size(); i++)
////        if (vals[i] == -1)
////            holeInd = i;
////    for (int i = 0; i < maxDepth; i++) {
////        visited = new std::unordered_set<std::vector<int>, IntVectorHasher>();
////        fflush(stdout);
////        solved = _solve(input, size, i, holeInd, goal, visited);
////        if (solved != nullptr) {
////            std::cout << "depth: " << i << std::endl;
////            for (int i = 0; i < solved->size(); i++) {
////                std::cout << solved->at(i) << std::endl;
////            }
////            return std::deque<int>(*solved);
////        }
////        visited->clear();
////        delete visited;
////    }

////    std::cout << "test" << std::endl;
////    std::vector<int> r(*steps);
////    steps->clear();
////    steps->shrink_to_fit();
////    delete steps;
//    return std::deque<int>();
//}

//std::deque<int>* IDDFSSolver::_solve(std::vector<int>* vals, int size, int depth, int holeInd, std::deque<int>* goal, std::unordered_set<std::deque<int>, IntVectorHasher>* visited) {
////    if (visited->find(*vals) != visited->end()) return nullptr;
////    visited->insert(*vals);

////    if (depth == 0) {
////        bool solved = *vals == *goal;
////        if (solved) {
////            std::cout << "SOLVED!!!!" << std::endl;
////        }
////        if (solved) {
////            std::deque<int>* result = new std::deque<int>();
////            return result;
////        }
////        return nullptr;
////    }

////    int row = holeInd / size;
////    int col = holeInd % size;
////    std::deque<int>* solved;
////    for (int dir = 0; dir < 4; dir++) {
////        int rowToSwap = row + directions[dir][0];
////        int colToSwap = col + directions[dir][1];

////        if (0 <= rowToSwap && rowToSwap < size && 0 <= colToSwap && colToSwap < size) {
////            swap(vals, holeInd, rowToSwap * size + colToSwap);
////            solved = _solve(vals, size, depth - 1, rowToSwap * size + colToSwap, goal, visited);
////            swap(vals, holeInd, rowToSwap * size + colToSwap);
////            if (solved != nullptr) {
////                solved->push_back(rowToSwap * size + colToSwap);
////                return solved;
////            }
////        }
////    }
////    return solved;
//    return new std::deque<int>();
//}

//void IDDFSSolver::swap(std::vector<int>* vals, int i, int j) {
//    int tmp = (*vals)[i];
//    (*vals)[i] = (*vals)[j];
//    (*vals)[j] = tmp;
//}
