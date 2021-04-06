#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameManager gm;
    MainWindow w(&gm, nullptr);
    w.show();

    return a.exec();
}
