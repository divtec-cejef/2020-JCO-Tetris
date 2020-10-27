#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * Ouvre la fenêtre de jeu après avoir cliqué sur le bouton "Solo"
 */
void MainWindow::on_BT_Solo_clicked()
{
    gameWindow->show();
    this->close();
}

void MainWindow::on_actionQuitter_triggered()
{
    this->close();
}
