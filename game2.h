#ifndef game2_H
#define game2_H


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


class game2P:public QLabel
{
    Q_OBJECT

public:
    game2P(QWidget *parent = 0);
    ~game2P();
    void win();
    MainWindow *mw;
protected:
    void mousePressEvent( QMouseEvent* ev );

private:
    std::vector<can*> matrix;
    QPixmap *bg2PImg;
    QPixmap *winImg;
    QPixmap *loseImg;
    int score1,score2;
    void updTxt(QLabel *lbl,QString txt);
    QFont font;
    QLabel *score1lbl,*clock1lbl,*score2lbl,*clock2lbl;
    QLabel *msg1lbl,*msg2lbl;
    long clockCount;
    QTimer *clock;




private slots:
    void getCan(int type, int id);
    void tick();
    void preWin();

signals:
    void hasWon2P();
    void restartGame();
    void freeze();


public slots:
    void start();


};








#endif // SPLASH_H
