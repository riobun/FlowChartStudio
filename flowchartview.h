#ifndef FLOWCHARTVIEW_H
#define FLOWCHARTVIEW_H

#include <QGraphicsView>


class FlowChartView : public QGraphicsView
{
    Q_OBJECT

public:
    FlowChartView(QWidget *parent = nullptr);

private:
    void mousePressEvent(QMouseEvent *event) final;
    void mouseReleaseEvent(QMouseEvent *event) final;

private:
    QPointF mousePressedPoint;
};

#endif // FLOWCHARTVIEW_H
