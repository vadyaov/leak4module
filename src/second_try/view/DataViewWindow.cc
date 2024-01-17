#include "DataViewWindow.h"

#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
// #include <QTableWidget>
// #include <QTableWidgetItem>
#include <QTableView>

#include <iostream>

DataViewWindow::DataViewWindow() {
  Button *dir_button = CreateButton(tr("Directory"), SLOT(DirectoryClicked()));
  Button *show_button = CreateButton(tr("show"), SLOT(ShowClicked()));

  dir_name = new QLabel;

  way_box = new QComboBox;
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

  // tableWidget = new QTableWidget(this);
  tableView = new QTableView;

  QGridLayout *main_layout = new QGridLayout;
  QGridLayout *stuff_layout = new QGridLayout;

  stuff_layout->addWidget(dir_button, 0, 0, 1, 1);
  stuff_layout->addWidget(dir_name, 0, 1, 1, 1);
  stuff_layout->addWidget(way_box, 1, 0, 1, 1);
  stuff_layout->addWidget(var_box, 1, 1, 1, 1);
  stuff_layout->addWidget(show_button, 3, 0, 2, 2);

  // main_layout->addWidget(tableWidget, 0, 1, 10, 10);
  main_layout->addWidget(tableView, 0, 1, 10, 10);

  main_layout->addLayout(stuff_layout, 0, 0, 1, 1);

  setLayout(main_layout);
}

void InitModel(QSqlTableModel* m) {
  m->setTable("Release");
  m->setEditStrategy(QSqlTableModel::OnManualSubmit); // All changes will be cached in the model until either submitAll() or revertAll() is called.
}

void DataViewWindow::DirectoryClicked() {
  QString dir_path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly
                                                                                                 | QFileDialog::DontResolveSymlinks);
  if (!dir_path.isEmpty()) {
    auto pos = dir_path.lastIndexOf('/') + 1;
    dir_name->setText(dir_path.mid(pos, dir_path.size() - pos));
    variants.LoadData(dir_path.toStdString());

    var_box->clear();
    for (const std::string& s : variants.GetNames())
      var_box->addItem(QString(s.data()));
  }
}

