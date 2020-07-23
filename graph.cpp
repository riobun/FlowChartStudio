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
