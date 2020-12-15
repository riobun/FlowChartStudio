#include "checker.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "arrow.h"
#include "arrownode.h"
#include "rootnode.h"

QVector<QString> Checker::messages;
MainWindow* Checker::window;
Ui::MainWindow* Checker::ui;
Scene* Checker::scene;
Graph* Checker::graph;

void Checker::check()
{
    if (!initialize()) return;
    checkNodes();
    checkArrows();
    showMessages();
}

bool Checker::initialize()
{
    messages.clear();
    window = MainWindow::instance();
    ui = window->getUi();
    scene = window->scene();
    if (scene == nullptr) return false;
    graph = scene->graph;
    return true;
}

QString Checker::getNodeString(const Node* node)
{
    auto idString = QString("0x%1").arg(QString::number(node->getNodeId(), 16));
    return QString("ID为%1的节点").arg(idString);
}

QString Checker::getArrowString(const Arrow* arrow)
{
    auto from = arrow->startItem()->GetNode();
    while (dynamic_cast<ArrowNode*>(from) != nullptr)
    {
        from = from->getSourceArrow()->startItem()->GetNode();
    }
    auto fromString = getNodeString(from);
    auto to = arrow->endItem()->GetNode();
    while (dynamic_cast<ArrowNode*>(to) != nullptr)
    {
        to = to->getDestinationArrow()->startItem()->GetNode();
    }
    auto toString = getNodeString(to);
    return QString("连接%1和%2的箭头").arg(fromString).arg(toString);
}

void Checker::addWarningMessage(const QString& message)
{
    auto finalMessage = QString("警告：%1").arg(message);
    messages.append(finalMessage);
}

void Checker::addErrorMessage(const QString& message)
{
    auto finalMessage = QString("错误：%1").arg(message);
    messages.append(finalMessage);
}

void Checker::checkNodes()
{
    auto& nodes = graph->getNodes();
    Node* root = nullptr;
    bool hasMultiRoot = false;
    foreach (auto node, nodes)
    {
        checkNodeEnglish(node);
        if (dynamic_cast<RootNode*>(node) != nullptr)
        {
            if (root != nullptr)
            {
                if (hasMultiRoot) continue;
                addErrorMessage("不能有多个根节点。");
                hasMultiRoot = true;
            }
            checkRootNode(node);
            root = node;
        }
        else if (dynamic_cast<Rectangle*>(node) != nullptr) checkRectangle(node);
        else if (dynamic_cast<Diamond*>(node) != nullptr) checkDiamond(node);
    }
}

void Checker::checkNodeEnglish(const Node* node)
{
    auto text = node->content;
    if (text != nullptr)
    {
        auto content = text->get_text_content();
        if (content != "")
        {
            auto& nodeDictionary = scene->nodeDictionary;
            if (!nodeDictionary.contains(content))
            {
                auto idString = getNodeString(node);
                auto message = QString("%1的内容没有对应的英文。").arg(idString);
                addWarningMessage(message);
            }
        }
    }
}

void Checker::checkRootNode(const Node* node)
{
    if (node->getDestinationArrow() != nullptr)
    {
        auto nodeString = getNodeString(node);
        auto message = QString("%1不能有入口箭头。").arg(nodeString);
        addErrorMessage(message);
    }
    if (node->getSourceArrows().size() > 1)
    {
        auto nodeString = getNodeString(node);
        auto message = QString("%1不能有多个出口箭头。").arg(nodeString);
        addErrorMessage(message);
    }
}

void Checker::checkRectangle(const Node* node)
{
    if (node->getDestinationArrows().size() != 1)
    {
        auto nodeString = getNodeString(node);
        auto message = QString("%1必须有1个入口箭头。").arg(nodeString);
        addErrorMessage(message);
    }
    if (node->getSourceArrows().size() > 1)
    {
        auto nodeString = getNodeString(node);
        auto message = QString("%1不能有多个出口箭头。").arg(nodeString);
        addErrorMessage(message);
    }
}

void Checker::checkDiamond(const Node* node)
{
    if (node->getDestinationArrows().size() != 1)
    {
        auto nodeString = getNodeString(node);
        auto message = QString("%1必须有1个入口箭头。").arg(nodeString);
        addErrorMessage(message);
    }
    if (node->getSourceArrows().size() != 2)
    {
        auto nodeString = getNodeString(node);
        auto message = QString("%1必须有2个出口箭头。").arg(nodeString);
        addErrorMessage(message);
    }
}

void Checker::checkArrows()
{
    auto& arrows = graph->getArrows();
    foreach (auto arrow, arrows)
    {
        checkArrowText(arrow);
    }
}

void Checker::checkArrowText(const Arrow* arrow)
{
    auto text = arrow->content;
    if (text != nullptr)
    {
        auto content = text->get_text_content();
        if (content != "")
        {
            auto& dictionary = scene->branchDictionary;
            auto& branches = scene->branches;
            if (!dictionary.contains(content))
            {
                auto arrowString = getArrowString(arrow);
                auto message = QString("%1的内容没有对应的英文。").arg(arrowString);
                addWarningMessage(message);
            }
            else if (!branches.contains(dictionary[content]))
            {
                auto arrowString = getArrowString(arrow);
                auto message = QString("%1的内容没有对应的函数。").arg(arrowString);
                addWarningMessage(message);
            }
        }
    }
}

void Checker::showMessages()
{
    auto listWidget = ui->listWidget;
    listWidget->clear();
    if (messages.size() == 0)
    {
        listWidget->addItem("无问题。");
    }
    else
    {
        foreach (auto& message, messages)
        {
            listWidget->addItem(message);
        }
    }
}
