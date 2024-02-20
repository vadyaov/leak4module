#include "MainWindow.h"

#include "GroupBox.h"
#include "button.h"

#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLineEdit>
#include <QLineSeries>
#include <QChartView>
#include <QValueAxis>

#include <QStandardItemModel>
#include <QStandardItem>

#include <QSplitter>


#include <iostream>
#include <limits>

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
  Button *dir_button = CreateButton(tr("Open"), SLOT(DirectoryClicked()));

  dir_name = new QLabel;

  groupbox = new GroupBox(tr("Choose nuclides to find min/max"));

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

  Button* update_minmax = CreateButton(tr("update"), SLOT(FindMaxMinVariant()));

  max_var = new QLabel;
  min_var = new QLabel;

  errors = new QLineEdit;
  errors->setReadOnly(true);

  tableWidget = new QTableWidget;
  tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  chart = new QChart;
  chart_view = new QChartView(chart);
  chart_view->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

  nucl_box = new QComboBox;
  connect(nucl_box, &QComboBox::currentIndexChanged, [this]() { chart->removeAllSeries(); });

  QGridLayout *main_layout = new QGridLayout;
  QGridLayout *stuff_layout = new QGridLayout;

  QSplitter* splitter = new QSplitter;

  stuff_layout->addWidget(dir_button, 0, 0, 1, 1);
  stuff_layout->addWidget(dir_name, 0, 1, 1, 1);
  stuff_layout->addWidget(way_box, 1, 0, 1, 1);
  stuff_layout->addWidget(var_box, 1, 1, 1, 1);
  stuff_layout->addWidget(groupbox, 2, 0, 3, 1);
  stuff_layout->addWidget(update_minmax, 2, 1, 1, 1);
  stuff_layout->addWidget(max_var, 3, 1, 1, 1);
  stuff_layout->addWidget(min_var, 4, 1, 1, 1);
  stuff_layout->addWidget(errors, 10, 0, 1, 2);

  stuff_layout->addWidget(createGroupBoxForChart(), 11, 0, 1, 1);
  stuff_layout->addWidget(nucl_box, 11, 1, 1, 1, Qt::AlignTop);

  splitter->addWidget(tableWidget);
  splitter->addWidget(chart_view);
  // main_layout->addWidget(tableWidget, 0, 1, 3, 1);
  // main_layout->addWidget(chart_view, 0, 2, 3, 1);
  main_layout->addWidget(splitter, 0, 1, 3, 2);

  main_layout->setColumnStretch(1, 2);
  main_layout->setColumnStretch(2, 3);

  main_layout->addLayout(stuff_layout, 0, 0, 1, 1);

  setLayout(main_layout);
}

