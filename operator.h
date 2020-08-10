#ifndef ELEMENTOPERATOR_H
#define ELEMENTOPERATOR_H

#include <QObject>

#include "elementshape.h"

class MainWindow;

class Operator : public QObject
{
    Q_OBJECT

public:
    Operator(MainWindow* parent);

    MainWindow* getWindow() const;

private:
    void connectAddButtons();

private:
    ElementShape _nextAddedShape;
};

#endif // ELEMENTOPERATOR_H
