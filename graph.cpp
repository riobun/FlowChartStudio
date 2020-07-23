#include "graph.h"

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
