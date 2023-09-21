#include "controller.h"

s21::Controller::Controller(Model *m) : model_(m) {}
s21::Controller::~Controller() {}

bool s21::Controller::ProcessExpression(std::string &expression, double x) {
  if (!model_->ParsingExpressions(expression))
    return false;

  model_->RewriteToList();

  if (!model_->Calculations(x))
    return false;

  return true;
}

bool s21::Controller::Run(std::string expression, double x) {
  return ProcessExpression(expression, x);
}

double s21::Controller::GetCalculationResult() {
  return model_->GetCalculationResult();
}

void s21::Controller::BuildGraphs(std::string expression, double x_begin,
                                  double x_end) {
  model_->BuildGraphInModel(expression, x_begin, x_end);
}

std::vector<double> s21::Controller::GetXVectorValues() {
  return model_->GetXValues();
}

std::vector<double> s21::Controller::GetYVectorValues() {
  return model_->GetYValues();
}

void s21::Controller::CleanModel() { model_->Refresh(); }