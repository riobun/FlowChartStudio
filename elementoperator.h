#ifndef ELEMENTOPERATOR_H
#define ELEMENTOPERATOR_H

#include <QObject>

class MainWindow;

class ElementOperator : public QObject
{
    Q_OBJECT

public:
    ElementOperator(MainWindow* parent);

    MainWindow* window() const;
};

#endif // ELEMENTOPERATOR_H
