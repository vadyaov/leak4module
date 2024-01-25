#ifndef DATAVIEWWINDOW_H_
#define DATAVIEWWINDOW_H_

#include <QWidget>

#include "../model/variants.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QComboBox;
class QTableWidget;
class QLineEdit;
class Button;
QT_END_NAMESPACE

class GroupBox;

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
      void FindMaxMinVariant();

    private:
      Variants variants;

      QTableWidget* tableWidget;
      QLabel* dir_name;
      QComboBox* var_box;
      QComboBox* way_box;

      GroupBox* groupbox;
      QLabel *max_var, *min_var;

      QLineEdit *errors;


    private:
      Button* CreateButton(const QString& text, const char* member);

      void FillTableWithOneForm(size_t it, Release::Way way_idx, int var_idx, int& line_idx);
      void FillTimeLine(int& line_idx);

};

#endif // DATAVIEWWINDOW_H_
