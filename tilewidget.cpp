#include "tilewidget.h"

#include <QLabel>
#include <string>
#include <iostream>
#include <QStyle>
#include <QPainter>
#include <QFont>

TileWidget::TileWidget(Tile* tile, QWidget *parent) : QWidget(parent)
{
    this->tile = tile;
    clickEnabled = true;
    setCursor(QCursor(Qt::PointingHandCursor));
    setAutoFillBackground(true);
    setActive(false);
}

void TileWidget::enable()
{
    clickEnabled = true;
}

void TileWidget::disable()
{
    clickEnabled = false;
}

void TileWidget::paintEvent(QPaintEvent* e) {
    if (tile->getValue() != -1) {
        QWidget::paintEvent(e);
        QPainter painter(this);
        painter.drawRect(rect().left(), rect().top(), rect().width() - 1, rect().height() - 1);

        if (tile->getImage() == nullptr) {
            QFont font = painter.font();
            font.setPixelSize(24);
            painter.setFont(font);
            QString val(std::to_string(tile->getValue()).c_str());
            painter.drawText(rect(), Qt::AlignCenter | Qt::AlignHCenter, val);
        } else {
            QPixmap* pixmap = tile->getImage()->getPixmap();
            int width = tile->getImage()->getPixmap()->width();
            int gridSize = tile->getImage()->getGridSize();
            int value = tile->getValue();
            int tileW = pixmap->width() / gridSize;
            int tileH = pixmap->height() / gridSize;
            QRect dst = rect();
            QRect src((value % gridSize) * tileW, (value / gridSize) * tileH, tileW, tileH);
            painter.drawPixmap(dst, *pixmap, src);
        }
    }
}

void TileWidget::enterEvent(QEvent*) {
    if (tile->getValue() != -1)
        setActive(true);
}

void TileWidget::leaveEvent(QEvent*) {
    setActive(false);
}

void TileWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (clickEnabled == true) {
        emit clicked();
        if (tile->getValue() == -1)
            setActive(false);
    }
}

void TileWidget::setActive(bool active) {
    auto p = palette();
    p.setColor(foregroundRole(), active ? Qt::white : Qt::black);
    p.setColor(backgroundRole(), active ? Qt::gray : Qt::transparent);
    setPalette(p);
}
