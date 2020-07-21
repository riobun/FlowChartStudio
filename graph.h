#ifndef GRAPH_H
#define GRAPH_H

#include"node.h"
#include"text.h"


class Graph:public GraphElement
{
public:
    Graph();
private:
    bool isExpended;
    Node& subGraphNode;
    QMap<int, Node&> nodes;
    QMap<int, Arrow&> Arrows;
    QMap<int, Text&> texts;
    QMap<int, Graph&> subGraph;
};

#endif // GRAPH_H
