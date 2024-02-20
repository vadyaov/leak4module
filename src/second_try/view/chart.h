#ifndef CHART_H_
#define CHART_H_

#include <QGraphicsView>
#include <QChartGlobal>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QMouseEvent;
class QResizeEvent;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

class Callout;

QT_CHARTS_USE_NAMESPACE

class ChartView : public QGraphicsView {
  Q_OBJECT

  public:
    ChartView(QWidget* parent = 0);

    void addLine(const QString& line_name, const QString& obj_name, const std::vector<double>& activity, const std::vector<double>& time);

  protected:
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

  public slots:
    void keepCallout();
    void tooltip(QPointF point, bool state);

  private:
    QGraphicsSimpleTextItem *m_coordX;
    QGraphicsSimpleTextItem *m_coordY;
    QChart *m_chart;
    Callout *m_tooltip;
    QList<Callout*> m_callouts;
}

#endif // CHART_H_