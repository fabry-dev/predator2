#include "game.h"
#include "qdebug.h"
#include "qtimer.h"
#include "mainwindow.h"


#define INFO_TIME 3000

#define buttonWidth 700
#define buttonSpacing 30


game::game(QWidget *parent):QLabel(parent)
{

    this->hide();
    this->resize(1920,1080);

    bgImg = new QPixmap(PATH+"gameBG.png");

}



void game::start(int players, QString playerName1, QString playerName2)
{

    this->setPixmap(*bgImg);
    this->show();

}




game::~game()
{


}


