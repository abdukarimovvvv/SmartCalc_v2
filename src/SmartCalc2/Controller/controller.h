#ifndef SRC_SMARTCALC2_CONTROLLER_CONTROLLER_H_
#define SRC_SMARTCALC2_CONTROLLER_CONTROLLER_H_

#include "../Model/model.h"

namespace s21 {
class Controller {
public:
  Controller(Model *m);
  ~Controller();

  bool Run(std::string expression, double x);

  double GetCalculationResult();

  void BuildGraphs(std::string expression, double x_begin, double x_end);

  std::vector<double> GetXVectorValues();

  std::vector<double> GetYVectorValues();

  void CleanModel();

private:
  Model *model_;

  bool ProcessExpression(std::string &expression, double x);
};
} // namespace s21
#endif // SRC_SMARTCALC2_CONTROLLER_CONTROLLER_H_