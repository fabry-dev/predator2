#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    vs->start();

    gm = new game(this);



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
    gm->start(1,playerName);

}





MainWindow::~MainWindow()
{
    delete ui;



}
