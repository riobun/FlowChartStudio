#include "changetextaction.h"
#include "mainwindow.h"

ChangeTextAction::ChangeTextAction(bool isCreated, QPointF point, QString string, QFont font,
                                   QColor color, Text* text, bool isAdded) :
    Action(isAdded), point(point), string(string), font(font), isCreated(isCreated), color(color), text(text)
{

}

void ChangeTextAction::Do()
{
    auto scene = MainWindow::instance()->scene();
    if (isCreated)
    {
        text = new Text(point.toPoint(), 100.0, 100.0);
        text->build_text(scene, QColor(), QFont());
    }
    else
    {
        text->delete_text(scene);
    }
}

void ChangeTextAction::Undo()
{
    ChangeTextAction(!isCreated, point, string, font, color, text, false).Do();
}
