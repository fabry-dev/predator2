#include "game2.h"
#include "qdebug.h"
#include "qtimer.h"
#include "mainwindow.h"



#define WINTIME 3


#define windowWidth 950
#define windowY0 130
#define GAPX 30

#define buttonWidth 700
#define buttonSpacing 30


#define boxcount 4

#define borderX 30

#define SCORE1_X0 517
#define SCORE1_Y0 20
#define SCORE1_X1 773
#define SCORE1_Y1 115
#define OFFSETY 20

#define CLOCK1_X0 187
#define CLOCK1_Y0 SCORE1_Y0
#define CLOCK1_X1 446
#define CLOCK1_Y1 SCORE1_Y1

#define SCORE2_X0 1452
#define SCORE2_Y0 SCORE1_Y0
#define SCORE2_X1 1719
#define SCORE2_Y1 SCORE1_Y1

#define CLOCK2_X0 1125
#define CLOCK2_Y0 SCORE1_Y0
#define CLOCK2_X1 1383
#define CLOCK2_Y1 SCORE1_Y1

#define OFFSETX 0


#define GAMETIME 60


#define FONTNAME "police.ttf"

const int pointsPerType[] = {0,1,1,2,-5};


game2P::game2P(QWidget *parent):QLabel(parent)
{
    mw = (MainWindow*)(this->parent());

    this->hide();
    this->resize(1920,1080);

    bg2PImg = new QPixmap(mw->PATH+"game2PBG.png");
    winImg = new QPixmap(mw->PATH+"win2P.png");
    loseImg = new QPixmap(mw->PATH+"lose2P.png");



    int id = QFontDatabase::addApplicationFont(mw->PATH+FONTNAME);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(family,75);


    score1lbl = new QLabel(this);
    score1lbl->setText("");
    score1lbl->setFont(font);
    score1lbl->setAlignment(Qt::AlignCenter);
    score1lbl->resize(SCORE1_X1-SCORE1_X0,SCORE1_Y1-SCORE1_Y0);
    score1lbl->move(SCORE1_X0+OFFSETX,SCORE1_Y0+OFFSETY);
    score1lbl->setStyleSheet("QLabel { color : white; }");
    score1lbl->show();

    clock1lbl = new QLabel(this);
    clock1lbl->setText("");
    clock1lbl->setFont(font);
    clock1lbl->setAlignment(Qt::AlignCenter);
    clock1lbl->resize(CLOCK1_X1-CLOCK1_X0,CLOCK1_Y1-CLOCK1_Y0);
    clock1lbl->move(CLOCK1_X0+OFFSETX,CLOCK1_Y0+OFFSETY);
    clock1lbl->setStyleSheet("QLabel { color : white; }");
    clock1lbl->show();



    score2lbl = new QLabel(this);
    score2lbl->setText("");
    score2lbl->setFont(font);
    score2lbl->setAlignment(Qt::AlignCenter);
    score2lbl->resize(SCORE2_X1-SCORE2_X0,SCORE2_Y1-SCORE2_Y0);
    score2lbl->move(SCORE2_X0+OFFSETX,SCORE2_Y0+OFFSETY);
    score2lbl->setStyleSheet("QLabel { color : white; }");
    score2lbl->show();

    clock2lbl = new QLabel(this);
    clock2lbl->setText("");
    clock2lbl->setFont(font);
    clock2lbl->setAlignment(Qt::AlignCenter);
    clock2lbl->resize(CLOCK2_X1-CLOCK2_X0,CLOCK2_Y1-CLOCK2_Y0);
    clock2lbl->move(CLOCK2_X0+OFFSETX,CLOCK2_Y0+OFFSETY);
    clock2lbl->setStyleSheet("QLabel { color : white; }");
    clock2lbl->show();








    msg1lbl = new QLabel(this);
    msg1lbl->resize(winImg->size());
    msg1lbl->move(0,400);
    msg1lbl->show();

    msg2lbl = new QLabel(this);
    msg2lbl->resize(winImg->size());
    msg2lbl->move(windowWidth+GAPX,400);
    msg2lbl->show();




    clock = new QTimer(this);
    connect(clock,SIGNAL(timeout()),this,SLOT(tick()));


    matrix1.clear();
    matrix2.clear();

    int num = 0;

    for(int j = 0;j<4;j++)
        for (int i =0;i<4;i++)
        {

            can *c = new can(this,1,windowWidth/boxcount,false,mw->PATH);
            c->show();
            matrix1.push_back(c);
            c->move((double)i*windowWidth/boxcount,windowY0+c->height()*(j));
            connect(c,SIGNAL(clicked(int,int)),this,SLOT(getCan(int,int)));
            connect(this,SIGNAL(freeze()),c,SLOT(freeze()));
            connect(this,SIGNAL(restartGame()),c,SLOT(unfreeze()));
            num++;
        }

    num  = 0;
    for(int j = 0;j<4;j++)
        for (int i =0;i<4;i++)
        {

            can *c = new can(this,2,windowWidth/boxcount,false,mw->PATH,true);
            c->show();
            matrix2.push_back(c);
            c->move((double)i*windowWidth/boxcount+GAPX+windowWidth,windowY0+c->height()*(j));
            connect(c,SIGNAL(clicked(int,int)),this,SLOT(getCan(int,int)));
            connect(this,SIGNAL(freeze()),c,SLOT(freeze()));
            connect(this,SIGNAL(restartGame()),c,SLOT(unfreeze()));
            connect(matrix1[num],SIGNAL(changedTo(int)),c,SLOT(changeType(int)));

            num++;
        }
}



