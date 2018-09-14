#include "rankingui.h"
#include "qdebug.h"
#include "qtimer.h"
#include "mainwindow.h"


#define NUMSCORES 10
#define NAMEW 800
#define NAMEH 120
#define MINY 380

#define borderX 10

#define XSPACING 100

#define FONTNAME "Futura.ttc"


rankingUI::rankingUI(QWidget *parent):QLabel(parent)
{
    mw = (MainWindow*)(this->parent());

    this->hide();
    this->resize(1920,1080);



    int id = QFontDatabase::addApplicationFont(mw->PATH+FONTNAME);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(family,50);





    rankingImg = new QPixmap(mw->PATH+"scoreboardBG.png");




    this->setPixmap(*rankingImg);

    for (int i =0;i<NUMSCORES;i++)
    {
        QLabel *lbl = new QLabel(this);

        int x = (width()-2*NAMEW-XSPACING)/2+(i/(NUMSCORES/2))*(NAMEW+XSPACING);
        lbl->move(x,MINY+(NAMEH+10)*(i%(NUMSCORES/2)));
        lbl->resize(NAMEW,NAMEH);
        lbl->setFont(font);
        lbl->setAlignment(Qt::AlignLeft);
        //lbl->setStyleSheet("QLabel { color : white;border: 1px solid black; }");
        lbl->setStyleSheet("QLabel { color : white;}");
        lbl->hide();
        namesLbl.push_back(lbl);
    }




}


void rankingUI::start(int score, QString playerName)
{
    for(auto l:namesLbl)
        l->hide();

    int nurank = updateHighScores(score,playerName);
    loadRanking(nurank,playerName);

    this->show();


}




int rankingUI::updateHighScores(int score, QString playerName)
{
    std::vector<int> scores;
    std::vector<QString> names;


    QFile file(mw->PATH+"highscores.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"no high scores file yet";

    }

    QTextStream in(&file);

    QString  line;
    QStringList fields;


    while(!in.atEnd()) {
        line = in.readLine();
        fields = line.split(",");
        names.push_back(fields[0]);
        scores.push_back(fields[1].toInt());


    }

    file.close();

    int pos = scores.size();

    for(int i =0;i<scores.size();i++)
    {
        if(score>scores[i])
        {

            pos = i;
            break;
        }
    }

    scores.insert(scores.begin()+pos, score);
    names.insert(names.begin()+pos, playerName);


    QFile file2(mw->PATH+"highscores.txt");
    if(!file2.open(QIODevice::Append)) {
        qDebug()<<"cannot open file to write";
        return 0;
    }
    file2.resize(0);
    QTextStream out(&file2);


    for(int i =0;i<scores.size();i++)
    {
        out << names[i]<<","<<scores[i]<<"\n";
    }

    file2.close();




    return pos;
}





void rankingUI::mousePressEvent(QMouseEvent *ev)
{
    qDebug()<<ev->pos();
}


void rankingUI::loadRanking(int rank,QString name)
{

    std::vector<int> scores;
    std::vector<QString> names;


    QFile file(mw->PATH+"highscores.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"no high scores file yet";

    }

    QTextStream in(&file);

    QString  line;
    QStringList fields;


    for(int i = 0;i<NUMSCORES;i++) {
        if(in.atEnd())
            break;
        line = in.readLine();
        fields = line.split(",");
        names.push_back(fields[0]);
        scores.push_back(fields[1].toInt());
    }


    for(int j = 0;j<scores.size();j++)
    {
        updTxt(namesLbl[j],QString::number(j+1)+". "+names[j],j==rank);
        namesLbl[j]->show();
        namesLbl[j]->raise();
    }

    int j = scores.size()-1;

    if(rank>j)
        updTxt(namesLbl[j],QString::number(rank+1)+". "+name,true);


    file.close();
}




void rankingUI::updTxt(QLabel *lbl,QString txt,bool frame)
{
    QFontMetrics metrics(font);
    QSize size = metrics.size(0, txt); //Get size of text


    QPixmap px(100,100);
    px.fill(Qt::transparent);
    if (frame)
        px.load(mw->PATH+"playerScore.png");

    px = px.scaled(lbl->width(),lbl->height());
    float factorw = (lbl->width()-2*borderX) / (float)size.width(); //Get the width factor
    float factorh = (lbl->height()) / (float)size.height(); //Get the height factor
    float factor = qMin(factorw, factorh); //To fit contents in the screen select as factor
    //the minimum factor between width and height
    //font.setPointSizeF(110); //Set font size
    lbl->setFont(font);
    //lbl->setText(txt);


    QPainter painter( &px );
    painter.setFont( font );
    painter.setPen(Qt::white);

    painter.drawText(QRectF(35,15,lbl->width()-70,lbl->height()), Qt::AlignLeft, txt);


    lbl->setPixmap(px);

}






rankingUI::~rankingUI()
{


}


