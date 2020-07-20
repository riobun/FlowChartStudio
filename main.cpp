#include "mainwindow.h"
#include <QApplication>
#include "rectangle.h"
#include "diamond.h"
#define DEBUG
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
#ifdef DEBUG
    Rectangle* r1=new Rectangle(QPointF(25,25),50,50);
    Rectangle* r2=new Rectangle(QPointF(0,0),50,50);
    r1->SetFrameColor(Qt::red);
    r1->Paint(w.scene());
    r2->Paint(w.scene());
    r2->SetBackgroundColor(Qt::blue);
    Diamond* d1=new Diamond(QPoint(100,100),100,50);
    d1->SetBackgroundColor(Qt::green);
    d1->Paint(w.scene());
    d1->SetFrameColor(Qt::yellow);
#endif
    return a.exec();
}
