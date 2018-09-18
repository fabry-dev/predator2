#include "visual.h"
#include "qdebug.h"
#include "qtimer.h"
#include "mainwindow.h"


#define INFO_TIME 3000
#define TIMETOLAUNCH 6

#define buttonWidth 700
#define buttonSpacing 30


#define borderX 10
#define TEXT1P_X0 854
#define TEXT1P_Y0 251
#define TEXT1P_X1 1495
#define TEXT1P_Y1 325
#define NAME1_MAX_LENGTH 25
#define NAME1_MIN_LENGTH 3


#define FONTNAME "Futura.ttc"


visual::visual(QWidget *parent):QLabel(parent)
{
    mw = (MainWindow*)(this->parent());


    gameState = game_none;
    this->hide();
    this->resize(1920,1080);

    startImg = new QPixmap(mw->PATH+"startBG.png");
    infoImg = new QPixmap(mw->PATH+"infoBG.png");
    playersImg = new QPixmap(mw->PATH+"playersBG.png");
    keyboardImg1 = new QPixmap(mw->PATH+"keyboardBG1.png");
    rulesImg = new QPixmap(mw->PATH+"pointsBG.png");
    cdImg1 = new QPixmap(mw->PATH+"CD1.png");
    cdImg2 = new QPixmap(mw->PATH+"CD2.png");
    cdImg3 = new QPixmap(mw->PATH+"CD3.png");
    cdImg11 = new QPixmap(mw->PATH+"CD1-1.png");
    cdImg22 = new QPixmap(mw->PATH+"CD2-2.png");
    cdImg33 = new QPixmap(mw->PATH+"CD3-3.png");


    int id = QFontDatabase::addApplicationFont(mw->PATH+FONTNAME);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(family,50);
    name1P = new QLabel(this);
    name1P->setText("");
    name1P->setFont(font);
    name1P->setAlignment(Qt::AlignCenter);
    name1P->resize(TEXT1P_X1-TEXT1P_X0,TEXT1P_Y1-TEXT1P_Y0);
    name1P->move(TEXT1P_X0,TEXT1P_Y0);
    name1P->hide();

    initKeyboards();


    bOne = new button(this,1,buttonWidth,mw->PATH+"onePlayer2.png",mw->PATH+"onePlayer.png",true);
    bOne->move((width()-2*bOne->width()-buttonSpacing)/2,500);
    connect(bOne,SIGNAL(clicked(int)),this,SLOT(startKeyboard(int)));
    bTwo = new button(this,2,buttonWidth,mw->PATH+"twoPlayers2.png",mw->PATH+"twoPlayers.png",true);
    bTwo->move(width()-bOne->width()-bOne->x(),500);
    connect(bTwo,SIGNAL(clicked(int)),this,SLOT(startKeyboard(int)));



    //
}

void visual::mousePressEvent( QMouseEvent* ev )
{
    QPoint pt = ev->pos();


    if(gameState==game_start)
        this->showInfo();
    else if(gameState==game_keyboard1)
    {
        for (auto b:keyMap1)
        {
            if((pt.x()>b.x1)&&(pt.x()<b.x2)&&(pt.y()>b.y1)&(pt.y()<b.y2))
            {
                keyIn1(b.txt);
            }
        }
    }

    // qDebug()<<ev->pos();
}


void visual::start(void)
{
    gameState = game_start;
    name1P->hide();
    this->setPixmap(*startImg);
    this->show();
}


void visual::showInfo()
{
    gameState = game_info;
    this->setPixmap(*infoImg);
    this->show();
    QTimer::singleShot(INFO_TIME,this,SLOT(playersChoice()));
}

void visual::playersChoice()
{
    gameState = game_choice;
    this->setPixmap(*playersImg);
    this->show();
    bOne->show();
    bTwo->show();
}






void visual::keyIn1(QString k)
{
    if(k == "send")
    {
        if(name1.size()>=NAME1_MIN_LENGTH)
            showRules1();
        return;
    }
    else if(k=="back")
    {
        if(name1.size()>0)
            name1 = name1.remove(name1.size()-1,1);
    }
    else
    {
        if(name1.size()<NAME1_MAX_LENGTH)
            name1.append(k);
    }
    updTxt(name1P,name1);
}

