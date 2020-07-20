#ifndef RECTANGLE_H
#define RECTANGLE_H
#include"QGraphicsItem"

class Rectangle
{
public:
    Rectangle();
private:
    QGraphicsRectItem* shape=new QGraphicsRectItem();
};

#endif // RECTANGLE_H
