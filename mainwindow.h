#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamemanager.h"

#include <QMainWindow>

enum WindowState {
    WAITING_FOR_USERNAME,
    BOARD_NOT_LOADED,
    BOARD_LOADED,
    SOLVING
};

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
    void showTimeoutMessage();
    void solveEnded();
private:
    WindowState state;
    Ui::MainWindow *ui;
    GameManager* gameManager;
    void setupConnections();
    void clearTileWidgets();
    void createTileWidgetsFromBoard(Board *board);
    void updateControls();
};

#endif // MAINWINDOW_H
