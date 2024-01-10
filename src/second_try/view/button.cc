#include "button.h"

Button::Button(const QString &text, QWidget *parent) : QToolButton(parent) {
  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
  setText(text);
}

QSize Button::sizeHint() const { return QSize(180, 30); }