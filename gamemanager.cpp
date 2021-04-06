#include "gamemanager.h"

GameManager::GameManager(QObject *parent) : QObject(parent)
{

}

Board* GameManager::newGame(int size)
{
    if (board == nullptr)
        delete board;
    board = new Board(size);
    return board;
}

Board* GameManager::getActiveBoard() {
    return board;
}

void GameManager::setPlayer(Player* player) {
    this->player = player;
}
