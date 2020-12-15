#ifndef CHECKER_H
#define CHECKER_H

#include <QVector>
#include <QString>

class MainWindow;
class Scene;
class Graph;
class Node;
class Arrow;

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
    static bool initialize();
    static QString getNodeString(const Node* node);
    static QString getArrowString(const Arrow* arrow);
    static void addWarningMessage(const QString& message);
    static void addErrorMessage(const QString& message);
    static void checkNodes();
    static void checkNodeEnglish(const Node* node);
    static void checkRootNode(const Node* node);
    static void checkRectangle(const Node* node);
    static void checkDiamond(const Node* node);
    static void checkArrows();
    static void checkArrowText(const Arrow* arrow);
    static void showMessages();
};

#endif // CHECKER_H
