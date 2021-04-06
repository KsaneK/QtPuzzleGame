#include "tile.h"
#include <iostream>

Tile::Tile(int value)
{
    this->value = value;
    pixmapTile = nullptr;
}

Tile::Tile(Tile &&t) {
    value = t.value;
    pixmapTile = t.pixmapTile;
}

int Tile::getValue() const {
    return value;
}

void Tile::setValue(int v) {
    value = v;
}

void Tile::setImage(PixmapTile* pixmapTile)
{
    this->pixmapTile = pixmapTile;
}

PixmapTile* Tile::getImage() {
    return pixmapTile;
}

bool Tile::operator ==(const Tile& another) {
    return value == another.value;
}
