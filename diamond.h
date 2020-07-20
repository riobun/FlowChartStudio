#ifndef DIAMOND_H
#define DIAMOND_H
#include"QGraphicsItem"
#include"node.h"
class Diamond:public Node
{
public:
    Diamond();
    Diamond(QPointF lc,double wd,double h);
    virtual void Paint(QGraphicsScene* qgs) override;
    virtual void Remove(QGraphicsScene *qgs) override;
    virtual void SetVisibility(bool vis) override;
    virtual void SetLocation(const QPointF &qp) override;
    virtual void SetFrameColor(const QColor &qc) override;
    virtual void SetBackgroundColor(const QColor &qc) override;
    virtual void SetWidth(double wd) override;
    virtual void SetHeight(double h) override;
    ~Diamond();
private:
    QGraphicsPolygonItem* shape=new QGraphicsPolygonItem();
};

#endif // DIAMOND_H
