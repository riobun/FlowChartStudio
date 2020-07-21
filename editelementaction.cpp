#include "editelementaction.h"

EditElementAction::EditElementAction(void* element, ElementShape shape, ElementProperty property, void* from, void* to)
    : shape(shape), property(property), from(from), to(to), element(element) {}

void EditElementAction::Do()
{

}

void EditElementAction::Undo()
{
    EditElementAction(element, shape, property, to, from).Do();
}
