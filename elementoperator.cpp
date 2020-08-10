#include "elementoperator.h"
#include "mainwindow.h"

ElementOperator::ElementOperator(MainWindow* parent) : QObject(parent)
{

}

MainWindow* ElementOperator::window() const
{
    return static_cast<MainWindow*>(parent());
}
