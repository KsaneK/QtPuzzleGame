#ifndef TILE_H
#define TILE_H

#include "pixmaptile.h"

#include <QObject>
#include <QPixmap>

class Tile : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int value READ getValue)
public:
    explicit Tile(int value);
    Tile(Tile&& t);
    int getValue() const;
    PixmapTile *getImage();
    void setValue(int v);
    void setImage(PixmapTile* pixmapTile);
    bool operator ==(const Tile& another);
signals:

public slots:

private:
    int value;
    PixmapTile* pixmapTile;
};

#endif // TILE_H
