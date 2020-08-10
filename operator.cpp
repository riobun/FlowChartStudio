#include "operator.h"
#include "mainwindow.h"

Operator::Operator(MainWindow* parent) : QObject(parent)
{

}

MainWindow* Operator::window() const
{
    return static_cast<MainWindow*>(parent());
}
