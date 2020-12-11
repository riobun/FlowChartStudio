#include "checker.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

QVector<QString> Checker::messages;
MainWindow* Checker::window;
Ui::MainWindow* Checker::ui;
Scene* Checker::scene;
Graph* Checker::graph;

void Checker::check()
{
    initialize();
    checkNodes();
    showMessages();
}

void Checker::initialize()
{
    messages.clear();
    window = MainWindow::instance();
    ui = window->getUi();
    scene = window->scene();
    graph = scene->graph;
}

void Checker::checkNodes()
{
    auto nodes = graph->getNodes();
    checkNodesEnglish(nodes);
}

void Checker::checkNodesEnglish(const QMap<int, Node*>& nodes)
{
    auto& nodeDictionary = scene->nodeDictionary;
    foreach (auto node, nodes)
    {
        auto nodeId = node->getNodeId();
        auto text = node->content;
        if (text != nullptr)
        {
            auto content = text->get_text_content();
            if (content != "")
            {
                if (!nodeDictionary.contains(content))
                {
                    auto message = QString("警告：ID为%1的节点的内容没有对应的英文。").arg(nodeId);
                    messages.append(message);
                }
                continue;
            }
        }
        auto message = QString("警告：ID为%1的节点没有内容。").arg(nodeId);
        messages.append(message);
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
