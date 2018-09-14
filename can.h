#ifndef can_H
#define can_H


#include "qobject.h"
#include "qpainter.h"
#include "qlabel.h"
#include "qthread.h"
#include "qevent.h"
#include <QMouseEvent>
#include "qstringlist.h"
#include "QPropertyAnimation"

#define CAN 0
#define CANGLOW 1
#define CANRED 2
#define PREDATOR1 3
#define PREDATOR2 4


class MainWindow;


class can:public QWidget
{
    Q_OBJECT

public:
    can(QWidget* parent = 0, int id=-1, int w=10, bool ignoreEmptySpace=true, QString path="", bool slave=false);
    ~can();
    void setWidth(int w);
    double ratio;



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
    bool slave;
    QTimer *t0;
    bool frozen;
    QLabel *lbl1,*lbl2;
    QPropertyAnimation *appearance1,*disappearance1,*appearance2,*disappearance2;
    MainWindow *mw;

   // void changeType(int nutype);

signals:
    void clicked(int,int);
    void changedTo(int nutype);

private slots:
    void goBackToCan();
    void randomChange();
    void freeze();
    void unfreeze();
    void setType(int nutype);
    void changeType(int nutype);
};








#endif
