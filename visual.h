#ifndef visual_H
#define visual_H


#include "qobject.h"
#include "qpainter.h"
#include "qlabel.h"
#include "qthread.h"
#include "qevent.h"
#include <QMouseEvent>
#include "qstringlist.h"
#include "button.h"
#include "qfontdatabase.h"

enum states { game_none,game_start,game_info,game_choice,game_keyboard1,game_keyboard2 };


struct key {
   int x1,y1,x2,y2;
   QString txt;
};

class visual:public QLabel
{
    Q_OBJECT

public:
    visual(QWidget *parent = 0);
    ~visual();
    void mousePressEvent( QMouseEvent* ev );
    void start();

private:
    QPixmap *startImg,*infoImg,*playersImg,*keyboardImg1,*keyboardImg2;
    button *bOne,*bTwo;
    states gameState;
    QLabel *name1P,*name2P1,*name2P2;
    void updTxt(QLabel *lbl,QString txt);
    QFont font;
    QString name1,name21,name22;
    void addKey(std::vector<key> *keyMap, int x1, int y1, int x2, int y2, QString txt);
    std::vector<key> keyMap1,keyMap21,keyMap22;
    void initKeyboards();
    void keyIn1(QString k);


private slots:
    void showInfo();

public slots:
    void playersChoice();
    void startKeyboard(int playersCount);

signals:
    void startGame1(QString name);


};








#endif // SPLASH_H
