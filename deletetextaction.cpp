#include "deletetextaction.h"
#include "mainwindow.h"
#include "addtextaction.h"

DeleteTextAction::DeleteTextAction(Text* text, bool isAdded) : Action(isAdded), text(text)
{
    point = text->get_text_location();
    string = text->get_text_content();
    font = text->get_text_fond();
    color = text->get_text_color();
}

void DeleteTextAction::Do()
{
    auto scene = MainWindow::instance()->scene();
    text->delete_text(scene);
}

void DeleteTextAction::Undo()
{
    AddTextAction(point, string, font, color, false).Do();
}
