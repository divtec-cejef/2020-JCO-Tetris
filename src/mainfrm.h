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
    explicit MainFrm(QWidget *parent = nullptr);
    ~MainFrm();

private:
    Ui::MainFrm *ui;
};

#endif // MAINFRM_H
