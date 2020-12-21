#include "splashscreen.h"
#include <QApplication>
#include <QScreen>
#include "mainwindow.h"

SplashScreen::SplashScreen()
{
}

void SplashScreen::showScreen(QApplication& app)
{
    QPixmap pixmap(":/images/line_planes_new.jpg");
    auto screenSize = QGuiApplication::screens()[0]->size();
    QPixmap newPixmap = pixmap.scaled(screenSize);
    setPixmap(newPixmap);
    setFont(QFont("微软雅黑", 50));
    setStyleSheet("color: red;");
    showMessage("自主决策系统图形化配置软件\n点击继续", Qt::AlignCenter | Qt::AlignHCenter, Qt::red);
    show();
    while (!hasClicked) app.processEvents();
    MainWindow::instance()->show();
}

void SplashScreen::mousePressEvent(QMouseEvent* event)
{
    hasClicked = true;
}
