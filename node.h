#ifndef NODE_H
#define NODE_H
#include"QPoint"
#include"QColor"
#include"QMap"
#include"qpen.h"
#include"graphelement.h"
#include"QGraphicsScene"
#include"nodeitem.h"
class Arrow;
class Node:public GraphElement
{
public:
    Node();
    Node(QPointF lc,double wd,double h);
    virtual void SetVisibility(bool vis)=0;
    virtual void Paint(QGraphicsScene* qgs)=0;//在创建Node实例之后需要调用一次Paint()才会显示
    double GetWidth();
    virtual void SetWidth(double wd)=0;
    double GetHeight();
    virtual void SetHeight(double h)=0;
    QPointF GetLocation();
    virtual void SetLocation(const QPointF& qp)=0;
    QColor GetBackgroundColor();
    virtual void SetBackgroundColor(const QColor& qc)=0;
    QColor GetFrameColor();
    virtual void SetFrameColor(const QColor& qc)=0;
    void ConnectAsSource(Arrow* ar);
    void ConnectAsDestination(Arrow* ar);
    void DisconnectAsSource(Arrow* ar);
    void DisconnectAsDestination(Arrow* ar);
    virtual void Remove(QGraphicsScene* qgs)=0;
    virtual ~Node();
    QVector<Arrow*> getArrows();


    NodeItem* getNodeItem() const { return shape; }
    virtual int GetType()=0;

protected:
    QPointF location=QPointF(0.0,0.0);//表示图形中心位置
    double width,height;
    QColor backgroundColor=Qt::white,frameColor=Qt::black;
    NodeItem* shape=new NodeItem(this);
private:
    QMap<int,Arrow*> sourceArrows;
    QMap<int,Arrow*> destinationArrows;
};

#endif // NODE_H
