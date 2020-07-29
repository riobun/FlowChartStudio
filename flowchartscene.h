#ifndef FLOWCHARTSCENE_H
#define FLOWCHARTSCENE_H

#include <QGraphicsScene>
#include "rectangle.h"


class FlowChartScene : public QGraphicsScene
{
public:
    FlowChartScene();

    static void pasteElements();
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
