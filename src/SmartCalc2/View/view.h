#ifndef SRC_SMARTCALC2_VIEW_VIEW_H_
#define SRC_SMARTCALC2_VIEW_VIEW_H_

#include <qlineedit.h>

#include <QDesktopServices>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>

#include "../Controller/controller.h"
#include "../QCustomPlot/qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class View : public QMainWindow {
  Q_OBJECT

public:
  View(Controller *controller, QWidget *parent = nullptr);
  ~View();

private slots:

  void on_DotButton_clicked();

  void on_DeleteAllCharsButton_clicked();

  void on_DeleteLastCharButton_clicked();

  void on_PlusButton_clicked();

  void on_MinusButton_clicked();

  void on_MultiplyButton_clicked();

  void on_DivisionButton_clicked();

  void on_SinButton_clicked();

  void on_CosButton_clicked();

  void on_TanButton_clicked();

  void on_AsinButton_clicked();

  void on_AcosButton_clicked();

  void on_LnButton_clicked();

  void on_LogButton_clicked();

  void on_OpenBracketButton_clicked();

  void on_CloseBracketButton_clicked();

  void on_AtanButton_clicked();

  void on_SqrtButton_clicked();

  void on_PowButton_clicked();

  void on_ZeroButton_clicked();

  void on_OneButton_clicked();

  void on_TwoButton_clicked();

  void on_ThreeButton_clicked();

  void on_FourButton_clicked();

  void on_FiveButton_clicked();

  void on_SixButton_clicked();

  void on_SevenButton_clicked();

  void on_EightButton_clicked();

  void on_NineButton_clicked();

  void on_ModButton_clicked();

  void on_ResultButton_clicked();

  void on_XButton_clicked();

  void on_GraphButton_clicked();

  void on_XButton_2_clicked();

  void on_ExpButton_clicked();

private:
  Ui::View *ui_;
  Controller *controller_;

  void ChangeLabel(QLineEdit *textLabel, QString newStr);
};

} // namespace s21
#endif // SRC_SMARTCALC2_VIEW_VIEW_H_
