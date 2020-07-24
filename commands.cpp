#include "commands.h"


QList<Command*> Command::_undoStack;
QList<Command*> Command::_redoStack;

Command::Command()
{
    _undoStack.append(this);
}

Command::~Command()
{
    if (_undoStack.last() == this)
    {
        _undoStack.removeLast();
    }
}
