#ifndef GRAPHELEMENT_H
#define GRAPHELEMENT_H
#include "arrow.h"

//class GraphElement
//{
//public:
//    GraphElement();
//};
int k=0;
class GraphElement //图形元素
{
      public:
          GraphElement();
          ~GraphElement();
          GraphElement* father;
          int Id;//单个文件内唯一,文件内可能存在若干子图，但ID不同
//		  Text& content; 文本内容
          void setId();


};
#endif // GRAPHELEMENT_H
