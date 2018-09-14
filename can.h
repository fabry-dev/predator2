#ifndef can_H
#define can_H


#include "qobject.h"
#include "qpainter.h"
#include "qlabel.h"
#include "qthread.h"
#include "qevent.h"
#include <QMouseEvent>
#include "qstringlist.h"


#define CAN 0
#define CANGLOW 1
#define CANRED 2
#define PREDATOR1 3
#define PREDATOR2 4



class can:public QLabel
{
    Q_OBJECT

public:
    can(QWidget* parent = 0, int id=-1, int w=10, bool ignoreEmptySpace=true,QString path="");
    ~can();
    void setWidth(int w);
    double ratio;
    void changeType(int nutype);


protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * ev);

private:
    int id;//can identifier
    int type;
    void drawState();
    QImage *canPic,*canglowPic,*canredPic,*predator1Pic,*predator2Pic;
    QFont font;
    bool ignoreEmptySpace;
    QTimer *t0;
    bool frozen;


signals:
    void clicked(int,int);

private slots:
    void goBackToCan();
    void randomChange();
    void freeze();
    void unfreeze();
};








#endif
