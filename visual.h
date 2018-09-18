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
#include "mainwindow.h"

enum states { game_none,game_start,game_info,game_choice,game_keyboard1,game_rules,countdown };

class  MainWindow;


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
    MainWindow *mw;

    QPixmap *startImg,*infoImg,*playersImg,*keyboardImg1,*rulesImg,*cdImg1,*cdImg2,*cdImg3,*cdImg11,*cdImg22,*cdImg33;
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
    void showRules1();
    void showRules2();
    int count;

private slots:
    void showInfo();
    void launchGame1();
    void launchGame2();


public slots:
    void playersChoice();
    void startKeyboard(int playersCount);
    void startCountDown1P();
    void startCountDown2P();

signals:
    void startGame1(QString name);
    void startGame2();

};








#endif // SPLASH_H
