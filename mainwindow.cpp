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
    state = WindowState::WAITING_FOR_USERNAME;
    updateControls();
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
        Board* board = gameManager->newGame(size, ui->radioImage->isChecked());
        connect(board, SIGNAL(moved()), this, SLOT(repaintBoard()));
        clearTileWidgets();
        createTileWidgetsFromBoard(board);
        state = WindowState::BOARD_LOADED;
        updateControls();
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
    state = WindowState::BOARD_NOT_LOADED;
    updateControls();
}

void MainWindow::setNumberBoard() {
    if (ui->radioNumber->isChecked()) {
        gameManager->getActiveBoard()->clearImage();
        repaintBoard();
    }
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
            repaintBoard();
        }
    }
}

void MainWindow::saveGame() {
    QFileDialog fdialog(this);
    fdialog.setAcceptMode(QFileDialog::AcceptMode::AcceptSave);
    fdialog.setNameFilter(QString::fromStdString("Puzzzle Save Files (*.puzz)"));
    fdialog.setDefaultSuffix("puzz");
    if(fdialog.exec()) {
        QString fileName = fdialog.selectedFiles().at(0);
        gameManager->saveGame(fileName);
    }
}

void MainWindow::loadGame() {
    QFileDialog fdialog(this);
    fdialog.setFileMode(QFileDialog::AnyFile);
    fdialog.setNameFilter(QString::fromStdString("Puzzzle Save Files (*.puzz)"));
    fdialog.setDefaultSuffix(QString::fromStdString("puzz"));
    if (fdialog.exec()) {
        QString selectedFile = fdialog.selectedFiles().at(0);
        bool loaded = gameManager->loadGame(selectedFile);
        if (loaded) {
            state = WindowState::BOARD_LOADED;
            updateControls();
            clearTileWidgets();
            createTileWidgetsFromBoard(gameManager->getActiveBoard());
            connect(gameManager->getActiveBoard(), SIGNAL(moved()), this, SLOT(repaintBoard()));
            repaintBoard();
        } else {
            QMessageBox msgbox;
            msgbox.setText("Nie udało się wczytać gry. Plik może być uszkodzony.");
            msgbox.exec();
        }
    }
}

void MainWindow::solve() {
    gameManager->solve(SolverType::IDAStar);
}

void MainWindow::showTimeoutMessage() {
    QMessageBox msgbox;
    msgbox.setText("Nie udało się znaleźć rozwiązania w ciągu 10 sekund.");
    msgbox.exec();
}

void MainWindow::updateControls() {
    ui->radioNumber->setEnabled(state == WindowState::BOARD_LOADED);
    ui->radioImage->setEnabled(state == WindowState::BOARD_LOADED);
    ui->actionZapisz_gr->setEnabled(state == WindowState::BOARD_LOADED);
    ui->actionWczytaj_gr->setEnabled(state != WindowState::WAITING_FOR_USERNAME);
    ui->solveBtn->setEnabled(state == WindowState::BOARD_LOADED && gameManager->getActiveBoard()->getSize() <= 4);
}

void MainWindow::setupConnections() {
    connect(ui->usernameBtn, SIGNAL(clicked(bool)), this, SLOT(setUsername()));
    connect(ui->generateBtn, SIGNAL(clicked(bool)), this, SLOT(createBoard()));
    connect(ui->radioNumber, SIGNAL(toggled(bool)), this, SLOT(setNumberBoard()));
    connect(ui->radioImage, SIGNAL(toggled(bool)), this, SLOT(setImageBoard()));
    connect(ui->actionWczytaj_gr, SIGNAL(triggered(bool)), this, SLOT(loadGame()));
    connect(ui->actionZapisz_gr, SIGNAL(triggered(bool)), this, SLOT(saveGame()));
    connect(ui->solveBtn, SIGNAL(clicked(bool)), this, SLOT(solve()));
    connect(gameManager, SIGNAL(solveTimeout()), this, SLOT(showTimeoutMessage()));
}