void game2P::mousePressEvent( QMouseEvent* ev )
{
    QPoint pt = ev->pos();
    //qDebug()<<ev->pos();
}

void game2P::tick(){

    if(clockCount>0)
    {
        clockCount--;
        QString time;

        int ms = (clockCount)%100;
        int sec = (clockCount/100)%60;
        int min = (clockCount/6000);


        time = QString("%1:%2:%3").arg(min, 2, 10, QChar('0')).arg(sec, 2, 10, QChar('0')).arg(ms, 2, 10, QChar('0'));

        updTxt(clock1lbl,time);
        updTxt(clock2lbl,time);
    }
    else
    {
        win();

    }
}

void game2P::updTxt(QLabel *lbl,QString txt)
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

void game2P::start()
{
    score1=score2= 0;

    emit restartGame();
    QString score1str = QString("%1").arg(score1, 4, 10, QChar('0'));
    QString score2str = QString("%1").arg(score1, 4, 10, QChar('0'));
    updTxt(score1lbl,score1str);
    updTxt(score2lbl,score2str);
    qDebug()<<"start game 1P";
    this->setPixmap(*bg2PImg);
    clockCount = GAMETIME*100;
    clock->start(10);
    msg1lbl->hide();
    msg2lbl->hide();
    this->show();
}

void game2P::getCan(int type,int id)
{
    if(id == 1)
    {
        score1+=pointsPerType[type];
        QString scorestr = QString("%1").arg(score1, 4, 10, QChar('0'));
        updTxt(score1lbl,scorestr);
    }
    else
    {
        score2+=pointsPerType[type];
        QString scorestr = QString("%1").arg(score2, 4, 10, QChar('0'));
        updTxt(score2lbl,scorestr);
    }

}

void game2P::win()
{
    if(score1>score2)
    {
        msg1lbl->setPixmap((*winImg).scaledToWidth(windowWidth));
        msg2lbl->setPixmap((*loseImg).scaledToWidth(windowWidth));
    }
    else if(score1<score2)
    {
        msg2lbl->setPixmap((*winImg).scaledToWidth(windowWidth));
        msg1lbl->setPixmap((*loseImg).scaledToWidth(windowWidth));
    }
    else
    {
        msg1lbl->setPixmap((*winImg).scaledToWidth(windowWidth));
        msg2lbl->setPixmap((*winImg).scaledToWidth(windowWidth));
    }

    msg1lbl->show();
    msg2lbl->show();
    msg1lbl->raise();
    msg2lbl->raise();
    clock->stop();
    emit freeze();
    QTimer::singleShot(1000*WINTIME,this,SLOT(preWin()));

}

void game2P::preWin()
{

    emit hasWon2P();
}



game2P::~game2P()
{


}


