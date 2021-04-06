#ifndef PIXMAPTILE_H
#define PIXMAPTILE_H

#include <QObject>

class PixmapTile : public QObject
{
    Q_OBJECT
public:
    explicit PixmapTile(QPixmap *pixmap, int gridSize, QObject *parent = nullptr);
    int getGridSize();
    QPixmap *getPixmap();
signals:

public slots:

private:
    QPixmap* pixmap;
    int gridSize;
};

#endif // PIXMAPTILE_H
