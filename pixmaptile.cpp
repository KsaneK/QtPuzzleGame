#include "pixmaptile.h"

PixmapTile::PixmapTile(QPixmap* pixmap, int gridSize, QObject *parent) : QObject(parent)
{
    this->pixmap = pixmap;
    this->gridSize = gridSize;
}

QPixmap* PixmapTile::getPixmap() {
    return pixmap;
}

int PixmapTile::getGridSize() {
    return gridSize;
}
