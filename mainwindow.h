#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamewindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionQuitter_triggered();

    void on_BT_Solo_clicked();

private:
    Ui::MainWindow *ui;
    gamewindow *gameWindow = new gamewindow;
};

#endif // MAINWINDOW_H