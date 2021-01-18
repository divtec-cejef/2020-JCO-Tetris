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
    connect(ui->GameBox, &TetrisWidget::rowDeleted, this, &MainFrm::onRowDeleted);
    connect(ui->GameBox, &TetrisWidget::oneRowDeleted, this, &MainFrm::onOneRowDeleted);
    connect(ui->GameBox, &TetrisWidget::twoRowDeleted, this, &MainFrm::onTwoRowDeleted);
    connect(ui->GameBox, &TetrisWidget::threeRowDeleted, this, &MainFrm::onThreeRowDeleted);
    connect(ui->GameBox, &TetrisWidget::fourRowDeleted, this, &MainFrm::onFourRowDeleted);

    initStyle();

}

MainFrm::~MainFrm()
{
    delete ui;
}

void MainFrm::initStyle() {
    ui->BT_Start->setStyleSheet("color: white;"
                                "border-radius: 8px;"
                                "background-color: crimson");
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

    ui->BT_Start->setStyleSheet("color: black;"
                                "border-radius: 8px;"
                                "background-color: grey");
}


/**
 * S'exécute à chaque fois que le jeu est terminé
 */
void MainFrm::onEndOfGame() {
    ui->BT_Start->setEnabled(true);
    ui->TXT_GameOver->setVisible(true);

    initStyle();
}

/**
 * Code effectué quand au moins une ligne est supprimée
 */
void MainFrm::onRowDeleted() {

    if(score >= SCORE_LEVEL1 && score < SCORE_LEVEL2) {
        level = 1;
        ui->GameBox->setTimer(SPEED_LEVEL1);
    } else if(score >= SCORE_LEVEL2 && score < SCORE_LEVEL3) {
        level = 2;
        ui->GameBox->setTimer(SPEED_LEVEL2);
    } else if(score >= SCORE_LEVEL3 && score < SCORE_LEVEL4) {
        level = 3;
        ui->GameBox->setTimer(SPEED_LEVEL3);
    } else if(score >= SCORE_LEVEL4 && score < SCORE_LEVEL5) {
        level = 4;
        ui->GameBox->setTimer(SPEED_LEVEL4);
    } else if(score >= SCORE_LEVEL5 && score < SCORE_LEVEL6) {
        level = 5;
        ui->GameBox->setTimer(SPEED_LEVEL5);
    } else if(score >= SCORE_LEVEL6) {
        level = 6;
        ui->GameBox->setTimer(SPEED_LEVEL6);
    }

    // Affiche le niveau actuel
    ui->TXT_Level->setText("Niveau : " + QString::number(level));

}

/**
 * Code effectué quand le nombre de ligne supprimé est égal à 1
 */
void MainFrm::onOneRowDeleted() {
    score += 40*(level+1);
    ui->TXT_Score->setText("Score : " + QString::number(score));
}

/**
 * Code effectué quand le nombre de ligne supprimé est égal à 2
 */
void MainFrm::onTwoRowDeleted() {
    score += 100*(level+1);
    ui->TXT_Score->setText("Score : " + QString::number(score));
}

/**
 * Code effectué quand le nombre de ligne supprimé est égal à 3
 */
void MainFrm::onThreeRowDeleted() {
    score += 300*(level+1);
    ui->TXT_Score->setText("Score : " + QString::number(score));
}

/**
 * Code effectué quand le nombre de ligne supprimé est égal à 4
 */
void MainFrm::onFourRowDeleted() {
    score += 1200*(level+1);
    ui->TXT_Score->setText("Score : " + QString::number(score));
}
