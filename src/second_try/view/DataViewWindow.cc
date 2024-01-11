#include "DataViewWindow.h"

#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QTableWidget>
#include <QComboBox>

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

  tableWidget = new QTableWidget(this);

  QGridLayout *main_layout = new QGridLayout;
  QGridLayout *stuff_layout = new QGridLayout;

  stuff_layout->addWidget(dir_button, 0, 0, 1, 1);
  stuff_layout->addWidget(dir_name, 0, 1, 1, 1);
  stuff_layout->addWidget(way_box, 1, 0, 1, 1);
  stuff_layout->addWidget(var_box, 1, 1, 1, 1);
  stuff_layout->addWidget(show_button, 3, 0, 2, 2);

  main_layout->addWidget(tableWidget, 0, 1, 10, 10);

  main_layout->addLayout(stuff_layout, 0, 0, 1, 1);

  setLayout(main_layout);
}

void DataViewWindow::DirectoryClicked() {
  QString dir_path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly
                                                                                                 | QFileDialog::DontResolveSymlinks);
  if (!dir_path.isEmpty()) {
    auto pos = dir_path.lastIndexOf('/') + 1;
    dir_name->setText(dir_path.mid(pos, dir_path.size() - pos));
    int way = way_box->itemData(way_box->currentIndex()).toInt();
    variants.LoadData(dir_path.toStdString(), way);
    // variants.print(way);

    var_box->clear();
    for (const std::string& s : variants.GetNames())
      var_box->addItem(QString(s.data()));
  }
}

void DataViewWindow::ShowClicked() {
  int headnames_num = 6;
  int rows = variants.TotalNuclidesNumber() + headnames_num + 1; // adding 1 for time line
  int columns = variants.GetTimeArray().size() + 1;

  int start_for_span = 2;

  tableWidget->setRowCount(rows);
  tableWidget->setColumnCount(columns);

  tableWidget->setSpan(0, 1, 1, columns); // Time

  tableWidget->setSpan(start_for_span++, 0, 1, columns); // molecular iodine
  for (int k = variants.IodNum(); k != 0; --k) {
    // ПРОДОЛЖИТЬ ТУТ
  }
  
  start_for_span += variants.IodNum();

  tableWidget->setSpan(start_for_span, 0, 1, columns); // organic iodine
  start_for_span += variants.IodNum() + 1;

  tableWidget->setSpan(start_for_span, 0, 1, columns); // irg
  start_for_span += variants.IrgNum() + 1;

  tableWidget->setSpan(start_for_span, 0, 1, columns); // aer
  start_for_span += variants.AerNum() + 1;

  tableWidget->setSpan(start_for_span, 0, 1, columns); // aee iodine

}

Button *DataViewWindow::CreateButton(const QString &text, const char *member) {
  Button *button = new Button(text);
  connect(button, SIGNAL(clicked()), this, member);
  return button;
}