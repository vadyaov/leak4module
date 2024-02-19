#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QWidget>

#include "../model/variants.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QComboBox;
class QTableWidget;
class QLineEdit;
class Button;
class QLineSeries;
class QChart;
class QChartView;
class QGroupBox;
class QRadioButton;
class QValueAxis;

class QStandardItemModel;
QT_END_NAMESPACE

class GroupBox;

class MainWindow : public QWidget {
  Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);

    private slots:
      void DirectoryClicked();
      void UpdateTable();
      void FindMaxMinVariant();

      void FillIodine();
      void FillIrg();
      void FillAero();

      void PrintChart();

    private:
      Variants variants;

      QTableWidget* tableWidget;
      QLabel* dir_name;
      QComboBox* var_box;
      QComboBox* way_box;

      GroupBox* groupbox;
      QLabel *max_var, *min_var;

      QLineEdit *errors;

      QChart* chart;
      QChartView* chart_view;

      QComboBox* nucl_box;

      QRadioButton* mol_iod_radio;
      QRadioButton* org_iod_radio;
      QRadioButton* aer_iod_radio;
      QRadioButton* irg_radio;
      QRadioButton* aer_radio;

    private:
      Button* CreateButton(const QString& text, const char* member);

      void FillTableWithOneForm(size_t it, Release::Way way_idx, int var_idx, int& line_idx);
      void FillTimeLine(int& line_idx);

      QGroupBox *createGroupBoxForChart();

      QStandardItemModel* CreateModel(const std::vector<std::string>&);

      int GetTypeIndex();
      std::vector<std::string> GetNamesFromBox();
};

#endif  // MAINWINDOW_H_
