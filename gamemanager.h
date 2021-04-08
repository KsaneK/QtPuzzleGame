#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "board.h"
#include "player.h"

#include <QObject>
#include <QPixmap>

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);
    Board* newGame(int size, bool keepImage);
    void saveGame(QString& filename);
    bool loadGame(QString& filename);

    void setPlayer(Player* player);
    Board *getActiveBoard();
signals:

public slots:

private:
    Board* board;
    Player* player;
    QPixmap* image;
};

#endif // GAMEMANAGER_H
