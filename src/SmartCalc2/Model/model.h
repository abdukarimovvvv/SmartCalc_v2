#ifndef SRC_SMARTCALC2_MODEL_MODEL_H_
#define SRC_SMARTCALC2_MODEL_MODEL_H_

#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <list>
#include <regex>
#include <stack>
#include <string>

namespace s21 {
class Model {
public:
  enum MathOperatorAndSigns {
    EMPTY_SIGN = '\0',
    COS = 'c',
    SIN = 's',
    TAN = 't',

    ACOS = '1',
    ASIN = '2',
    ATAN = '3',

    SQRT = 'q',

    LN = '5',
    LOG = 'l',

    MOD = 'm',

    OPEN_BRACKET = '(',
    CLOSE_BRACKET = ')',

    UNARY_PLUS = '&',
    UNARY_MINUS = '@',

    POW = '^',

    MINUS = '-',
    PLUS = '+',

    DIVISION = '/',
    MULTIPLICATION = '*'
  };
  Model();

  ~Model();

  bool Calculations(double x);

  bool ParsingExpressions(std::string expression);

  void RewriteToList();

  void SetCalculationResult(double value);

  double GetCalculationResult();

  void BuildGraphInModel(std::string expression, double x_begin, double x_end);

  std::vector<double> GetXValues();

  std::vector<double> GetYValues();

  void Refresh();

private:
  class Node {
  public:
    Node() : value_(0), sign_(EMPTY_SIGN), is_x_(false), priority_(-1) {}

    Node(double value, char sign, bool isX, int priority)
        : value_(value), sign_(sign), is_x_(isX), priority_(priority) {}

    double GetValue() const { return value_; }

    bool GetIsX() const { return is_x_; }

    int GetPriority() const { return priority_; }

    char GetSign() const { return sign_; }

  private:
    double value_;
    char sign_;
    bool is_x_;
    int priority_;
  };

  std::stack<Node> stack_for_notation_;

  std::list<Node> rewritten_stack_;

  double calculation_result_;

  std::vector<double> x_values_, y_values_;

  bool CheckIsSign(char c);

  bool CheckIsOperation(char c);

  void FunctionInputIterator(std::string::iterator &i, std::string &temp);

  double ScanDouble(std::string::iterator &i, bool &status);

  int GetPriority(char c);

  bool CheckIsAlpha(char c);

  bool ReadFunctionName(std::string::iterator &i,
                        std::stack<Node> &stackForSigns);

  bool ScanSign(std::string::iterator &i, std::stack<Node> &stackForSigns,
                char lastChar);

  bool IsBalanced(const std::string &str);

  void SkipSpaces(std::string::iterator &i);

  bool CheckIsNodeValue(Node node);

  bool ProcessBinaryOperations(std::list<double> &hasDoubles, char sign);

  bool ProcessUnaryOperations(std::list<double> &hasDoubles, char sign);

  bool CheckIsX(Node node);
  void CleanStack(std::stack<Node> stack_for_notation_);
};

} // namespace s21

#endif // SRC_SMARTCALC2_MODEL_MODEL_H_