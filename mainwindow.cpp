#include "mainwindow.h"
#include "player.h"
#include "tilewidget.h"
#include "ui_mainwindow.h"
#include <string>
#include <iostream>
#include <QMessageBox>
#include <QLabel>
#include <QFileDialog>

MainWindow::MainWindow(GameManager* gm, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    gameManager = gm;
    ui->setupUi(this);
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createBoard() {
    bool ok;
    int size = ui->sizeField->text().toInt(&ok);
    std::string err = "";
    if (!ok) err = "Musisz podać liczbę";
    else if (size < 3) err = "Minimalna wielkość planszy to 3";

    if (err.size() > 0) {
        QMessageBox msgBox;
        msgBox.setText(err.c_str());
        msgBox.exec();
    } else {
        Board* board = gameManager->newGame(size);
        clearTileWidgets();
        createTileWidgetsFromBoard(board);
        ui->radioImage->setEnabled(true);
        ui->radioNumber->setEnabled(true);
    }
}

void MainWindow::clearTileWidgets() {
    while (ui->boardGrid->count()) {
        QWidget* w = ui->boardGrid->itemAt(0)->widget();
        ui->boardGrid->removeWidget(w);
        delete w;
    }
}

void MainWindow::createTileWidgetsFromBoard(Board* board) {
    for (int i = 0; i < board->getSize(); i++) {
        for (int j = 0; j < board->getSize(); j++) {
            TileWidget* tileWidget = new TileWidget(board->tileAt(i, j));
            ui->boardGrid->addWidget(tileWidget, i, j);
            connect(tileWidget, &TileWidget::clicked, [=](){
                board->move(board->tileAt(i, j));
                repaintBoard();
            });
        }
    }
}

void MainWindow::repaintBoard() {
    for (int i = 0; i < ui->boardGrid->count(); i++) {
        ui->boardGrid->itemAt(i)->widget()->update();
    }
}

void MainWindow::setUsername() {
    QString username = ui->usernameField->text();
    Player* player = new Player(username);
    QString text("Gracz: ");
    text.append(username);
    gameManager->setPlayer(player);
    ui->lUsername->setText(text);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::setNumberBoard() {
    if (ui->radioNumber->isChecked())
        std::cout << "test " << std::endl;
}

void MainWindow::setImageBoard() {
    if (ui->radioImage->isChecked()) {
        QStringList mimeTypeFilters({"image/jpeg", "image/png"});
        QFileDialog fdialog;
        fdialog.setMimeTypeFilters(mimeTypeFilters);
        if (fdialog.exec()) {
            QString selectedFile = fdialog.selectedFiles().at(0);
            QPixmap* img = new QPixmap(selectedFile);
            gameManager->getActiveBoard()->setImage(img);
        }
    }
}

void MainWindow::setupConnections() {
    connect(ui->usernameBtn, SIGNAL(clicked(bool)), this, SLOT(setUsername()));
    connect(ui->generateBtn, SIGNAL(clicked(bool)), this, SLOT(createBoard()));
    connect(ui->radioNumber, SIGNAL(toggled(bool)), this, SLOT(setNumberBoard()));
    connect(ui->radioImage, SIGNAL(toggled(bool)), this, SLOT(setImageBoard()));
}
