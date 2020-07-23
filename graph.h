#ifndef GRAPH_H
#define GRAPH_H

#include"node.h"
#include"text.h"


class Graph:public GraphElement
{
public:
    Graph(){}
    void resizeGraph(){} //调整图形在屏幕上的布局
    void MoveSubGraph(){}//移动子图
    void FoldSubGraph(){}//折叠
    void unFoldSubGraph(){}  //展开
    void DeleteSubGraph(){}  //删除子图，当前子图下所有节点归为父节点
    void addNode(Node* node)
    {
        nodes.insert(node->GetID(), node);
    }
    Node* searchNode(QPointF point);
    QVector<Node*> searchNodes(Node* node);

    void BindToText(QGraphicsScene *qgs) override {}
private:
    bool isExpended;
    Node* subGraphNode;
    //Node& subGraphNode;
    QMap<int, Node*> nodes;
    QMap<int, Arrow*> Arrows;
    QMap<int, Text*> texts;
    QMap<int, Graph*> subGraph;
};

#endif // GRAPH_H
