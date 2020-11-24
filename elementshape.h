#ifndef SHAPE_H
#define SHAPE_H

#include <QString>

enum class ElementShape
{
    Unknown,
    Rectangle,
    Diamond,
    Arrow,
    SubGraph,
    Text,
    Input,
    Output,
    ArrowNode,
    InnerInput,
    InnerOutput,
    RootNode,
};

inline bool isNode(ElementShape shape)
{
    return shape == ElementShape::Input || shape == ElementShape::Output ||
            shape == ElementShape::Diamond || shape == ElementShape::SubGraph ||
            shape == ElementShape::Rectangle || shape == ElementShape::InnerInput ||
            shape == ElementShape::InnerOutput || shape == ElementShape::ArrowNode ||
            shape == ElementShape::RootNode;
}

inline const char* getShapeString(ElementShape shape)
{
    switch (shape)
    {
    case ElementShape::Text: return "text";
    case ElementShape::Arrow: return "arrow";
    case ElementShape::Input: return "input";
    case ElementShape::Output: return "output";
    case ElementShape::Diamond: return "diamond";
    case ElementShape::Unknown: return "unknown";
    case ElementShape::SubGraph: return "subgraph";
    case ElementShape::ArrowNode: return "arrowNode";
    case ElementShape::Rectangle: return "rectangle";
    case ElementShape::InnerInput: return "innerInput";
    case ElementShape::InnerOutput: return "innerOutput";
    case ElementShape::RootNode: return "rootNode";
    }
}

inline ElementShape parseShape(const QString& str)
{
    if (str == "rectangle") return ElementShape::Rectangle;
    else if (str == "diamond") return ElementShape::Diamond;
    else if (str == "arrow") return ElementShape::Arrow;
    else if (str == "subgraph") return ElementShape::SubGraph;
    else if (str == "text") return ElementShape::Text;
    else if (str == "input") return ElementShape::Input;
    else if (str == "output") return ElementShape::Output;
    else if (str == "innerInput") return ElementShape::InnerInput;
    else if (str == "innerOutput") return ElementShape::InnerOutput;
    else if (str == "arrowNode") return ElementShape::ArrowNode;
    else if (str == "rootNode") return ElementShape::RootNode;
    else return ElementShape::Unknown;
}

#endif // SHAPE_H