// creation results table
void DataViewWindow::ShowClicked() {
  /*
  int headnames_num = 6;
  int rows = variants.TotalNuclidesNumber() + headnames_num + 1; // adding 1 for time line
  int columns = variants.GetTimeArray().size();

  tableWidget->setRowCount(rows);
  tableWidget->setColumnCount(columns);

  int start_for_span = 0;
  int current_var = var_box->currentIndex();
  Release::Way current_way = Release::Way(1 << way_box->currentIndex());

  tableWidget->setSpan(start_for_span++, 0, 1, columns); // Time
  QTableWidgetItem *vheaderItem = new QTableWidgetItem(tr("TIME, s"));
  vheaderItem->setTextAlignment(Qt::AlignCenter);
  tableWidget->setVerticalHeaderItem(start_for_span, vheaderItem);

  int t_col = 0;
  for (int t : variants.GetTimeArray()) {
    QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(t));
    newItem->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(start_for_span, t_col++, newItem);
  }
  start_for_span++;

  tableWidget->setSpan(start_for_span, 0, 1, columns); // molecular iodine

  QTableWidgetItem *molHheaderItem = new QTableWidgetItem(tr("Molecular Iodine"));
  molHheaderItem->setTextAlignment(Qt::AlignCenter);
  tableWidget->setItem(start_for_span++, 0, molHheaderItem);

  auto molecular_iod = variants.GetNuclideData(current_var, current_way, Nuclide::IOD_MOL);
  for (const auto & iod : molecular_iod) {
    QTableWidgetItem *newItem = new QTableWidgetItem(QString(iod.first.data()));
    newItem->setTextAlignment(Qt::AlignCenter);
    // molecular_iod_items.push_back(newItem);
    tableWidget->setVerticalHeaderItem(start_for_span, newItem);
    for (std::size_t col = 0; col < iod.second.size(); ++col) {
      QTableWidgetItem *actItem = new QTableWidgetItem(QString::number(iod.second[col]));
      actItem->setTextAlignment(Qt::AlignCenter);
      tableWidget->setItem(start_for_span, col, actItem);
    }
    start_for_span++;
  }

  tableWidget->setSpan(start_for_span, 0, 1, columns); // organic iodine

  QTableWidgetItem *orgHheaderItem = new QTableWidgetItem(tr("Organic Iodine"));
  orgHheaderItem->setTextAlignment(Qt::AlignCenter);
  tableWidget->setItem(start_for_span++, 0, orgHheaderItem);

  auto organic_iod = variants.GetNuclideData(current_var, current_way, Nuclide::IOD_ORG);
  for (const auto & iod : organic_iod) {
    QTableWidgetItem *newItem = new QTableWidgetItem(QString(iod.first.data()));
    newItem->setTextAlignment(Qt::AlignCenter);
    // molecular_iod_items.push_back(newItem);
    tableWidget->setVerticalHeaderItem(start_for_span, newItem);
    for (std::size_t col = 0; col < iod.second.size(); ++col) {
      QTableWidgetItem *actItem = new QTableWidgetItem(QString::number(iod.second[col]));
      actItem->setTextAlignment(Qt::AlignCenter);
      tableWidget->setItem(start_for_span, col, actItem);
    }
    start_for_span++;
  }

  tableWidget->setSpan(start_for_span, 0, 1, columns); // irg

  QTableWidgetItem *irgHheaderItem = new QTableWidgetItem(tr("IRG"));
  irgHheaderItem->setTextAlignment(Qt::AlignCenter);
  tableWidget->setItem(start_for_span++, 0, irgHheaderItem);

  auto irg = variants.GetNuclideData(current_var, current_way, Nuclide::IRG);
  for (const auto & ir : irg) {
    QTableWidgetItem *newItem = new QTableWidgetItem(QString(ir.first.data()));
    newItem->setTextAlignment(Qt::AlignCenter);
    // molecular_iod_items.push_back(newItem);
    tableWidget->setVerticalHeaderItem(start_for_span, newItem);
    for (std::size_t col = 0; col < ir.second.size(); ++col) {
      QTableWidgetItem *actItem = new QTableWidgetItem(QString::number(ir.second[col]));
      actItem->setTextAlignment(Qt::AlignCenter);
      tableWidget->setItem(start_for_span, col, actItem);
    }
    start_for_span++;
  }

  tableWidget->setSpan(start_for_span, 0, 1, columns); // aer

  QTableWidgetItem *aerHheaderItem = new QTableWidgetItem(tr("Aerosols"));
  aerHheaderItem->setTextAlignment(Qt::AlignCenter);
  tableWidget->setItem(start_for_span++, 0, aerHheaderItem);

  auto aer = variants.GetNuclideData(current_var, current_way, Nuclide::AER);
  for (const auto & a : aer) {
    QTableWidgetItem *newItem = new QTableWidgetItem(QString(a.first.data()));
    newItem->setTextAlignment(Qt::AlignCenter);
    // molecular_iod_items.push_back(newItem);
    tableWidget->setVerticalHeaderItem(start_for_span, newItem);
    for (std::size_t col = 0; col < a.second.size(); ++col) {
      QTableWidgetItem *actItem = new QTableWidgetItem(QString::number(a.second[col]));
      actItem->setTextAlignment(Qt::AlignCenter);
      tableWidget->setItem(start_for_span, col, actItem);
    }
    start_for_span++;
  }

  tableWidget->setSpan(start_for_span, 0, 1, columns); // aer iodine

  QTableWidgetItem *aerIHheaderItem = new QTableWidgetItem(tr("Aerosol Iodine"));
  aerIHheaderItem->setTextAlignment(Qt::AlignCenter);
  tableWidget->setItem(start_for_span++, 0, aerIHheaderItem);

  auto i_aer = variants.GetNuclideData(current_var, current_way, Nuclide::IOD_AER);
  for (const auto & ia : i_aer) {
    QTableWidgetItem *newItem = new QTableWidgetItem(QString(ia.first.data()));
    // molecular_iod_items.push_back(newItem);
    tableWidget->setVerticalHeaderItem(start_for_span, newItem);
    for (std::size_t col = 0; col < ia.second.size(); ++col) {
      QTableWidgetItem *actItem = new QTableWidgetItem(QString::number(ia.second[col]));
      tableWidget->setItem(start_for_span, col, actItem);
    }
    start_for_span++;
  }
*/
}

Button *DataViewWindow::CreateButton(const QString &text, const char *member) {
  Button *button = new Button(text);
  connect(button, SIGNAL(clicked()), this, member);
  return button;
}