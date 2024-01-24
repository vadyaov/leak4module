#ifndef GROUP_BOX_H
#define GROUP_BOX_H

#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QVBoxLayout>

class GroupBox : public QGroupBox {
  Q_OBJECT
  public:
    GroupBox(const QString& title, QWidget* parent = nullptr) : QGroupBox(title, parent) {
      QRadioButton* select_all = new QRadioButton(tr("All"));
      /* select_all->setChecked(true); */
      const std::vector<std::string> forms {"Molecular Iodine", "Organic Iodine", "Aerosol Iodine", "IRG", "Aerorsols"};

      nucl_form_box.reserve(forms.size());
      for (size_t i = 0; i != forms.size(); ++i) {
        nucl_form_box.push_back(new QCheckBox(tr(forms[i].data())));
      }

      connect(select_all, SIGNAL(clicked(bool)), this, SLOT(AllButtonClicked()));

      QVBoxLayout *vbox = new QVBoxLayout;
      vbox->addWidget(select_all);
      for (size_t i = 0; i != nucl_form_box.size(); ++i) {
        vbox->addWidget(nucl_form_box[i]);
      }
      setLayout(vbox);
    }

    std::vector<int> SelectedForms() const {
      std::vector<int> selected;
      selected.reserve(nucl_form_box.size());

      for (size_t i = 0; i != nucl_form_box.size(); ++i) {
        if (nucl_form_box[i]->isChecked()) {
          selected.push_back(i);
        }
      }

      return selected;
    }

    private slots:
      void AllButtonClicked() {
        QObject* sender = QObject::sender();
        if (sender != nullptr && reinterpret_cast<QRadioButton*>(sender)->isChecked()) {
          for (size_t i = 0; i != nucl_form_box.size(); ++i)
            nucl_form_box[i]->setChecked(true);
        }
      }

  private:
    std::vector<QCheckBox*> nucl_form_box;
};

#endif // GROUP_BOX_H
