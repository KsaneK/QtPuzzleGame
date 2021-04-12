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
    void saveGame();
    void loadGame();
    void solve();
    void repaintBoard();
private:
    Ui::MainWindow *ui;
    GameManager* gameManager;
    void setupConnections();
    void clearTileWidgets();
    void createTileWidgetsFromBoard(Board *board);
};

#endif // MAINWINDOW_H
