#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    if (false)
    {
        QCursor cursor(Qt::BlankCursor);
        QApplication::setOverrideCursor(cursor);
        QApplication::changeOverrideCursor(cursor);
    }


    setWindowState(Qt::WindowFullScreen);

    vs = new visual(this);
    connect(vs,SIGNAL(startGame1(QString)),this,SLOT(startGame1(QString)));
    vs->start();

    gm = new game(this);


 //test

}



void MainWindow::startGame1(QString playerName)
{
    qDebug()<<"player "<<playerName<<" starts game 1";
    vs->hide();
    gm->start(1,playerName);

}











MainWindow::~MainWindow()
{
    delete ui;



}
