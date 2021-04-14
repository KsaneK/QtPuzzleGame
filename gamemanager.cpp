#include "gamemanager.h"

#include <QApplication>
#include <QBuffer>
#include <QThread>
#include <iostream>
#include <thread>

GameManager::GameManager(QObject *parent) : QObject(parent)
{
    board = nullptr;
}

Board* GameManager::newGame(int size, bool keepImage=false)
{
    QPixmap* pm = nullptr;
    if (board != nullptr) {
        if (keepImage) {
            if (board->getSize() > 0) {
                PixmapTile* pmt = board->tileAt(0, 0)->getImage();
                pm = pmt->getPixmap();
                delete pmt;
            }
        }
        delete board;   
    }
    board = keepImage && pm != nullptr ? new Board(size, pm) : new Board(size);
    connect(this, SIGNAL(solved()), board, SLOT(solve()));
    return board;
}

void GameManager::saveGame(QString &filename)
{
    int boardSize = board->getSize();
    FILE* f = fopen(filename.toStdString().c_str(), "wb");
    fwrite(&boardSize, sizeof(int), 1, f);
    for (int i = 0; i < boardSize * boardSize; i++) {
        int val = board->tileAt(i / boardSize, i % boardSize)->getValue();
        fwrite(&val, sizeof(int), 1, f);
    }
    if (board->tileAt(0, 0)->getImage() != nullptr) {
        QPixmap* pm = board->tileAt(0, 0)->getImage()->getPixmap();
        QByteArray bytes;
        QBuffer buf(&bytes);
        buf.open(QIODevice::WriteOnly);
        pm->save(&buf, "PNG");
        unsigned int size = bytes.size();
        const char* data = bytes.constData();
        size_t saved = 0, bwrite;
        fwrite(&size, sizeof(int), 1, f);
        while (saved < size) {
            bwrite = fwrite(data + saved, 1, size - saved, f);
            saved += bwrite;
        }
    } else {
        int val = 0;
        fwrite(&val, sizeof(int), 1, f);
    }
    fclose(f);
}

bool GameManager::loadGame(QString &filename)
{
    size_t bytesRead;
    unsigned int boardSize;
    FILE* f = fopen(filename.toStdString().c_str(), "rb");
    bytesRead = fread(&boardSize, sizeof(int), 1, f);
    if (bytesRead != 1) { fclose(f); return false; }
    std::vector<int> values;
    for (unsigned int i = 0; i < boardSize * boardSize; i++) {
        int v;
        bytesRead = fread(&v, sizeof(int), 1, f);
        if (bytesRead != 1) { fclose(f); return false; }
        values.push_back(v);
    }
    unsigned int pixmapSize = 0;
    QPixmap* pm = nullptr;
    bytesRead = fread(&pixmapSize, sizeof(int), 1, f);
    if (pixmapSize > 0) {
        char* bytes = new char[pixmapSize];
        bytesRead = fread(bytes, 1, pixmapSize, f);
        if (bytesRead != pixmapSize) { fclose(f); delete[] bytes; return false; }
        QByteArray byteArray(bytes, pixmapSize + 1);
        byteArray[pixmapSize] = 0;
        pm = new QPixmap();
        if (!pm->loadFromData(byteArray)) {
            delete pm;
            delete[] bytes;
            fclose(f);
            return false;
        }
    }

    if (board != nullptr)
        delete board;
    if (pm != nullptr) board = new Board(boardSize, values, pm);
    else board = new Board(boardSize, values);
    connect(this, SIGNAL(solved()), board, SLOT(solve()));
    return true;
}

Board* GameManager::getActiveBoard() {
    return board;
}

void GameManager::solve(SolverType solverType)
{
    std::vector<int> vals = board->getValues();
    std::thread solverThread([this, vals]() {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        try {
            std::vector<int> moves = idastarsolver.solve(vals);
            board->setSolution(moves);
            emit solved();
        } catch (const TimeoutException& e) {
            emit solveTimeout();
        }
        QApplication::restoreOverrideCursor();
    });
    solverThread.detach();
}

void GameManager::setPlayer(Player* player) {
    this->player = player;
}

