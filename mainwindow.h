#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "visual.h"
#include "qstring.h"
#include "qdebug.h"
#include "game.h"

#define PATH (QString)"/home/fred/Dropbox/Taf/Cassiopee/predator2/files/"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    visual *vs;
    game *gm;

private:
    Ui::MainWindow *ui;

private slots:
    void startGame1(QString playerName);

};

#endif // MAINWINDOW_H