void MainWindow::DirectoryClicked() {
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

void MainWindow::FillTableWithOneForm(size_t it, Release::Way way_idx, int var_idx, int& line_idx) {

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

void MainWindow::FillTimeLine(int& line_idx) {
  tableWidget->setVerticalHeaderItem(line_idx, new QTableWidgetItem);
  tableWidget->setSpan(line_idx, 0, 1, tableWidget->columnCount());
  QTableWidgetItem* hHeaderRelease = new QTableWidgetItem(QString("Release by time, Bq"));
  hHeaderRelease->setTextAlignment(Qt::AlignCenter);
  tableWidget->setItem(line_idx, 0, hHeaderRelease);

  ++line_idx;
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

void MainWindow::UpdateTable() {
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

Button *MainWindow::CreateButton(const QString &text, const char *member) {
  Button *button = new Button(text);
  connect(button, SIGNAL(clicked()), this, member);
  return button;
}

void MainWindow::FindMaxMinVariant() {
  if (!variants.Empty()) {
    std::vector<int> selected_forms = groupbox->SelectedForms();
    if (selected_forms.empty()) {
      errors->setText(tr("NO FORMS SELECTED"));
      return;
    }
    errors->clear();

    Release::Way current_way = Release::Way(1 << way_box->currentIndex());

    std::string min_variant_dir_name = variants.FindVariant<double>(current_way, selected_forms, std::less<double>{});
    QString min{"Minimum: "};
    QString max{"Maximum: "};

    min.append(variants.FindVariant<double>(current_way, selected_forms, std::less<double>{}));
    max.append(variants.FindVariant<double>(current_way, selected_forms, {}));

    min_var->setText(min);
    max_var->setText(max);
  }
}

QGroupBox* MainWindow::createGroupBoxForChart() {
  QGroupBox* groupBox = new QGroupBox(tr("Select nuclide form"));

  mol_iod_radio = new QRadioButton(tr("Molecular Iodine"));
  connect(mol_iod_radio, SIGNAL(clicked()), this, SLOT(FillIodine()));
  org_iod_radio = new QRadioButton(tr("Organic Iodine"));
  connect(org_iod_radio, SIGNAL(clicked()), this, SLOT(FillIodine()));
  aer_iod_radio = new QRadioButton(tr("Aerosol Iodine"));
  connect(aer_iod_radio, SIGNAL(clicked()), this, SLOT(FillIodine()));
  irg_radio = new QRadioButton(tr("IRG"));
  connect(irg_radio, SIGNAL(clicked()), this, SLOT(FillIrg()));
  aer_radio = new QRadioButton(tr("Aerosols"));
  connect(aer_radio, SIGNAL(clicked()), this, SLOT(FillAero()));

  // mol_iod_radio->setChecked(true);

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(mol_iod_radio);
  vbox->addWidget(org_iod_radio);
  vbox->addWidget(aer_iod_radio);
  vbox->addWidget(irg_radio);
  vbox->addWidget(aer_radio);

  groupBox->setLayout(vbox);

  return groupBox;
}

void MainWindow::FillIodine() {
  auto names = variants.GetNuclideNames(Nuclide::IOD_MOL);
  nucl_box->setModel(CreateModel(names));
}

void MainWindow::FillIrg() {
  auto names = variants.GetNuclideNames(Nuclide::IRG);
  nucl_box->setModel(CreateModel(names));
}

void MainWindow::FillAero() {
  auto names = variants.GetNuclideNames(Nuclide::AER);
  nucl_box->setModel(CreateModel(names));
}
// Я хочу не перерисовывать каждый раз график, когда нажимается что то внутри бокса, а проверять, добавлена серия или удалена. И если
// добавлена, то добавить ее на график, если удалена - то удалить. Для этого я хочу чтобы метод print принимал указатель на итем, который
// изменился, и уже в принте надо проверить, что с ним случилось (удалить его или добавить, то есть если он checked то добавить, и наоборот)
QStandardItemModel* MainWindow::CreateModel(const std::vector<std::string>& names) {
  QStandardItemModel* model = new QStandardItemModel(names.size(), 1);
  for (std::size_t i = 0; i < names.size(); ++i) {
    QStandardItem* item = new QStandardItem(QString(names[i].data()));

    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setData(Qt::Unchecked, Qt::CheckStateRole);

    model->setItem(i, 0, item);
  }

  connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(PrintChart(QStandardItem*)));

  return model;
}

void MainWindow::PrintChart(QStandardItem* item) {
  QString item_name = item->text();

  int way_idx = way_box->currentIndex();
  int type_idx = GetTypeIndex();

  static double ymax {std::numeric_limits<double>::min()};
  static double ymin {std::numeric_limits<double>::max()};

  const std::vector<double>& time_arr = variants.GetTimeArray();

  if (item->checkState() == Qt::Checked) {
    std::cout << "Add to chart\n";
    auto activity_data = variants.NuclideActivityFor(item_name.toStdString(), Release::Way(1 << way_idx), Nuclide::Tp(type_idx));
    auto dir_names = variants.GetDirNames();

    for (std::size_t i = 0; i != activity_data.size(); ++i) {
      // std::cout << "Activity for " << item_name << ": ";
      auto series = new QLineSeries();
      series->setName(dir_names[i].data());
      series->setObjectName(item_name);
      for (std::size_t j = 0; j != activity_data[i].second.size(); ++j) {
        series->append(time_arr[j], activity_data[i].second[j]);
        std::cout << activity_data[i].second[j] << " ";
        if (activity_data[i].second[j] > ymax)
          ymax = activity_data[i].second[j];
        if (activity_data[i].second[j] < ymin)
          ymin = activity_data[i].second[j];
      }
      chart->addSeries(series);
      chart->createDefaultAxes();
      std::cout << "\n";
    } 

    QList<QAbstractAxis*> axisy = chart->axes(Qt::Vertical);
    if (!axisy.empty()) {
      axisy.back()->setRange(ymin + 100, ymax - 100);
      static_cast<QValueAxis*>(axisy.back())->setLabelFormat("%.3e");
    }

    QList<QAbstractAxis*> axisx = chart->axes(Qt::Horizontal);
    if (!axisy.empty())
      axisx.back()->setRange(0, time_arr.back() + 1000);

  } else {
    auto sers = chart->series();
    for (QAbstractSeries* s : sers) {
      if (s->objectName() == item_name)
        chart->removeSeries(s);
    }
  }

}

int MainWindow::GetTypeIndex() {
  int idx;
  if (mol_iod_radio->isChecked())
    idx = 0;
  else if (org_iod_radio->isChecked())
    idx = 1;
  else if (aer_iod_radio->isChecked())
    idx = 2;
  else if (irg_radio->isChecked())
    idx = 3;
  else if (aer_radio->isChecked())
    idx = 4;
  else {
    // noone is checked
  }
  return idx;
}

std::vector<std::string> MainWindow::GetNamesFromBox() {
  const int n = nucl_box->count();
  std::vector<std::string> names;

  names.reserve(n);
  QAbstractItemModel* model_ptr = nucl_box->model();
  for (int i = 0; i != n; ++i) {
    if (qobject_cast<QStandardItemModel*>(model_ptr)->item(i)->checkState() == Qt::Checked)
      names.push_back(nucl_box->itemText(i).toStdString());
  }

  return names;
}