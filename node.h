#ifndef NODE_H
#define NODE_H
#include"QPoint"
#include"QColor"
#include"QMap"
#include"graphelement.h"
#include"arrow.h"

class Node:public GraphElement
{
public:
    Node()=default;
    Node(QPointF lc,double wd,double height);
    virtual void SetVisibility(bool vis);
    QPointF GetLocation();
    void SetLocation(const QPointF& qp);
    QColor GetBackgroundColor();
    QColor SetBackgroundColor(const QColor& qc);
    QColor GetFrameColor();
    QColor SetFrameColor(const QColor& qc);
    void ConnectAsSource(Arrow& ar);
    void ConnectAsDestination(Arrow& ar);
    void DisconnectAsSource(Arrow& ar);
    void DisconnectAsDestination(Arrow& ar);
    virtual void Remove();
private:
    QPointF location=QPointF(0.0,0.0);
    double width,height;
    QColor backgroundColor=Qt::white,freamColor=Qt::black;
    QMap<int,Arrow&> sourceArrows;
    QMap<int,Arrow&> destinationArrows;
};

#endif // NODE_H
