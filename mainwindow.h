#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "visual.h"
#include "qstring.h"
#include "qdebug.h"
#include "game.h"
#include "qtimer.h"
#include "rankingui.h"

#define PATH_DEFAULT (QString)"/home/fred/Dropbox/Taf/Cassiopee/predator2/files/"

class visual;
class game1P;
class rankingUI;

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
    game1P *gm1;
    rankingUI *rk;

    QString PATH;
    bool HIDE_CURSOR;

private:
    Ui::MainWindow *ui;
    void getParams(QStringList params);


private slots:
    void startGame1(QString playerName);
    void startGame2();
    void winGame1(int score,QString playerName);
    void reset(void);


};

#endif // MAINWINDOW_H
