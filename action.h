#ifndef ACTION_H
#define ACTION_H


class Action
{
public:
    Action();
    ~Action();

    virtual void Do() = 0;
    virtual void Undo() = 0;
};

#endif // ACTION_H
