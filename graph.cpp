#include "graph.h"
#include "arrow.h"
#include "subgraphnode.h"
Graph::Graph(QVector<Node*>& v_Node, QVector<Text*>& v_Text, QVector<Graph*>& v_Graph){

}

void Graph::resizeGraph(){

}

void Graph::MoveSubGraph(){

}

void Graph::FoldSubGraph(){
    if (!isExpended)    //若未展开（折叠状态）则不进行折叠
            return;
        //以下遍历map
    foreach(auto node, nodes){
        node->SetVisibility(false);
    }
    foreach(auto arrow, arrows){
        //arrow->SetVisibility(false);
    }
    foreach(auto text, texts){
        text->hide();
    }
    foreach(auto sub, subGraph){
        sub->SetVisibility(false);
    }
    subGraphNode->SetVisibility(true);
    isExpended=false;
}

void Graph::unFoldSubGraph(){
    if (isExpended)    //若已展开则不进行展开
            return;
    //以下遍历map
    foreach(auto node, nodes){
        node->SetVisibility(true);
    }
    foreach(auto arrow, arrows){
        //arrow->SetVisibility(true);
    }
    foreach(auto text, texts){
        text->show();
    }
    foreach(auto sub, subGraph){
        sub->SetVisibility(true);
    }
    subGraphNode->SetVisibility(false);
    isExpended=true;
}

void Graph::DeleteSubGraph(){

}

void Graph::addNode(Node* node)
{
    nodes.insert(node->GetID(), node);
}


void Graph::addNode(Node* node, int index, ElementShape shape){
    node_info n;
    n.node_id=node->GetID();
    n.p_node=node;
    n.index=index;
    n.shape=shape;
    v_node_info.push_back(n);
}

QVector<QPair<Node*,ElementShape>> Graph::Nodes_ElementShape(int index){
    QVector<QPair<Node*,ElementShape>> v;
    foreach(auto n,v_node_info){
        if(n.index == index){
            v.push_back({n.p_node,n.shape});
        }
    }
    return v;
}


void Graph::removeNode(Node* node)
{
    nodes.remove(node->GetID());
}

Node* Graph::searchNode(QPointF point)
{
    foreach (auto node, nodes)
    {
        auto size = QPointF(node->GetWidth(), node->GetHeight());
        QPointF position = node->GetLocation();
        if (point.rx() >= position.rx() - size.rx() && point.ry() >= position.ry() - size.ry() &&
                point.rx() <= position.rx() + size.rx() && point.ry() <= position.ry() + size.ry())
        {
            return node;
        }
    }
    return nullptr;
}

QVector<Node*> Graph::searchNodes(Node* node)
{
    auto size = QPointF(node->GetWidth(), node->GetHeight());
    auto rect = QRectF(node->GetLocation() - size / 2, QSizeF(size.rx(), size.ry()));
    QVector<Node*> vec;
    foreach (auto node, nodes)
    {
        auto sSize = QPointF(node->GetWidth(), node->GetHeight());
        auto point = node->GetLocation() - sSize / 2;
        if (rect.contains(point))
        {
            vec.append(node);
            continue;
        }
        point = node->GetLocation() + QPointF(sSize.rx(), -sSize.ry());
        if (rect.contains(point))
        {
            vec.append(node);
            continue;
        }
        point = node->GetLocation() + QPointF(-sSize.rx(), sSize.ry());
        if (rect.contains(point))
        {
            vec.append(node);
            continue;
        }
        point = node->GetLocation() + sSize / 2;
        if (rect.contains(point))
        {
            vec.append(node);
            continue;
        }
    }
    return vec;
}
QVector<Arrow*> Graph::searchArrows(Node* node)
{

    QVector<Arrow*> vec;
    foreach (auto arrow, arrows)
    {
        if( node->getNodeItem()->contains(arrow->startItem()->pos())||
                node->getNodeItem()->contains(arrow->endItem()->pos())||
                  node->getNodeItem()->contains(
                    QPointF((arrow->endItem()->pos().x()+arrow->endItem()->pos().x())/2
                            ,(arrow->endItem()->pos().y()+arrow->endItem()->pos().y())/2)))
        {
                vec.append(arrow);
                continue;
    }


    }
    return vec;
}
void Graph::addText(Text* text)
{
    texts.append(text);
}

void Graph::removeText(Text* text)
{
    texts.removeAll(text);
}

Text* Graph::searchText(QPointF point)
{
    foreach (auto text, texts)
    {
        auto size = QPointF(text->textWidth(), 0);
        QPointF position = text->get_text_location();
        if (point.rx() >= position.rx() - size.rx() && point.ry() >= position.ry() - size.ry() &&
                point.rx() <= position.rx() + size.rx() && point.ry() <= position.ry() + size.ry())
        {
            return text;
        }
    }
    return nullptr;
}

QVector<Text*> Graph::searchTexts(Node* node)
{
    auto size = QPointF(node->GetWidth(), node->GetHeight());
    auto rect = QRectF(node->GetLocation() - size / 2, QSizeF(size.rx(), size.ry()));
    QVector<Text*> vec;
    foreach (auto text, texts)
    {
        auto sSize = QPointF(text->textWidth(), 0);
        auto point = text->get_text_location() - sSize / 2;
        if (rect.contains(point))
        {
            vec.append(text);
            continue;
        }
        point = text->get_text_location() + QPointF(sSize.rx(), -sSize.ry());
        if (rect.contains(point))
        {
            vec.append(text);
            continue;
        }
        point = text->get_text_location() + QPointF(-sSize.rx(), sSize.ry());
        if (rect.contains(point))
        {
            vec.append(text);
            continue;
        }
        point = text->get_text_location() + sSize / 2;
        if (rect.contains(point))
        {
            vec.append(text);
            continue;
        }
    }
    return vec;
}

void Graph::addArrow(Arrow* arrow)
{
    arrows[arrow->GetID()] = arrow;
}

void Graph::removeArrow(Arrow* arrow)
{
    arrows.remove(arrow->GetID());
}

void Graph::SetVisibility(bool set){

}

void Graph::clear()
{
    nodes.clear();
    texts.clear();
    arrows.clear();
}

void Graph::AddRelatedNode(SubgraphNode *sn)
{
    relatedNodes.insert(sn->GetID(),sn);
}

void Graph::RemoveRelatedNode(SubgraphNode *sn)
{
    relatedNodes.remove(sn->GetID());
}
