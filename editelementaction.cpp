#include "editelementaction.h"
#include "text.h"
#include "node.h"
#include <QPointF>
#include "mainwindow.h"

EditElementAction::EditElementAction(void* element, ElementShape shape, ElementProperty property, void* from, void* to)
    : shape(shape), property(property), from(from), to(to), element(element) {}

EditElementAction::~EditElementAction()
{
    if (!from) return;
    if (property == ElementProperty::Font)
    {
        delete (QFont*)from;
        delete (QFont*)to;
    }
    else if (property == ElementProperty::Size)
    {
        delete (QSizeF*)from;
        delete (QSizeF*)to;
    }
    else if (property == ElementProperty::String)
    {
        delete (QString*)from;
        delete (QString*)to;
    }
    else if (property == ElementProperty::Location)
    {
        delete (QPointF*)from;
        delete (QPointF*)to;
    }
    else if (property == ElementProperty::FontColor ||
             property == ElementProperty::FrameColor ||
             property == ElementProperty::BackgroundColor)
    {
        delete (QColor*)from;
        delete (QColor*)to;
    }
    else if (property == ElementProperty::Visibility)
    {
        delete (bool*)from;
        delete (bool*)to;
    }
}

void EditElementAction::Do()
{
    if(shape == ElementShape::Rectangle || shape==ElementShape::Diamond)
      {
          auto node = static_cast<Node*>(element);

           if(property == ElementProperty::Location)
           {
               auto toPoint =static_cast<QPointF*>(to);
               node->SetLocation(*toPoint);
           }
           else if (property == ElementProperty::Size)
           {
               auto toSize=static_cast<QSizeF*>(to);
               node->SetWidth(toSize->rwidth());
               node->SetHeight(toSize->rheight());
           }
           else if (property == ElementProperty:: BackgroundColor)
           {
               auto toBackgroundColor = static_cast<QColor*>(to);
               node->SetBackgroundColor(*toBackgroundColor);
           }
           else if (property == ElementProperty:: FrameColor)
           {
               auto toFrameColor = static_cast<QColor*>(to);
               node->SetFrameColor(*toFrameColor);
           }
      }
      else if(shape==  ElementShape::Text)
          {
           auto text = static_cast<Text*>(element);

          if(property == ElementProperty::Location)
          {
              auto toPoint =static_cast<QPointF*>(to);
              text->move_text(*toPoint);
          }
          else if (property == ElementProperty::Size)
          {
              auto toSize=static_cast<QSizeF*>(to);
              //text->resize_text(toSize->rwidth(),toSize->rheight());

          }
          else if (property == ElementProperty:: FontColor)
          {
              auto toFontColor = static_cast<QColor*>(to);
              text->reset_color(*toFontColor);
          }
          else if (property == ElementProperty:: Font)
          {
              auto toFont = static_cast<QFont*>(to);
              text->reset_font(*toFont);
          }

          }
}

void EditElementAction::Undo()
{
    EditElementAction(element, shape, property, nullptr, from).Do();
}
