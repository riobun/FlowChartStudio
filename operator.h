#ifndef ELEMENTOPERATOR_H
#define ELEMENTOPERATOR_H

#include <QObject>

class MainWindow;

class Operator : public QObject
{
    Q_OBJECT

public:
    Operator(MainWindow* parent);

    MainWindow* window() const;
};

#endif // ELEMENTOPERATOR_H
