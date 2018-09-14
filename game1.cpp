#include "game1.h"
#include "qdebug.h"
#include "qtimer.h"
#include "mainwindow.h"

#define WINTIME 3
#define INFO_TIME 3000

#define buttonWidth 700
#define buttonSpacing 30

#define windowY0 275
#define boxcount 7

#define borderX 30
#define SCORE1P_X0 1650
#define SCORE1P_Y0 0
#define SCORE1P_X1 1918
#define SCORE1P_Y1 275
#define OFFSETY 20


#define CLOCK1P_X0 0
#define CLOCK1P_Y0 0
#define CLOCK1P_X1 275
#define CLOCK1P_Y1 275


#define OFFSETX 0


#define GAMETIME (mw->params[2])


#define FONTNAME "police.ttf"

const int pointsPerType[] = {0,1,1,2,-5};


game1P::game1P(QWidget *parent):QLabel(parent)
{
    mw = (MainWindow*)(this->parent());

    this->hide();
    this->resize(1920,1080);

    bg1PImg = new QPixmap(mw->PATH+"game1PBG.png");
    //bg2PImg = new QPixmap(mw->PATH+"game2PBG.png");
    win1PImg = new QPixmap(mw->PATH+"win1p.png");

    int id = QFontDatabase::addApplicationFont(mw->PATH+FONTNAME);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(family,75);


    score1P = new QLabel(this);
    score1P->setText("");
    score1P->setFont(font);
    score1P->setAlignment(Qt::AlignCenter);
    score1P->resize(SCORE1P_X1-SCORE1P_X0,SCORE1P_Y1-SCORE1P_Y0);
    score1P->move(SCORE1P_X0+OFFSETX,SCORE1P_Y0+OFFSETY);
    score1P->setStyleSheet("QLabel { color : white; }");
    score1P->show();

    clock1P = new QLabel(this);
    clock1P->setText("");
    clock1P->setFont(font);
    clock1P->setAlignment(Qt::AlignCenter);
    clock1P->resize(CLOCK1P_X1-CLOCK1P_X0,CLOCK1P_Y1-CLOCK1P_Y0);
    clock1P->move(CLOCK1P_X0+OFFSETX,CLOCK1P_Y0+OFFSETY);
    clock1P->setStyleSheet("QLabel { color : white; }");
    clock1P->show();

    win1Plbl = new QLabel(this);
    win1Plbl->resize(win1PImg->size());
    win1Plbl->setPixmap(*win1PImg);
    win1Plbl->move(0,600);
    win1Plbl->hide();


    clock = new QTimer(this);
    connect(clock,SIGNAL(timeout()),this,SLOT(tick()));


    matrix.clear();

    int num = 0;

    for(int j = 0;j<4;j++)
        for (int i =0;i<boxcount;i++)
        {
            if(!((j==0)&&((i==0)||(i==6))))
            {
                can *c = new can(this,num,width()/boxcount+1,false,mw->PATH);
                c->show();
                matrix.push_back(c);
                c->move((double)i*width()/boxcount,c->height()*(j));
                connect(c,SIGNAL(clicked(int,int)),this,SLOT(getCan(int,int)));
                connect(this,SIGNAL(freeze()),c,SLOT(freeze()));
                connect(this,SIGNAL(restartGame()),c,SLOT(unfreeze()));
                num++;
            }
        }



}



void game1P::mousePressEvent( QMouseEvent* ev )
{
    QPoint pt = ev->pos();
    qDebug()<<ev->pos();
}

void game1P::tick(){

    if(clockCount>0)
    {
        clockCount--;
        QString time;

        int ms = (clockCount)%100;
        int sec = (clockCount/100)%60;
        int min = (clockCount/6000);


        time = QString("%1:%2:%3").arg(min, 2, 10, QChar('0')).arg(sec, 2, 10, QChar('0')).arg(ms, 2, 10, QChar('0'));

        updTxt(clock1P,time);
    }
    else
        win1p();

}

void game1P::updTxt(QLabel *lbl,QString txt)
{
    QFontMetrics metrics(font);
    QSize size = metrics.size(0, txt); //Get size of text
    float factorw = (lbl->width()-2*borderX) / (float)size.width(); //Get the width factor
    float factorh = (lbl->height()) / (float)size.height(); //Get the height factor
    float factor = qMin(factorw, factorh); //To fit contents in the screen select as factor
    //the minimum factor between width and height

    font.setPointSizeF(font.pointSizeF() * factor); //Set font size

    lbl->setFont(font);
    lbl->setText(txt);
}

void game1P::start(QString nuPlayerName)
{
    score = 0;
    playerName = nuPlayerName;
    emit restartGame();
    QString score2 = QString("%1").arg(score, 4, 10, QChar('0'));
    updTxt(score1P,score2);
    qDebug()<<"start game 1P";
    this->setPixmap(*bg1PImg);
    clockCount = GAMETIME*100;
    clock->start(10);
    win1Plbl->hide();
    this->show();
}

void game1P::getCan(int type,int id)
{
    score+=pointsPerType[type];
    QString score2 = QString("%1").arg(score, 4, 10, QChar('0'));
    updTxt(score1P,score2);
}

void game1P::win1p()
{
    win1Plbl->show();
    win1Plbl->raise();
    clock->stop();
    emit freeze();
    QTimer::singleShot(1000*WINTIME,this,SLOT(preWin()));

}

void game1P::preWin()
{
        emit hasWon1P(score,playerName);

}

game1P::~game1P()
{


}


