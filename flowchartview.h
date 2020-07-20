#ifndef FLOWCHARTVIEW_H
#define FLOWCHARTVIEW_H

#include <QGraphicsView>


class FlowChartView : public QGraphicsView
{
    Q_OBJECT

public:
    FlowChartView(QWidget *parent = nullptr);
};

#endif // FLOWCHARTVIEW_H
