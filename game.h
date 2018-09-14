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
#include "can.h"

class MainWindow;


class game1P:public QLabel
{
    Q_OBJECT

public:
    game1P(QWidget *parent = 0);
    ~game1P();

    MainWindow *mw;
protected:
    void mousePressEvent( QMouseEvent* ev );

private:
    std::vector<can*> matrix;
    QPixmap *bg1PImg;
    QPixmap *bg2PImg;
    QPixmap *win1PImg;
    int score;
    void updTxt(QLabel *lbl,QString txt);
    QFont font;
    QLabel *score1P,*clock1P;
    QLabel *win1Plbl;
    long clockCount;
    QTimer *clock;
    void win1p();
    QString playerName;


private slots:
    void getCan1P(int type);
    void tick();

signals:
    void hasWon1P(int,QString);
    void restartGame();


public slots:
    void start(QString nuPlayerName="");


};








#endif // SPLASH_H
