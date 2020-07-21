#include "action.h"
#include "mainwindow.h"


Action::Action(bool isAdded, QObject *parent) : QObject(parent)
{
    if (isAdded)
    {
        auto window = MainWindow::instance();
        window->Doing(this);
    }
}
