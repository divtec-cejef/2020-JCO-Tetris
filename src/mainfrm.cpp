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

