#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamemanager.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(GameManager* gm, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void createBoard();
    void setUsername();

    void setNumberBoard();
    void setImageBoard();
private:
    Ui::MainWindow *ui;
    GameManager* gameManager;
    void setupConnections();
    void repaintBoard();
    void clearTileWidgets();
    void createTileWidgetsFromBoard(Board *board);
};

#endif // MAINWINDOW_H
