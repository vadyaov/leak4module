#ifndef DATAVIEWWINDOW_H_
#define DATAVIEWWINDOW_H_

#include <QWidget>

#include "button.h"

#include "../model/variants.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QComboBox;
class QTableWidget;
QT_END_NAMESPACE

class DataViewWindow : public QWidget {
  Q_OBJECT

  public:
    DataViewWindow();

    // QSize sizeHint() const override;
    private slots:
      void DirectoryClicked();
      void ShowClicked();

    private:
      Variants variants;
      QTableWidget* tableWidget;
      QLabel* dir_name;
      QComboBox* var_box;
      QComboBox* way_box;

    private:
      Button* CreateButton(const QString& text, const char* member);

};

#endif // DATAVIEWWINDOW_H_