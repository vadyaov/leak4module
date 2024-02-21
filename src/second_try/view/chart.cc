#include "chart.h"

#include <QResizeEvent>
#include <QGraphicsScene>
#include <QChart>
#include <QLineSeries>
#include <QGraphicsTextItem>

#include "callout.h"

#include <QMouseEvent>

ChartView::ChartView(QWidget *parent)
     : QGraphicsView(new QGraphicsScene, parent),
       m_coordX(0),
       m_coordY(0),
       m_chart(0),
       m_tooltip(0)
{
  setDragMode(QGraphicsView::NoDrag);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  m_chart = new QChart;
  // m_chart->setMinimumSize(640, 480);
  m_chart->setTitle("Hover the line to show callout. Click the line to make it stay");
  m_chart->legend()->hide();
  m_chart->setAcceptHoverEvents(true);

  setRenderHint(QPainter::Antialiasing);
  scene()->addItem(m_chart);

  m_coordX = new QGraphicsSimpleTextItem(m_chart);
  m_coordX->setPos(m_chart->size().width()/2 - 50, m_chart->size().height());
  m_coordX->setText("x: ");

  m_coordY = new QGraphicsSimpleTextItem(m_chart);
  m_coordY->setPos(m_chart->size().width()/2 + 50, m_chart->size().height());
  m_coordY->setText("y: ");

  this->setMouseTracking(true);
}

// если легенда не будет нужна, можно оставить только line_name и убрать obj_name. и записывать туда (в line_name) имя нуклида, по которому
// можно будет потом удалить серию. сейчас в line_name записывается номер варианта (для корректного отображения легенды)
void ChartView::addLine(const QString& line_name, const QString& obj_name, const std::vector<double>& activity, const std::vector<double>& time) {
  QLineSeries* series = new QLineSeries;
  series->setName(line_name);
  series->setObjectName(obj_name);

  for (std::size_t i = 0; i != time.size(); ++i) {
    series->append(time[i], activity[i]);
  }

  connect(series, &QLineSeries::clicked, this, &ChartView::keepCallout);
  connect(series, &QLineSeries::hovered, this, &ChartView::tooltip);

  m_chart->addSeries(series);
  m_chart->createDefaultAxes();
}

void ChartView::deleteLine(const QString& obj_name) {
  for (const auto& s : m_chart->series())
    if (s->objectName() == obj_name)
      m_chart->removeSeries(s);
}

void ChartView::deleteAllLines() {
  m_chart->removeAllSeries();
}

void ChartView::resizeEvent(QResizeEvent *event) {
  if (scene()) {
    scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
    m_chart->resize(event->size());
    m_coordX->setPos(m_chart->size().width()/2 - 50, m_chart->size().height() - 20);
    m_coordY->setPos(m_chart->size().width()/2 + 50, m_chart->size().height() - 20);

    const auto callouts = m_callouts;
    for (Callout * callout : callouts)
      callout->updateGeometry();
  }
  QGraphicsView::resizeEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent *event) {
  m_coordX->setText(QString("x: %1").arg(m_chart->mapToValue(event->pos()).x()));
  m_coordY->setText(QString("y: %1").arg(m_chart->mapToValue(event->pos()).y()));
  QGraphicsView::mouseMoveEvent(event);
}

void ChartView::keepCallout() {
  m_callouts.append(m_tooltip);
  m_tooltip = new Callout(m_chart);
}

void ChartView::tooltip(QPointF point, bool state) {
  if (m_tooltip == 0)
    m_tooltip = new Callout(m_chart);

  if (state) {
    m_tooltip->setText(QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y()));
    m_tooltip->setAnchor(point);
    m_tooltip->setZValue(11);
    m_tooltip->updateGeometry();
    m_tooltip->show();
  } else {
    m_tooltip->hide();
  }
}