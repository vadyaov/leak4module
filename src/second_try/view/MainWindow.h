#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QWidget>

class MainWindow : public QWidget {
  Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr) : QWidget(parent) {
      setWindowTitle(tr("test"));
    }

    // QSize sizeHint() const override { return QSize(1000, 1000); }
};

#endif  // MAINWINDOW_H_