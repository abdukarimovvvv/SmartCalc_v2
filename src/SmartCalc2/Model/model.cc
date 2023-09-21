#include "model.h"

s21::Model::Model() : calculation_result_(0) {}

s21::Model::~Model() {}

bool s21::Model::CheckIsSign(char c) {
  return (c == PLUS || c == MINUS || c == MULTIPLICATION || c == DIVISION ||
          c == POW);
}

bool s21::Model::CheckIsOperation(char c) {
  return (c == PLUS || c == MINUS || c == MULTIPLICATION || c == DIVISION ||
          c == POW || c == SIN || c == COS || c == TAN || c == SQRT ||
          c == ASIN || c == ACOS || c == ATAN || c == MOD || c == LN ||
          c == LOG || c == UNARY_PLUS || c == UNARY_MINUS);
}

void s21::Model::FunctionInputIterator(std::string::iterator &i,
                                       std::string &temp) {
  if (*i >= '0' && *i <= '9') {
    while (*i >= '0' && *i <= '9') {
      temp += *i;
      i++;
    }
  }
}

double s21::Model::ScanDouble(std::string::iterator &i, bool &status) {
  std::string temp;
  int dotCounter = 0;
  while ((*i >= '0' && *i <= '9') || *i == '.') {
    if (*i == '.')
      dotCounter++;
    temp += *i;
    i++;
  }

  if (dotCounter <= 1) {
    if (*i == 'E') {
      temp += *i;
      i++;
      if (*i == PLUS || *i == MINUS) {
        temp += *i;
        i++;
        FunctionInputIterator(i, temp);
      } else
        FunctionInputIterator(i, temp);
    }
    i--;
    return std::stod(temp);
  } else {
    status = false;
  }
  return 0;
}

int s21::Model::GetPriority(char c) {
  int priority = -1;
  if (c == 'x' || (c >= '0' && c <= '9')) {
    priority = 0;
  } else if (c == PLUS || c == MINUS || c == UNARY_MINUS || c == UNARY_PLUS) {
    priority = 1;
  } else if (c == MULTIPLICATION || c == DIVISION || c == MOD) {
    priority = 2;
  } else if (c == POW) {
    priority = 3;
  } else if (c == COS || c == SIN || c == TAN || c == ACOS || c == ASIN ||
             c == ATAN || c == SQRT || c == LN || c == LOG) {
    priority = 4;
  }
  return priority;
}

bool s21::Model::ReadFunctionName(std::string::iterator &i,
                                  std::stack<Node> &stackForSigns) {
  bool isCorrectFlag = true;
  std::string temp;
  while (islower(*i)) {
    temp += *i;
    i++;
  }
  if (temp == "cos") {
    stackForSigns.push(Node(0, COS, false, GetPriority(COS)));
  } else if (temp == "sin") {
    stackForSigns.push(Node(0, SIN, false, GetPriority(SIN)));
  } else if (temp == "tan") {
    stackForSigns.push(Node(0, TAN, false, GetPriority(TAN)));
  } else if (temp == "acos") {
    stackForSigns.push(Node(0, ACOS, false, GetPriority(ACOS)));
  } else if (temp == "asin") {
    stackForSigns.push(Node(0, ASIN, false, GetPriority(ASIN)));
  } else if (temp == "atan") {
    stackForSigns.push(Node(0, ATAN, false, GetPriority(ATAN)));
  } else if (temp == "sqrt") {
    stackForSigns.push(Node(0, SQRT, false, GetPriority(SQRT)));
  } else if (temp == "ln") {
    stackForSigns.push(Node(0, LN, false, GetPriority(LN)));
  } else if (temp == "log") {
    stackForSigns.push(Node(0, LOG, false, GetPriority(LOG)));
  } else if (temp == "mod") {
    stackForSigns.push(Node(0, MOD, false, 2));
  } else {
    isCorrectFlag = false;
  }
  i--;
  return isCorrectFlag;
}

