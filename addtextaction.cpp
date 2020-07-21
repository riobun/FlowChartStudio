#include "addtextaction.h"
#include "mainwindow.h"
#include "deletetextaction.h"

AddTextAction::AddTextAction(QPointF point, QString string, QFont font, QColor color, bool isAdded) :
    Action(isAdded), point(point), string(string), font(font), color(color)
{

}

void AddTextAction::Do()
{
    auto scene = MainWindow::instance()->scene();
    text = new Text(point.toPoint(), 100.0, 100.0);
    text->build_text(scene, QColor(), QFont());
}

void AddTextAction::Undo()
{
    DeleteTextAction(text, false).Do();
}
