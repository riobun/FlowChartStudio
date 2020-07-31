#ifndef FLOWCHARTSCENE_H
#define FLOWCHARTSCENE_H

#include <QGraphicsScene>
#include "rectangle.h"
#include "graph.h"


class FlowChartScene : public QGraphicsScene
{
public:
    FlowChartScene();
    ~FlowChartScene();

    static void pasteElements(QGraphicsSceneContextMenuEvent *event = nullptr);
    Graph* graph = new Graph;
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
private:
    Rectangle* rect=nullptr;
    QPointF selectLeftTop;
    bool isCtrlDown;
    QPointF keyDownPosition;
    QGraphicsLineItem* line = nullptr;
    QPointF fromLinePosition;
    Node* lineFrom;
};

#endif // FLOWCHARTSCENE_H
