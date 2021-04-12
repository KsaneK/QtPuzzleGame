#include "board.h"
#include "pixmaptile.h"
#include <QMessageBox>
#include <iostream>
#include <algorithm>
#include <random>
#include <QPixmapCache>
#include <QTimer>

Board::Board(int size)
{
    finished = false;
    this->size = size;
    std::vector<int> values;
    for (int i = 0; i < size * size - 1; i++) values.push_back(i);
    std::random_device rd;
    auto random_engine = std::default_random_engine { rd() };
    std::shuffle(values.begin(), values.end(), random_engine);
    while(!isSolvable(values)) {
        std::shuffle(values.begin(), values.end(), random_engine);
    }

    tiles.reserve(size * size);
    for (unsigned int i = 0; i < values.size() ; i++) {
        tiles.emplace_back(values[i]);
    }
    tiles.emplace_back(-1);
    values.clear();
    values.shrink_to_fit();
}

Board::Board(int size, std::vector<int> values) {
    this->size = size;
    finished = false;
    tiles.reserve(size * size);
    for (unsigned int i = 0; i < values.size() ; i++) {
        tiles.emplace_back(values[i]);
    }
}

Board::Board(int size, QPixmap *pm) : Board(size) {
    setImage(pm);
}

Board::Board(int size, std::vector<int> values, QPixmap *pm) : Board(size, values) {
    setImage(pm);
}

Board::~Board() {

}

int Board::getSize() {
    return size;
}

void Board::setImage(QPixmap* pixmap) {
    PixmapTile* pixmapTile = new PixmapTile(pixmap, size);
    for (unsigned int i = 0; i < tiles.size(); i++) {
        tiles.at(i).setImage(pixmapTile);
    }
}

void Board::clearImage() {
    if (this->tiles.size() > 0 && this->tiles.at(0).getImage() != nullptr) {
        delete this->tiles.at(0).getImage()->getPixmap();
        delete this->tiles.at(0).getImage();
        QPixmapCache::clear();
    }
    for (unsigned int i = 0; i < tiles.size(); i++) {;
        tiles.at(i).setImage(nullptr);
    }
}

bool Board::isSolvable(std::vector<int> values) {
    int inversionCount = 0;
    for (unsigned int i = 0; i < values.size(); i++)
        for (unsigned int j = i + 1; j < values.size(); j++)
            if (values.at(i) > values.at(j))
                inversionCount++;
    return inversionCount % 2 == 0;
}

void Board::checkIfSolved() {
    for (unsigned int i = 0; i < tiles.size() - 1; i++) {
        if (tiles.at(i).getValue() != (int)i) return;
    }
    finished = true;
    tiles.at(tiles.size() - 1).setValue(tiles.size() - 1);
    QMessageBox msgBox;
    msgBox.setWindowTitle("Koniec");
    msgBox.setText("Puzzle rozwiązane! Gratulacje!");
    msgBox.exec();
}

Tile* Board::tileAt(int row, int col) {
    Tile* t = &tiles.at(row * size + col);
    return t;
}

std::vector<int> Board::getValues() {
    std::vector<int> vals;
    vals.reserve(size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            vals.push_back(tileAt(row, col)->getValue());
        }
    }
    return vals;
}

void Board::solve(std::vector<int> moves)
{
    solution.clear();
    for (int move : moves) solution.push_back(move);
    QTimer::singleShot(500, this, [=](){solveTile();});
}

void Board::solveTile() {
    if (!solution.empty()) {
        int ind = solution.front();
        std::cout << "test " << ind << std::endl;
        solution.pop_front();
        move(&tiles[ind]);
        emit moved();
        QTimer::singleShot(500, this, [=](){solveTile();});
    } else {
        finished = true;
    }
}

void Board::move(Tile* tile) {
    if (finished) return;

    auto it = std::find(tiles.begin(), tiles.end(), *tile);
    if (it != tiles.end()) {
        int ind = it - tiles.begin();
        int row = ind / size;
        int col = ind % size;
        int indEmpty = -1;
        if (row > 0 && tiles.at((row - 1) * size + col).getValue() == -1) indEmpty = (row - 1) * size + col;
        else if (row < size - 1 && tiles.at((row + 1) * size + col).getValue() == -1) indEmpty = (row + 1) * size + col;
        else if (col > 0 && tiles.at(row * size + col - 1).getValue() == -1) indEmpty = row * size + col - 1;
        else if (col < size - 1 && tiles.at(row * size + col + 1).getValue() == -1) indEmpty = row * size + col + 1;
        if (indEmpty != -1) {
            swap(ind, indEmpty);
            checkIfSolved();
        }
    }
}

void Board::swap(int i1, int i2) {
    int tmp = tiles.at(i1).getValue();
    tiles.at(i1).setValue(tiles.at(i2).getValue());
    tiles.at(i2).setValue(tmp);
}
