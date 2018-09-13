#ifndef game_H
#define game_H


#include "qobject.h"
#include "qpainter.h"
#include "qlabel.h"
#include "qthread.h"
#include "qevent.h"
#include <QMouseEvent>
#include "qstringlist.h"
#include "button.h"
#include "mainwindow.h"


class MainWindow;


class game:public QLabel
{
    Q_OBJECT

public:
    game(QWidget *parent = 0);
    ~game();
    void start(int playersCount, QString playerName1, QString playerName2="");

private:
    QPixmap *bgImg;
    MainWindow *mw;





};








#endif // SPLASH_H
