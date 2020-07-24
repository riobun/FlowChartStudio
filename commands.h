#ifndef COMMANDS_H
#define COMMANDS_H

#include <QObject>
#include <QList>


class Command : public QObject
{
    Q_OBJECT

public:
    virtual void Do() = 0;
    virtual void Undo() = 0;

protected:
    Command();
    ~Command();

private:
    static QList<Command*> _undoStack;
    static QList<Command*> _redoStack;
};

class AddNodesCommand : public Command
{
    Q_OBJECT
};

#endif // COMMANDS_H
