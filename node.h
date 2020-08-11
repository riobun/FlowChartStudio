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
class Graph;
class Node:public GraphElement
{
public:
    Node();
    Node(QPointF lc,double wd,double h);
    virtual void SetVisibility(bool vis);
    virtual void Paint(QGraphicsScene* qgs);//在创建Node实例之后需要调用一次Paint()才会显示
    double GetWidth();
    virtual void SetWidth(double wd);
    double GetHeight();
    virtual void SetHeight(double h);
    QPointF GetLocation();
    virtual void SetLocation(const QPointF& qp);
    QColor GetBackgroundColor();
    virtual void SetBackgroundColor(const QColor& qc);
    QColor GetFrameColor();
    virtual void SetFrameColor(const QColor& qc);
    void ConnectAsSource(Arrow* ar);
    void ConnectAsDestination(Arrow* ar);
    void DisconnectAsSource(Arrow* ar);
    void DisconnectAsDestination(Arrow* ar);
    virtual void Remove(QGraphicsScene* qgs);
    virtual void SetShape()=0;
    virtual void BindToText(QGraphicsScene* qgs) override;
    virtual ~Node();
    QVector<Arrow*> getArrows();
    QVector<Arrow*> getSourceArrows();
    virtual void ChangeZValue(bool isSelected);

    NodeItem* getNodeItem() const { return shape; }
    virtual int GetType()=0;
    QGraphicsScene* GetRelatedQGS() {return relatedQGS;}
protected:
    QPointF location=QPointF(0.0,0.0);//表示图形中心位置
    double width,height;
    QColor backgroundColor=Qt::white,frameColor=Qt::black;
    NodeItem* shape=new NodeItem(this);
    bool isRemoved=false;
    Graph* fatherGraph=nullptr;
    QGraphicsScene* relatedQGS=nullptr;
private:
    QMap<int,Arrow*> sourceArrows;
    QMap<int,Arrow*> destinationArrows;

};

#endif // NODE_H
