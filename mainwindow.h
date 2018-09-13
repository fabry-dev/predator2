#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "visual.h"
#include "qstring.h"
#include "qdebug.h"
#include "game.h"

#define PATH_DEFAULT (QString)"/home/fred/Dropbox/Taf/Cassiopee/predator2/files/"

class visual;
class game;

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
    QString PATH;
    bool HIDE_CURSOR;

private:
    Ui::MainWindow *ui;
    void getParams(QStringList params);

private slots:
    void startGame1(QString playerName);

};

#endif // MAINWINDOW_H
