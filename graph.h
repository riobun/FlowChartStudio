#ifndef GRAPH_H
#define GRAPH_H

#include"node.h"
#include"text.h"


class Graph:public GraphElement
{
public:
    Graph(){}
    //调用下面这个函数来定义子图，传入要生成子图的节点们
    Graph(QVector<Node*>& v_Node, QVector<Text*>& v_Text, QVector<Graph*>& v_Graph);
    void resizeGraph(); //调整图形在屏幕上的布局
    void MoveSubGraph();//移动子图
    void FoldSubGraph();//折叠
    void unFoldSubGraph();  //展开
    void DeleteSubGraph();  //删除子图，当前子图下所有节点归为父节点

    void addNode(Node* node);
    void removeNode(Node* node);
    Node* searchNode(QPointF point);
    QVector<Node*> searchNodes(Node* node);
    void addText(Text* node);
    void removeText(Text* node);
    Text* searchText(QPointF point);
    QVector<Arrow*> searchArrows(Node* node);
    QVector<Text*> searchTexts(Node* node);
    void addArrow(Arrow* arrow);
    void removeArrow(Arrow* arrow);
    void clear();
    QMap<int, Node*>& getNodes() { return nodes; }
    QMap<int, Arrow*>& getArrows() { return arrows; }
    QVector<Text*>& getTexts() { return texts; }

    void BindToText(QGraphicsScene *qgs) override {}
    Node* node;
private:
    void SetVisibility(bool set);
    bool isExpended;
    Node* subGraphNode;
    QMap<int, Node*> nodes;
    QMap<int, Arrow*> arrows;
    QVector<Text*> texts;
    QMap<int, Graph*> subGraph;
};

#endif // GRAPH_H
