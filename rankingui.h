#ifndef rankingUI_H
#define rankingUI_H


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

class  MainWindow;



class rankingUI:public QLabel
{
    Q_OBJECT

public:
    rankingUI(QWidget *parent = 0);
    ~rankingUI();
    void mousePressEvent( QMouseEvent* ev );
    void start(int score, QString playerName);
    int updateHighScores(int score, QString playerName);

private:
    MainWindow *mw;
    QPixmap *rankingImg,*nameImg;
    QFont font;
    void loadRanking(int rank, QString name);
    std::vector<QLabel*>namesLbl;

    void updTxt(QLabel *lbl, QString txt, bool frame);






};








#endif // SPLASH_H
