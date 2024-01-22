#ifndef DATAVIEWWINDOW_H_
#define DATAVIEWWINDOW_H_

#include <QWidget>

#include "button.h"

#include "../model/variants.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QComboBox;
class QTableWidget;
/* class QTableWidgetItem; */
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
      void UpdateTable();

    private:
      Variants variants;
      QTableWidget* tableWidget;
      QLabel* dir_name;
      QComboBox* var_box;
      QComboBox* way_box;

    private:
      Button* CreateButton(const QString& text, const char* member);

      // std::vector<QTableWidgetItem*> molecular_iod_items;
      void FillTableWithOneForm(size_t it, Release::Way way_idx, int var_idx, int& line_idx);
      void FillTimeLine(int& line_idx);

};

#endif // DATAVIEWWINDOW_H_
