#include "DataViewWindow.h"

#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QTableWidget>

#include <iostream>

DataViewWindow::DataViewWindow() {
  Button *dir_button = CreateButton(tr("Directory"), SLOT(DirectoryClicked()));
  dir_name = new QLabel;;

  tableWidget = new QTableWidget(this);

  QGridLayout *main_layout = new QGridLayout;
  QGridLayout *stuff_layout = new QGridLayout;

  stuff_layout->addWidget(dir_button, 0, 0, 1, 1);
  stuff_layout->addWidget(dir_name, 0, 1, 1, 1);

  main_layout->addWidget(tableWidget, 0, 1, 10, 10);

  main_layout->addLayout(stuff_layout, 0, 0, 1, 1);

  setLayout(main_layout);
}

void DataViewWindow::DirectoryClicked() {
  QString dir_path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly
                                                                                                 | QFileDialog::DontResolveSymlinks);
  auto pos = dir_path.lastIndexOf('/') + 1;
  dir_name->setText(dir_path.mid(pos, dir_path.size() - pos));
}

Button *DataViewWindow::CreateButton(const QString &text, const char *member) {
  Button *button = new Button(text);
  connect(button, SIGNAL(clicked()), this, member);
  return button;
}