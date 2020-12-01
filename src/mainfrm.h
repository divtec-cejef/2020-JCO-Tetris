#ifndef MAINFRM_H
#define MAINFRM_H

#include <QWidget>

namespace Ui {
class MainFrm;
}

class MainFrm : public QWidget
{
    Q_OBJECT

public:
    MainFrm(QWidget *parent = nullptr);
    ~MainFrm();

private slots:
    void on_BT_Start_clicked();

private:
    Ui::MainFrm *ui;
};

#endif // MAINFRM_H
