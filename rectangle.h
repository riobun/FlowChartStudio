#ifndef RECTANGLE_H
#define RECTANGLE_H
#include"rectangleitem.h"
#include"node.h"
class Rectangle:public Node
{
public:
    Rectangle();
    Rectangle(QPointF lc,double wd,double h);
    virtual void Paint(QGraphicsScene* qgs) override;
    virtual void Remove(QGraphicsScene *qgs) override;
    virtual void SetVisibility(bool vis) override;
    virtual void SetLocation(const QPointF &qp) override;
    virtual void SetFrameColor(const QColor &qc) override;
    virtual void SetBackgroundColor(const QColor &qc) override;
    virtual void SetWidth(double wd) override;
    virtual void SetHeight(double h) override;
    virtual void BindToText(QGraphicsScene* qgs) override;
    virtual int GetType() override;
    ~Rectangle();
};

#endif // RECTANGLE_H
