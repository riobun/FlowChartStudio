#include "action.h"
#include "mainwindow.h"


Action::Action(QObject *parent) : QObject(parent)
{
    auto window = MainWindow::instance();
    window->Doing(this);
}
