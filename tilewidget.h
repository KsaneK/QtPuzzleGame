#ifndef TILEWIDGET_H
#define TILEWIDGET_H

#include "tile.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QFont>

class TileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TileWidget(Tile* tile, QWidget *parent = nullptr);
signals:
    void clicked();

public slots:

private:
    Tile* tile;

    void paintEvent(QPaintEvent*);
    void enterEvent(QEvent* e);
    void leaveEvent(QEvent* e);
    void setActive(bool active);
    void mousePressEvent(QEvent* e);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // TILEWIDGET_H
