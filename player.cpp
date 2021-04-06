#include "player.h"

Player::Player(QString username, QObject *parent) : QObject(parent)
{
    this->username = username;
}
