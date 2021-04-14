#ifndef BOARD_H
#define BOARD_H

#include "simplevector.h"
#include "tile.h"
#include <vector>
#include <QPixmap>
#include <QObject>
#include <deque>
#include <QTimer>

class Board : public QObject
{
    Q_OBJECT
public:
    explicit Board(int size);
    Board(int size, std::vector<int> values);
    Board(int size, QPixmap* pm);
    Board(int size, std::vector<int> values, QPixmap* pm);
    Tile* tileAt(int row, int col);

    void move(Tile* tile);
    ~Board();
    void setImage(QPixmap *pixmap);
    int getSize();
    void clearImage();
    std::vector<int> getValues();
    void setSolution(std::vector<int> moves);
signals:
    void moved();
public slots:
    void solveTile();
    void solve();

private:
    bool finished;
    std::deque<int> solution;
    std::vector<Tile> tiles;
    int size;
    void swap(int i1, int i2);
    bool isSolvable(std::vector<int> values);
    void checkIfSolved();
};

#endif // BOARD_H
