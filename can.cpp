#include "algorithm"
#include "qdebug.h"
#include "qtimer.h"
#include "mainwindow.h"
#include "QFont"
#include "qfontdatabase.h"
#include "qpalette.h"
#include "qtextdocument.h"
#include "qstatictext.h"
#include "QTime"



#define TIMEON 1000
#define DT 300


can::can(QWidget* parent , int id,int w,bool ignoreEmptySpace,QString path,bool slave)
    : QWidget(parent),id(id),ignoreEmptySpace(ignoreEmptySpace),slave(slave)
{

    hide();

    QTime now = QTime::currentTime();
    qsrand(now.msec());

    canPic = new QImage(path+"can.png");
    canglowPic =  new QImage(path+"canglow.png");
    canredPic =  new QImage(path+"canred.png");
    predator1Pic =  new QImage(path+"predator.png");
    predator2Pic =  new QImage(path+"predator2.png");






    frozen = false;










    ratio = (double)(canPic->width())/(canPic->height());

    setWidth(w);


    //this->setStyleSheet2("border: 1px solid black");



    lbl1 = new QLabel(this);
    lbl1->resize(size());
    lbl1->setPixmap(QPixmap::fromImage((*canPic).scaled(width(),height())));
    lbl2 = new QLabel(this);
    lbl2->resize(size());


    appearance1 = new QPropertyAnimation(lbl1, "geometry");
    appearance1->setDuration(200);
    appearance1->setStartValue(QRect(-width(), 0, width(),height()));
    appearance1->setEndValue(QRect(0, 0, width(),height()));
    appearance1->setEasingCurve(QEasingCurve::InCurve);


    disappearance1 = new QPropertyAnimation(lbl1, "geometry");
    disappearance1->setDuration(200);
    disappearance1->setStartValue(QRect(0, 0, width(),height()));
    disappearance1->setEndValue(QRect(-width(), 0, width(),height()));
    disappearance1->setEasingCurve(QEasingCurve::InCurve);
    connect(disappearance1,SIGNAL(finished()),lbl1,SLOT(hide()));

    appearance2 = new QPropertyAnimation(lbl2, "geometry");
    appearance2->setDuration(200);
    appearance2->setStartValue(QRect(width(), 0, width(),height()));
    appearance2->setEndValue(QRect(0, 0, width(),height()));
    appearance2->setEasingCurve(QEasingCurve::InCurve);


    disappearance2 = new QPropertyAnimation(lbl2, "geometry");
    disappearance2->setDuration(200);
    disappearance2->setStartValue(QRect(0, 0, width(),height()));
    disappearance2->setEndValue(QRect(width(), 0, width(),height()));
    disappearance2->setEasingCurve(QEasingCurve::InCurve);
    connect(disappearance2,SIGNAL(finished()),lbl2,SLOT(hide()));














    type = CAN;
    drawState();


    t0 = new QTimer(this);
    connect(t0,SIGNAL(timeout()),this,SLOT(randomChange()));
    if(!slave)

    t0->start(DT);

}

void can::setWidth(int w)
{
    int h = canPic->height()*w/canPic->width();
    this->resize(w,h);
}

void can::randomChange()
{
    if(type != CAN)
        return;

    int r = qrand()%1000;

    if(r<10)
        changeType(CANGLOW);
    else if(r<20)
        changeType(CANRED);
    else if(r<25)
        changeType(PREDATOR1);
    else if(r<30)
        changeType(PREDATOR2);



}

void can::drawState()
{
    QPixmap pix;
    appearance1->stop();
    disappearance2->stop();
    appearance2->stop();
    disappearance1->stop();
    if(type==CAN)
    {
        appearance1->start();
        disappearance2->start();
    }
    else
    {
        if (type==CANRED)
            pix = QPixmap::fromImage((*canredPic).scaled(width(),height()));
        else if (type==CANGLOW)
            pix = QPixmap::fromImage((*canglowPic).scaled(width(),height()));
        else if (type==PREDATOR1)
            pix = QPixmap::fromImage((*predator1Pic).scaled(width(),height()));
        else if (type==PREDATOR2)
            pix = QPixmap::fromImage((*predator2Pic).scaled(width(),height()));

        lbl2->setPixmap(pix);
        appearance2->start();
        disappearance1->start();
    }


    lbl2->show();
    lbl1->show();
}

void can::goBackToCan()
{
    setType(CAN);
    if(slave)
        return;
}

void can::freeze()
{
    goBackToCan();
    frozen = true;
}

void can::unfreeze()
{
    frozen = false;

}




void can::setType(int nutype)
{
    if(type == nutype)
        return;


    type = nutype;
    drawState();
}

void can::changeType(int nutype)
{


    if(frozen)
        return;


    emit changedTo(nutype);


    setType(nutype);

    QTimer::singleShot(TIMEON,this,SLOT(goBackToCan()));

}

void can::mousePressEvent( QMouseEvent* ev )
{


    if(frozen)
        return;

    if(type != CAN)
    {
        emit clicked(type,id);
        goBackToCan();
    }
}

void can::mouseReleaseEvent(QMouseEvent * ev)
{

}

can::~can()
{


}

