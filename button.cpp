#include "algorithm"
#include "qdebug.h"
#include "qtimer.h"
#include "mainwindow.h"
#include "QFont"
#include "qfontdatabase.h"
#include "qpalette.h"
#include "qtextdocument.h"
#include "qstatictext.h"




button::button(QWidget* parent , int id, int w, QString on, QString off,bool ignoreEmptySpace)
    : QLabel(parent),id(id),ignoreEmptySpace(ignoreEmptySpace)
{

    hide();

    offPix = new QImage(off); //preload image
    onPix = new QImage(on); //preload image




    ratio = (double)(offPix->width())/(offPix->height());

    setWidth(w);


    //this->setStyleSheet("border: 1px solid black");


    QPainter p1(offPix);
    p1.setPen(QPen(Qt::white));
    p1.setFont(font);



    p1.drawText(offPix->rect(), Qt::AlignCenter, text());


    QPainter p2(onPix);
    p2.setPen(QPen(Qt::white));
    p2.setFont(font);
    p2.drawText(onPix->rect(), Qt::AlignCenter, text());

    drawState(false);

}


void button::setWidth(int w)
{
    int h = offPix->height()*w/offPix->width();
    this->resize(w,h);
}




void button::drawState(bool state)
{
    QPixmap pix;

    if(state)
        pix = QPixmap::fromImage((*onPix).scaled(width(),height()));
    else
        pix = QPixmap::fromImage((*offPix).scaled(width(),height()));

    setPixmap(pix);
}


void button::mousePressEvent( QMouseEvent* ev )
{
    QImage image(pixmap()->toImage());
    QColor color(image.pixel(ev->pos()));



    if((color.black()==255)&(color.hslHue()==-1)&(color.hslSaturation()==0)&(ignoreEmptySpace))//transparent area
        return;

    drawState(true);

}


void button::mouseReleaseEvent(QMouseEvent * ev)
{
    drawState(false);
     emit clicked(id);
}


button::~button()
{


}

