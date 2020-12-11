#ifndef CHECKER_H
#define CHECKER_H

#include <QVector>
#include <QMap>
#include <QString>

class MainWindow;
class Scene;
class Graph;
class Node;

namespace Ui
{
    class MainWindow;
}

class Checker
{
public:
    static void check();

private:
    static QVector<QString> messages;

    static MainWindow* window;
    static Ui::MainWindow* ui;
    static Scene* scene;
    static Graph* graph;

private:
    static void initialize();
    static void checkNodes();
    static void checkNodesEnglish(const QMap<int, Node*>& nodes);
    static void showMessages();
};

#endif // CHECKER_H
