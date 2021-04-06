#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QString username, QObject *parent = nullptr);

signals:

public slots:

private:
    QString username;
};

#endif // PLAYER_H
