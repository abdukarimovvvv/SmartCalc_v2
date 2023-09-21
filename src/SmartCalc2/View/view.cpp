#include "view.h"

#include <QMessageBox>

#include "ui_view.h"

using namespace s21;

View::View(Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::View) {
  this->controller_ = controller;
  setFixedSize(1122, 522);
  ui_->setupUi(this);
}

View::~View() { delete ui_; }

void View::ChangeLabel(QLineEdit *textLabel, QString newStr) {
  if (textLabel->text() == "0") {
    textLabel->setText(newStr);
  } else {
    textLabel->setText(textLabel->text() + newStr);
  }
}

void View::on_DotButton_clicked() { ChangeLabel(ui_->Input, "."); }

void View::on_DeleteAllCharsButton_clicked() { ui_->Input->setText("0"); }

void View::on_DeleteLastCharButton_clicked() {
  std::string s = ui_->Input->text().toStdString();
  char *s1 = &s[0];
  char new_s[256] = {0};
  int len = std::strlen(s1);
  if (len > 1) {
    std::strncpy(new_s, s1, len - 1);
    QString remains = QString::fromStdString(new_s);
    ui_->Input->setText(remains);
  } else
    ui_->Input->setText("0");
}

void View::on_PlusButton_clicked() { ChangeLabel(ui_->Input, "+"); }

void View::on_MinusButton_clicked() { ChangeLabel(ui_->Input, "-"); }

void View::on_MultiplyButton_clicked() { ChangeLabel(ui_->Input, "*"); }

void View::on_DivisionButton_clicked() { ChangeLabel(ui_->Input, "/"); }

void View::on_SinButton_clicked() { ChangeLabel(ui_->Input, "sin("); }

void View::on_CosButton_clicked() { ChangeLabel(ui_->Input, "cos("); }

void View::on_TanButton_clicked() { ChangeLabel(ui_->Input, "tan("); }

void View::on_AsinButton_clicked() { ChangeLabel(ui_->Input, "asin("); }

void View::on_AcosButton_clicked() { ChangeLabel(ui_->Input, "acos("); }

void View::on_LnButton_clicked() { ChangeLabel(ui_->Input, "ln("); }

void View::on_LogButton_clicked() { ChangeLabel(ui_->Input, "log("); }

void View::on_OpenBracketButton_clicked() { ChangeLabel(ui_->Input, "("); }

void View::on_CloseBracketButton_clicked() { ChangeLabel(ui_->Input, ")"); }

void View::on_AtanButton_clicked() { ChangeLabel(ui_->Input, "atan("); }

void View::on_SqrtButton_clicked() { ChangeLabel(ui_->Input, "sqrt("); }

void View::on_PowButton_clicked() { ChangeLabel(ui_->Input, "^"); }

void View::on_ZeroButton_clicked() { ChangeLabel(ui_->Input, "0"); }

void View::on_OneButton_clicked() { ChangeLabel(ui_->Input, "1"); }

void View::on_TwoButton_clicked() { ChangeLabel(ui_->Input, "2"); }

void View::on_ThreeButton_clicked() { ChangeLabel(ui_->Input, "3"); }

void View::on_FourButton_clicked() { ChangeLabel(ui_->Input, "4"); }

void View::on_FiveButton_clicked() { ChangeLabel(ui_->Input, "5"); }

void View::on_SixButton_clicked() { ChangeLabel(ui_->Input, "6"); }

void View::on_SevenButton_clicked() { ChangeLabel(ui_->Input, "7"); }

void View::on_EightButton_clicked() { ChangeLabel(ui_->Input, "8"); }

void View::on_NineButton_clicked() { ChangeLabel(ui_->Input, "9"); }

void View::on_ModButton_clicked() { ChangeLabel(ui_->Input, "mod"); }

void View::on_XButton_2_clicked() { ChangeLabel(ui_->Input, "x"); }

void View::on_ExpButton_clicked() { ChangeLabel(ui_->Input, "E"); }

void View::on_ResultButton_clicked() {
  controller_->CleanModel();

  std::string expression = ui_->Input->text().toStdString();

  std::replace(expression.begin(), expression.end(), ',', '.');

  double result = 0;
  bool success = controller_->Run(expression, 0);
  if (success) {
    result = controller_->GetCalculationResult();

    QString result_expression = QString::number(result, 'g', 15);
    ui_->Input->setText(result_expression);
  } else {
    ui_->Input->setText("ERROR");
  }
}

void View::on_XButton_clicked() {
  controller_->CleanModel();

  std::string expression = ui_->Input->text().toStdString();


  std::replace(expression.begin(), expression.end(), ',', '.');

  double inputOfX = ui_->InputForX->value();
  if (ui_->Input->text().contains('x')) {
    bool success = controller_->Run(expression, inputOfX);
    if (success) {
      double result = 0;
      result = controller_->GetCalculationResult();
      QString result_expression = QString::number(result, 'g', 99);
      ui_->Input->setText(result_expression);
    } else {
      ui_->Input->setText("ERROR");
    }
  }
}


void View::on_GraphButton_clicked() {
  controller_->CleanModel();

  ui_->widget->clearGraphs();

  std::string expression = ui_->Input->text().toStdString();

  double x_begin = ui_->spinBoxXBegin->text().toDouble();
  double x_end = ui_->spinBoxXEnd->text().toDouble();
  double y_begin = ui_->spinBoxYBegin->text().toDouble();
  double y_end = ui_->spinBoxYEnd->text().toDouble();

  ui_->widget->xAxis->setRange(x_begin, x_end);

  controller_->BuildGraphs(expression, x_begin, x_end);

  std::vector<double> x_values_std_vector = controller_->GetXVectorValues();

  std::vector<double> y_values_std_vector = controller_->GetYVectorValues();

  QVector<double> x_values_vector(x_values_std_vector.begin(),
                                  x_values_std_vector.end());
  QVector<double> y_values_vector(y_values_std_vector.begin(),
                                  y_values_std_vector.end());

  ui_->widget->yAxis->setRange(y_begin, y_end);
  ui_->widget->addGraph();
  ui_->widget->graph(0)->setData(x_values_vector, y_values_vector);

  ui_->widget->replot();
}

