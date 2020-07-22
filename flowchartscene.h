#ifndef FLOWCHARTSCENE_H
#define FLOWCHARTSCENE_H

#include <QGraphicsScene>


class FlowChartScene : public QGraphicsScene
{
public:
    FlowChartScene();

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // FLOWCHARTSCENE_H
