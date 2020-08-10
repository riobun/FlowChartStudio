#include "operator.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

Operator::Operator(MainWindow* parent) : QObject(parent)
{
    connectAddButtons();
}

MainWindow* Operator::getWindow() const
{
    return static_cast<MainWindow*>(parent());
}

void Operator::connectAddButtons()
{
    auto window = getWindow();
    auto ui = window->getUi();
    auto clicked = &QAbstractButton::clicked;
    auto addRectangleButton = ui->addRectangleButton;
    connect(addRectangleButton, clicked, [this]()
    {
        _nextAddedShape = ElementShape::Rectangle;
    });
    auto addDiamondButton = ui->addDiamondButton;
    connect(addDiamondButton, clicked, [this]()
    {
        _nextAddedShape = ElementShape::Diamond;
    });
    auto addArrowButton = ui->addArrowButton;
    connect(addArrowButton, clicked, [this]()
    {
        _nextAddedShape = ElementShape::Arrow;
    });
    auto addTextButton = ui->addTextButton;
    connect(addTextButton, clicked, [this]()
    {
        _nextAddedShape = ElementShape::Text;
    });
    auto addInputButton = ui->addInputButton;
    connect(addInputButton, clicked, [this]()
    {
        _nextAddedShape = ElementShape::Input;
    });
    auto addOutputButton = ui->addOutputButton;
    connect(addOutputButton, clicked, [this]()
    {
        _nextAddedShape = ElementShape::Output;
    });
    auto addInnerInputButton = ui->addInnerInputButton;
    connect(addInnerInputButton, clicked, [this]()
    {
        _nextAddedShape = ElementShape::InnerInput;
    });
    auto addInnerOutputButton = ui->addInnerOutputButton;
    connect(addInnerOutputButton, clicked, [this]()
    {
        _nextAddedShape = ElementShape::InnerOutput;
    });
}
