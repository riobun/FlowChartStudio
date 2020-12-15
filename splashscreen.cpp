#include "splashscreen.h"
#include <QApplication>
#include "mainwindow.h"

SplashScreen::SplashScreen()
{
}

void SplashScreen::showScreen(QApplication& app)
{
    QPixmap pixmap(":/images/line_planes.jpg");
    setPixmap(pixmap);
    show();
    while (!hasClicked) app.processEvents();
    MainWindow::instance()->show();
}

void SplashScreen::mousePressEvent(QMouseEvent* event)
{
    hasClicked = true;
}
