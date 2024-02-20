#include "callout.h"

#include <QPainter>
#include <QFontMetrics>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QChart>

Callout::Callout(QChart* chart) : QGraphicsItem(chart), m_chart(chart) {}

QRectF Callout::boundingRect() const {
  QPointF anchor = mapFromParent(m_chart->mapToPosition(m_anchor));

  QRect rect;
  rect.setLeft(qMin(m_rect.left(), anchor.x()));
  rect.setRigth(qMax(m_rect.right(), anchor.x()));
  rect.setTop(qMin(m_rect.top(), anchor.y()));
  rect.setBottom(qMax(m_rect.bottom(), anchor.y()));

  return rect;
}