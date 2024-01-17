#ifndef DATAVIEWWINDOW_H_
#define DATAVIEWWINDOW_H_

#include <QWidget>
#include <QSqlTableModel>

#include "button.h"

#include "../model/variants.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QComboBox;
// class QTableWidget;
// class QTableWidgetItem;
class QTableView;
QT_END_NAMESPACE

class DataViewWindow : public QWidget {
  Q_OBJECT

  public:
    DataViewWindow();
    // ~DataViewWindow() {
    //   delete model;
    // }

    // QSize sizeHint() const override;
    private slots:
      void DirectoryClicked();
      void ShowClicked();

    private:
      Variants variants;
      // QTableWidget* tableWidget;
      QTableView *tableView;
      QLabel* dir_name;
      QComboBox* var_box;
      QComboBox* way_box;
      QSqlTableModel model;

    private:
      Button* CreateButton(const QString& text, const char* member);

      // std::vector<QTableWidgetItem*> molecular_iod_items;

};

#endif // DATAVIEWWINDOW_H_