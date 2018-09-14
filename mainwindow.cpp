#include "mainwindow.h"
#include "ui_mainwindow.h"

#define rankingTime 10

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    getParams(QCoreApplication::arguments());


    if (HIDE_CURSOR)
    {
        QCursor cursor(Qt::BlankCursor);
        QApplication::setOverrideCursor(cursor);
        QApplication::changeOverrideCursor(cursor);
    }


    setWindowState(Qt::WindowFullScreen);

    vs = new visual(this);
    connect(vs,SIGNAL(startGame1(QString)),this,SLOT(startGame1(QString)));
    connect(vs,SIGNAL(startGame2()),this,SLOT(startGame2()));
    gm1 = new game1P(this);
    connect(gm1,SIGNAL(hasWon1P(int,QString)),this,SLOT(winGame1(int,QString)));

    rk = new rankingUI(this);


    //


    vs->start();



}


void MainWindow::getParams(QStringList params)
{
    if(params.size()>1)
        PATH = params[1];
    else
        PATH=PATH_DEFAULT;

    if(params.size()>2)
        HIDE_CURSOR = (params[2]=="true");
    else
        HIDE_CURSOR = false;

}

void MainWindow::startGame1(QString playerName)
{
    qDebug()<<"player "<<playerName<<" starts game 1";
    vs->hide();
    gm1->start(playerName);

}

void MainWindow::winGame1(int score,QString playerName)
{
    qDebug()<<"won game1: score="<<score<<" by "<<playerName;
    rk->start(score,playerName);
    QTimer::singleShot(1000*rankingTime,this,SLOT(reset()));
}


void MainWindow::reset()
{
gm1->hide();
rk->hide();
vs->start();


}



void MainWindow::startGame2()
{
    return;
    qDebug()<<"starts game 2";
    vs->hide();


}

MainWindow::~MainWindow()
{
    delete ui;



}