void visual::addKey(std::vector<key> *keyMap,int x1,int y1,int x2,int y2,QString txt)
{
    key b;
    b.x1 = x1;     b.y1 = y1;     b.x2 = x2;     b.y2 = y2;    b.txt = txt;    keyMap->push_back(b);
}

void visual::initKeyboards()
{
    addKey(&keyMap1,227,467,332,575,"q");
    addKey(&keyMap1,361,467,467,575,"w");
    addKey(&keyMap1,499,467,600,575,"e");
    addKey(&keyMap1,633,467,738,575,"r");
    addKey(&keyMap1,768,467,875,575,"t");
    addKey(&keyMap1,905,467,1012,575,"y");
    addKey(&keyMap1,1038,467,1147,575,"u");
    addKey(&keyMap1,1174,467,1282,575,"i");
    addKey(&keyMap1,1311,467,1415,575,"o");
    addKey(&keyMap1,1445,467,1552,575,"p");
    addKey(&keyMap1,1581,467,1686,575,"back");

    addKey(&keyMap1,277,597,382,703,"a");
    addKey(&keyMap1,408,597,516,703,"s");
    addKey(&keyMap1,544,597,652,703,"d");
    addKey(&keyMap1,680,597,789,703,"f");
    addKey(&keyMap1,815,597,922,703,"g");
    addKey(&keyMap1,951,597,1059,703,"h");
    addKey(&keyMap1,1083,597,1191,703,"j");
    addKey(&keyMap1,1220,597,1327,703,"k");
    addKey(&keyMap1,1357,597,1464,703,"l");

    addKey(&keyMap1,361,720,468,831,"z");
    addKey(&keyMap1,495,720,603,831,"x");
    addKey(&keyMap1,628,720,735,831,"c");
    addKey(&keyMap1,761,720,870,831,"v");

    addKey(&keyMap1,894,720,1004,831,"b");
    addKey(&keyMap1,1029,720,1136,831,"n");
    addKey(&keyMap1,1165,720,1269,831,"m");
    addKey(&keyMap1,1298,720,1404,831,"@");
    addKey(&keyMap1,1432,720,1538,831,".");

    addKey(&keyMap1,628,847,1286,958," ");
    addKey(&keyMap1,1311,847,1421,958,"_");
    addKey(&keyMap1,1444,847,1688,958,"send");
}

void visual::startKeyboard(int playersCount)
{

    bOne->hide();
    bTwo->hide();


    if(playersCount<1) playersCount = 1;
    else if (playersCount>2) playersCount = 2;


    if(playersCount == 1)
    {
        gameState = game_keyboard1;
        this->setPixmap(*keyboardImg1);
        name1 = "";
        updTxt(name1P,name1);
        this->show();

    }
    else
    {

        this->showRules2();

    }




}

void visual::updTxt(QLabel *lbl,QString txt)
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

    lbl->show();
}



void visual::showRules1()
{
    name1P->hide();
    this->setPixmap(*rulesImg);
    gameState = game_rules;
    QTimer::singleShot(1000*TIMETOLAUNCH,this,SLOT(startCountDown1P()));
    count = 3;
}

void visual::showRules2()
{

    this->setPixmap(*rulesImg);
    gameState = game_rules;
    QTimer::singleShot(1000*TIMETOLAUNCH,this,SLOT(startCountDown2P()));
    count = 3;
}



void visual::startCountDown1P()
{
    if(count == 3)
        this->setPixmap(*cdImg3);
    else if(count == 2)
        this->setPixmap(*cdImg2);
    else if(count == 1)
        this->setPixmap(*cdImg1);
    else
    {
        QTimer::singleShot(1000,this,SLOT(launchGame1()));
        return;
    }
    gameState = countdown;
    count --;
    QTimer::singleShot(1000,this,SLOT(startCountDown1P()));
}



void visual::startCountDown2P()
{
    if(count == 3)
        this->setPixmap(*cdImg33);
    else if(count == 2)
        this->setPixmap(*cdImg22);
    else if(count == 1)
        this->setPixmap(*cdImg11);
    else
    {
        QTimer::singleShot(1000,this,SLOT(launchGame2()));
        return;
    }
    gameState = countdown;
    count --;
    QTimer::singleShot(1000,this,SLOT(startCountDown2P()));
}






void visual::launchGame1()
{

    emit startGame1(name1);
}


void visual::launchGame2()
{

    emit startGame2();
}


visual::~visual()
{


}