bool s21::Model::ScanSign(std::string::iterator &i,
                          std::stack<Node> &stackForSigns, char lastChar) {
  if (CheckIsSign(lastChar))
    return false;
  if (lastChar != 'x' && lastChar != CLOSE_BRACKET &&
      !(lastChar >= '0' && lastChar <= '9')) {
    if (*i == PLUS) {
      *i = UNARY_PLUS;
    } else if (*i == MINUS) {
      *i = UNARY_MINUS;
    }
  }
  if (!stackForSigns.empty() && stackForSigns.top().GetSign() == POW &&
      *i == POW) {
    stackForSigns.push(Node(0, POW, false, GetPriority(POW)));
  } else if (!stackForSigns.empty()) {
    if (GetPriority(*i) > stackForSigns.top().GetPriority()) {
      stackForSigns.push(Node(0, *i, false, GetPriority(*i)));
    } else {
      Node tempNode;
      while (!stackForSigns.empty() &&
             GetPriority(*i) <=
                 (tempNode = stackForSigns.top()).GetPriority()) {
        stackForSigns.pop();
        stack_for_notation_.push(tempNode);
      }
      stackForSigns.push(Node(0, *i, false, GetPriority(*i)));
    }
  } else {
    stackForSigns.push(Node(0, *i, false, GetPriority(*i)));
  }
  return true;
}

bool s21::Model::IsBalanced(const std::string &str) {
  int count = 0;

  for (char ch : str) {
    if (ch == OPEN_BRACKET) {
      count++;
    } else if (ch == CLOSE_BRACKET) {
      count--;
      if (count < 0) {
        return false;
      }
    }
  }

  return count == 0;
}

void s21::Model::SkipSpaces(std::string::iterator &i) {
  while (*i == ' ') {
    *i++;
  }
}

bool s21::Model::ParsingExpressions(std::string expression) {
  std::stack<Node> stackForSigns;
  bool status = true;
  if (IsBalanced(expression)) {
    status = true;
  } else {
    return false;
  }
  char lastChar = EMPTY_SIGN;
  for (auto i = expression.begin(); i != expression.end() && status; i++) {
    SkipSpaces(i);
    if (*i == OPEN_BRACKET && *(i + 1) == CLOSE_BRACKET) {
      return false;
    }

    double d = 0;
    if (*i >= '0' && *i <= '9') {
      d = ScanDouble(i, status);
      stack_for_notation_.push(Node(d, EMPTY_SIGN, false, 0));
    } else if (CheckIsSign(*i)) {
      status = ScanSign(i, stackForSigns, lastChar);
    } else if (*i == 'x') {
      stack_for_notation_.push(Node(0, EMPTY_SIGN, true, 0));
    } else if (islower(*i)) {
      ReadFunctionName(i, stackForSigns);
    } else if (*i == OPEN_BRACKET) {
      stackForSigns.push(Node(0, OPEN_BRACKET, false, 0));
    } else if (*i == CLOSE_BRACKET) {
      Node temp;
      while (!stackForSigns.empty() &&
             (temp = stackForSigns.top()).GetSign() != OPEN_BRACKET) {
        stack_for_notation_.push(temp);
        stackForSigns.pop();
      }
      stackForSigns.pop();
    } else {
      status = false;
    }
    lastChar = *i;
  }

  while (!stackForSigns.empty()) {
    Node temp = stackForSigns.top();
    stack_for_notation_.push(temp);
    stackForSigns.pop();
  }

  return status;
}

void s21::Model::RewriteToList() {
  while (!stack_for_notation_.empty()) {
    rewritten_stack_.push_back(stack_for_notation_.top());
    stack_for_notation_.pop();
  }
  rewritten_stack_.reverse();
}

void s21::Model::SetCalculationResult(double value) {
  calculation_result_ = value;
}

double s21::Model::GetCalculationResult() { return calculation_result_; }

bool s21::Model::CheckIsNodeValue(Node node) {
  return (!node.GetIsX() && node.GetSign() == EMPTY_SIGN &&
          node.GetPriority() == 0);
}

