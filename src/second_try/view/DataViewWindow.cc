#include "DataViewWindow.h"
#include "GroupBox.h"

#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QTableWidget>
#include <QTableWidgetItem>

#include <iostream>

DataViewWindow::DataViewWindow() {
  Button *dir_button = CreateButton(tr("Directory"), SLOT(DirectoryClicked()));

  dir_name = new QLabel;

  groupbox = new GroupBox(tr("MaxMin"));

  way_box = new QComboBox;
  connect(way_box, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateTable()));
  way_box->addItem(tr("AnnulusAirAct"), 1 << 0);
  way_box->addItem(tr("AnnulusSurfAct"), 1 << 1);
  way_box->addItem(tr("AnnulusVentRelease"), 1 << 2);
  way_box->addItem(tr("BypassRelease"), 1 << 3);
  way_box->addItem(tr("ContAirAct"), 1 << 4);
  way_box->addItem(tr("ContSurfAct"), 1 << 5);
  way_box->addItem(tr("ContVentRelease"), 1 << 6);
  way_box->addItem(tr("SourceAct"), 1 << 7);
  way_box->addItem(tr("SprinklerAct"), 1 << 8);

  var_box = new QComboBox;
  connect(var_box, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateTable()));

  Button* find_max = CreateButton(tr("Max"), SLOT(FindMaxVariant()));
  Button* find_min = CreateButton(tr("Min"), SLOT(FindMinVariant()));

  max_var = new QLabel;
  min_var = new QLabel;

  tableWidget = new QTableWidget(this);

  QGridLayout *main_layout = new QGridLayout;
  QGridLayout *stuff_layout = new QGridLayout;

  stuff_layout->addWidget(dir_button, 0, 0, 1, 1);
  stuff_layout->addWidget(dir_name, 0, 1, 1, 1);
  stuff_layout->addWidget(way_box, 1, 0, 1, 1);
  stuff_layout->addWidget(var_box, 1, 1, 1, 1);
  stuff_layout->addWidget(groupbox, 2, 0, 1, 2);
  stuff_layout->addWidget(find_max, 3, 0, 1, 1);
  stuff_layout->addWidget(find_min, 3, 1, 1, 1);
  stuff_layout->addWidget(max_var, 4, 0, 1, 1);
  stuff_layout->addWidget(min_var, 4, 1, 1, 1);

  main_layout->addWidget(tableWidget, 0, 1, 3, 1);

  main_layout->addLayout(stuff_layout, 0, 0, 1, 1);

  setLayout(main_layout);
}

void DataViewWindow::DirectoryClicked() {
  QString dir_path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "../", QFileDialog::ShowDirsOnly
                                                                                                 | QFileDialog::DontResolveSymlinks);
  if (!dir_path.isEmpty()) {
    auto pos = dir_path.lastIndexOf('/') + 1;
    dir_name->setText(dir_path.mid(pos, dir_path.size() - pos));
    variants.LoadData(dir_path.toStdString());

    var_box->clear();
    for (const std::string& s : variants.GetNames())
      var_box->addItem(QString(s.data()));
  }

  UpdateTable();
}

void DataViewWindow::FillTableWithOneForm(size_t it, Release::Way way_idx, int var_idx, int& line_idx) {

  static const std::vector<Nuclide::Tp> forms {Nuclide::IOD_MOL, Nuclide::IOD_ORG,
                                               Nuclide::IRG, Nuclide::AER, Nuclide::IOD_AER};

  static const std::vector<std::string> headers {"Molecular Iodine", "Organic Iodine",
                                          "IRG", "Aerosols", "Aerosol Iodine"};

    tableWidget->setSpan(line_idx, 0, 1, tableWidget->columnCount());
    QTableWidgetItem *headerItem = new QTableWidgetItem(tr(headers[it].data()));
    headerItem->setTextAlignment(Qt::AlignCenter);
    tableWidget->setVerticalHeaderItem(line_idx, new QTableWidgetItem);
    tableWidget->setItem(line_idx++, 0, headerItem);

    auto nuclide_data = variants.GetNuclideData(var_idx, way_idx, forms[it]);
    for (const auto & nucl : nuclide_data) {
      QTableWidgetItem *newItem = new QTableWidgetItem(QString(nucl.first.data()));
      newItem->setTextAlignment(Qt::AlignCenter);
      tableWidget->setVerticalHeaderItem(line_idx, newItem);
      for (std::size_t col = 0; col < nucl.second.size(); ++col) {
        QTableWidgetItem *actItem = new QTableWidgetItem(QString::number(nucl.second[col], 'e', 3));
        actItem->setTextAlignment(Qt::AlignCenter);
        tableWidget->setItem(line_idx, col, actItem);
      }
      ++line_idx;
    }
}

void DataViewWindow::FillTimeLine(int& line_idx) {
  tableWidget->setVerticalHeaderItem(line_idx, new QTableWidgetItem);
  tableWidget->setSpan(line_idx++, 0, 1, tableWidget->columnCount()); // Time
  QTableWidgetItem *vheaderItem = new QTableWidgetItem(tr("TIME, s"));
  vheaderItem->setTextAlignment(Qt::AlignCenter);
  tableWidget->setVerticalHeaderItem(line_idx, vheaderItem);

  int t_col = 0;
  for (int t : variants.GetTimeArray()) {
    QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(t));
    newItem->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(line_idx, t_col++, newItem);
  }
  line_idx++;
}

void DataViewWindow::UpdateTable() {
  if (variants.Empty() == false) {
    tableWidget->clear();
    tableWidget->setRowCount(variants.TotalNuclidesNumber() + 7); // adding 1 for time line and 6 for headers
    tableWidget->setColumnCount(variants.GetTimeArray().size());

    int current_var = var_box->currentIndex();
    Release::Way current_way = Release::Way(1 << way_box->currentIndex());

    int line_idx = 0;

    FillTimeLine(line_idx);
    for (size_t it = 0; it != 5; ++it) { // because we have 5 forms of nuclides
      FillTableWithOneForm(it, current_way, current_var, line_idx);
    }
  }
}

Button *DataViewWindow::CreateButton(const QString &text, const char *member) {
  Button *button = new Button(text);
  connect(button, SIGNAL(clicked()), this, member);
  return button;
}

void DataViewWindow::FindMaxVariant() {
  /* std::vector<int> selected_forms = groupbox->SelectedForms(); */
  /* Release::Way current_way = Release::Way(1 << way_box->currentIndex()); */

  // continue here

}

void DataViewWindow::FindMinVariant() {
}
