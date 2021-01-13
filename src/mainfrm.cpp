// 2020-JCO-Tetris
// Auteur : Membrez Matteo
// Date de la dernière modification : 11.01.21

#include "mainfrm.h"
#include "ui_mainfrm.h"

MainFrm::MainFrm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainFrm)
{
    ui->setupUi(this);
    ui->TXT_GameOver->setVisible(false);

    connect(ui->GameBox, &TetrisWidget::endOfGame, this, &MainFrm::onEndOfGame);

    connect(ui->GameBox, &TetrisWidget::oneRowDeleted, this, &MainFrm::oneRowDeleted);
    connect(ui->GameBox, &TetrisWidget::oneRowDeleted, this, &MainFrm::twoRowDeleted);
    connect(ui->GameBox, &TetrisWidget::oneRowDeleted, this, &MainFrm::threeRowDeleted);
    connect(ui->GameBox, &TetrisWidget::oneRowDeleted, this, &MainFrm::fourRowDeleted);
}

MainFrm::~MainFrm()
{
    delete ui;
}

/**
 * Lance le jeu au clic du bouton
 */
void MainFrm::on_BT_Start_clicked()
{
    ui->GameBox->startTimer(1000);
    ui->BT_Start->setEnabled(false);
    ui->TXT_GameOver->setVisible(false);
}

/**
 * S'exécute à chaque fois que le jeu est terminé
 */
void MainFrm::onEndOfGame() {
    ui->BT_Start->setEnabled(true);
    ui->TXT_GameOver->setVisible(true);
}

/**
 * Code effectué quand le nombre de ligne supprimé est égal à 1
 */
void MainFrm::oneRowDeleted() {

}

/**
 * Code effectué quand le nombre de ligne supprimé est égal à 2
 */
void MainFrm::twoRowDeleted() {

}

/**
 * Code effectué quand le nombre de ligne supprimé est égal à 3
 */
void MainFrm::threeRowDeleted() {

}

/**
 * Code effectué quand le nombre de ligne supprimé est égal à 4
 */
void MainFrm::fourRowDeleted() {

}