bool s21::Model::ProcessBinaryOperations(std::list<double> &hasDoubles,
                                         char sign) {
  if (hasDoubles.size() < 2)
    return false;

  double result = 0.0;
  double b = hasDoubles.back();
  hasDoubles.pop_back();
  double a = hasDoubles.back();
  hasDoubles.pop_back();

  if (sign == PLUS) {
    result = a + b;
  } else if (sign == MINUS) {
    result = a - b;
  } else if (sign == MULTIPLICATION) {
    result = a * b;
  } else if (sign == DIVISION && b != 0) {
    result = a / b;
  } else if (sign == POW) {
    result = pow(a, b);
  } else if (sign == MOD && b != 0) {
    result = fmod(a, b);
  } else {
    return false;
  }
  hasDoubles.push_back(result);
  return true;
}

bool s21::Model::ProcessUnaryOperations(std::list<double> &hasDoubles,
                                        char sign) {
  if (hasDoubles.empty())
    return false;

  double result;
  double x = hasDoubles.back();
  hasDoubles.pop_back();

  if (sign == UNARY_MINUS) {
    result = -x;
  } else if (sign == UNARY_PLUS) {
    result = x;
  } else if (sign == COS) {
    result = cos(x);
  } else if (sign == SIN) {
    result = sin(x);
  } else if (sign == TAN) {
    result = tan(x);
  } else if (sign == ACOS && x >= -1 && x <= 1) {
    result = acos(x);
  } else if (sign == ASIN && x >= -1 && x <= 1) {
    result = asin(x);
  } else if (sign == ATAN) {
    result = atan(x);
  } else if (sign == SQRT && x >= 0) {
    result = sqrt(x);
  } else if (sign == LN && x > 0) {
    result = log(x);
  } else if (sign == LOG && x > 0) {
    result = log10(x);
  } else {
    return false;
  }

  hasDoubles.push_back(result);
  return true;
}

bool s21::Model::CheckIsX(Node node) { return node.GetIsX(); }

bool s21::Model::Calculations(double x) {
  bool status = true;
  std::list<double> hasDoubles;

  for (auto i = rewritten_stack_.begin(); i != rewritten_stack_.end() && status;
       ++i) {
    if (CheckIsNodeValue(*i)) {
      hasDoubles.push_back((*i).GetValue());
    }
    if (CheckIsOperation((*i).GetSign())) {
      char sign = (*i).GetSign();
      if (sign == PLUS || sign == MINUS || sign == MULTIPLICATION ||
          sign == DIVISION || sign == POW || sign == MOD) {
        status = ProcessBinaryOperations(hasDoubles, sign);
      } else if (sign == COS || sign == SIN || sign == TAN || sign == ACOS ||
                 sign == ASIN || sign == ATAN || sign == SQRT || sign == LN ||
                 sign == LOG || sign == UNARY_PLUS || sign == UNARY_MINUS) {
        status = ProcessUnaryOperations(hasDoubles, sign);
      }
    }
    if (CheckIsX(*i)) {
      hasDoubles.push_back(x);
    }
  }
  if (hasDoubles.size() > 1)
    status = false;
  if (status)
    calculation_result_ = hasDoubles.back();
  return status;
}

void s21::Model::BuildGraphInModel(std::string expression, double x_begin,
                                   double x_end) {
  double h = 0.0099;

  bool success = ParsingExpressions(expression);
  RewriteToList();

  for (double x = x_begin; x <= x_end; x += h) {
    if (success && Calculations(x)) {
      x_values_.push_back(x);
      y_values_.push_back(calculation_result_);
    }
  }
}

std::vector<double> s21::Model::GetXValues() { return x_values_; }

std::vector<double> s21::Model::GetYValues() { return y_values_; }

void s21::Model::CleanStack(std::stack<Node> stack_for_notation_) {
  while (!stack_for_notation_.empty()) {
    stack_for_notation_.pop();
  }
}

void s21::Model::Refresh() {
  //  clean stack
  CleanStack(stack_for_notation_);
  rewritten_stack_.clear();
  calculation_result_ = 0;
  x_values_.clear();
  y_values_.clear();
}
