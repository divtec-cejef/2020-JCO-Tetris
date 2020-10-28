#ifndef INTRO_WINDOW_H
#define INTRO_WINDOW_H

#include <QMainWindow>

namespace Ui {
class intro_window;
}

class intro_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit intro_window(QWidget *parent = nullptr);
    ~intro_window();

private slots:
    void on_actionQuitter_triggered();

    void on_BT_Solo_clicked();

private:
    Ui::intro_window *ui;
};

#endif // INTRO_WINDOW_H
