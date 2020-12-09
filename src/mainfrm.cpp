#include "mainfrm.h"
#include "ui_mainfrm.h"

MainFrm::MainFrm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainFrm)
{
    ui->setupUi(this);
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
    ui->GameBox->startTimer();
}
