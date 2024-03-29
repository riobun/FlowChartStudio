#ifndef FLOWCHARTSCENE_H
#define FLOWCHARTSCENE_H

#include <QGraphicsScene>
#include <QList>

#include "rectangle.h"
#include "graph.h"
#include "action.h"

class Item;

class Scene : public QGraphicsScene
{
public:
    Scene(bool setId = true);
    ~Scene();

    static void pasteElements(QGraphicsSceneContextMenuEvent *event = nullptr);
    Graph* graph = new Graph();
    void clearSelect();
    QList<Action*> undoStack;
    QList<Action*> redoStack;
    int lastUndoSize;
    bool isChanged = false;
    QString file_path;
    Item* item = nullptr;
    QMap<QString, QString> branches;
    QMap<QString, QString> nodeDictionary;
    QMap<QString, QString> branchDictionary;

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
