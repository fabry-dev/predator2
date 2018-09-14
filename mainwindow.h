#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "visual.h"
#include "qstring.h"
#include "qdebug.h"
#include "game1.h"
#include "game2.h"
#include "qtimer.h"
#include "rankingui.h"

#define PATH_DEFAULT (QString)"/home/fred/Dropbox/Taf/Cassiopee/predator2/files/"

class visual;
class game1P;
class rankingUI;
class game2P;

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
    game2P *gm2;
    rankingUI *rk;

    QString PATH;
    bool HIDE_CURSOR;
    std::vector<int> params;

private:
    Ui::MainWindow *ui;
    void getParams(QStringList params);
    void loadParamsFile();


private slots:
    void startGame1(QString playerName);
    void startGame2();
    void winGame1(int score,QString playerName);
    void winGame2();
    void reset(void);


};

#endif // MAINWINDOW_H
