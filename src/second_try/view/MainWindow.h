#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QTabWidget>

#include "DataViewWindow.h"

class MainWindow : public QTabWidget {
  Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr) : QTabWidget(parent) {
      DataViewWindow *data_window = new DataViewWindow;

      addTab(data_window, QString("Data"));

      setWindowTitle(tr("MODULE"));
    }

    QSize sizeHint() const override { return QSize(1000, 1000); }
};

#endif  // MAINWINDOW_H_