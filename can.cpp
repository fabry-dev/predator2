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


can::can(QWidget* parent , int id,int w,bool ignoreEmptySpace,QString path)
    : QLabel(parent),id(id),ignoreEmptySpace(ignoreEmptySpace)
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


    type = CAN;
    drawState();


    t0 = new QTimer(this);
    connect(t0,SIGNAL(timeout()),this,SLOT(randomChange()));
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

    if(type==CAN)
        pix = QPixmap::fromImage((*canPic).scaled(width(),height()));
    else if (type==CANRED)
        pix = QPixmap::fromImage((*canredPic).scaled(width(),height()));
    else if (type==CANGLOW)
        pix = QPixmap::fromImage((*canglowPic).scaled(width(),height()));
    else if (type==PREDATOR1)
        pix = QPixmap::fromImage((*predator1Pic).scaled(width(),height()));
    else if (type==PREDATOR2)
        pix = QPixmap::fromImage((*predator2Pic).scaled(width(),height()));


    setPixmap(pix);
}

void can::goBackToCan()
{
    type = CAN;
    drawState();
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

void can::changeType(int nutype)
{
    if(frozen)
        return;

    type = nutype;
    drawState();
    QTimer::singleShot(TIMEON,this,SLOT(goBackToCan()));

}

void can::mousePressEvent( QMouseEvent* ev )
{
    QImage image(pixmap()->toImage());
    QColor color(image.pixel(ev->pos()));

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

