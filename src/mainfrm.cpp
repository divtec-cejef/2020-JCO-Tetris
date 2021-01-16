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

    // Connexion du signal relatif à la fin de la partie
    connect(ui->GameBox, &TetrisWidget::endOfGame, this, &MainFrm::onEndOfGame);

    // Connexion des signaux relatifs au nombre de lignes supprimées
    connect(ui->GameBox, &TetrisWidget::oneRowDeleted, this, &MainFrm::oneRowDeleted);
    connect(ui->GameBox, &TetrisWidget::twoRowDeleted, this, &MainFrm::twoRowDeleted);
    connect(ui->GameBox, &TetrisWidget::threeRowDeleted, this, &MainFrm::threeRowDeleted);
    connect(ui->GameBox, &TetrisWidget::fourRowDeleted, this, &MainFrm::fourRowDeleted);
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


    // Réinitialise le score du joueur
    score = 0;
    level = 0;
    ui->TXT_Score->setText("Score : " + QString::number(score));
    ui->TXT_Level->setText("Niveau : " + QString::number(level));
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
    score += 40*(level+1);
    ui->TXT_Score->setText("Score : " + QString::number(score));
}

/**
 * Code effectué quand le nombre de ligne supprimé est égal à 2
 */
void MainFrm::twoRowDeleted() {
    score += 100*(level+1);
    ui->TXT_Score->setText("Score : " + QString::number(score));
}

/**
 * Code effectué quand le nombre de ligne supprimé est égal à 3
 */
void MainFrm::threeRowDeleted() {
    score += 300*(level+1);
    ui->TXT_Score->setText("Score : " + QString::number(score));
}

/**
 * Code effectué quand le nombre de ligne supprimé est égal à 4
 */
void MainFrm::fourRowDeleted() {
    score += 1200*(level+1);
    ui->TXT_Score->setText("Score : " + QString::number(score));
}
