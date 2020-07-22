
#include <QMenu>

#include "textscene.h"
#include "changeelementaction.h"
#include "mainwindow.h"


void TextScence::contextMenuEvent(Text* text, QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    auto deleteAction = menu.addAction("删除");
    deleteAction->setShortcut(QKeySequence::Delete);
    auto selectedAction = menu.exec(event->screenPos());
    if (selectedAction == deleteAction)
    {
        auto action = new ChangeElementAction(text, ElementShape::Rectangle, false);
        action->Do();
    }
}

void TextScene::mousePressEvent( QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    if (!event->isAccepted()) {
        if (event->button() == Qt::LeftButton) {
            // 在 Scene 上添加一个自定义 item
            QPointF point = event->scenePos();
            Text t(point, 60, 40);
            t.build_text(QColor(), QFont());
            addItem(t.get_item());
        }
        else if (event->button() == Qt::RightButton) {
            // 检测光标下是否有 item
            QGraphicsItem* itemToRemove = NULL;
            foreach(QGraphicsItem * item, items(event->scenePos())) {
                if (item->type() == QGraphicsItem::UserType + 1) {
                    itemToRemove = item;
                    break;
                }
            }
            // 从 Scene 上移除 item
            if (itemToRemove != NULL)
                removeItem(itemToRemove);
        }
    }
}

void TextScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);

}
void TextScene::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Backspace) {
        // 移除所有选中的 items
        qDebug() << "selected items " << selectedItems().size();
        while (!selectedItems().isEmpty()) {
            removeItem(selectedItems().front());
        }
    }
    else {
        QGraphicsScene::keyPressEvent(event);
    }
}
© 202
