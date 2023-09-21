#include "../Model/model.h"
#include "gtest/gtest.h"

TEST(CalculatorTest, TestExpression1) {
  s21::Model model;
  std::string expression = "4/sin(5)^(6-4)";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_TRUE(success);
  EXPECT_NEAR(model.GetCalculationResult(), 4.35002112398, 1e-5);
}

TEST(CalculatorTest, TestExpression2) {
  s21::Model model;
  std::string expression = "3+4*2/(1-5)^2";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_TRUE(success);
  EXPECT_NEAR(model.GetCalculationResult(), 3.5, 1e-5);
}

TEST(CalculatorTest, TestExpression3) {
  s21::Model model;
  std::string expression = "(1+2)*4-3";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_TRUE(success);
  EXPECT_NEAR(model.GetCalculationResult(), 9.0, 1e-5);
}

TEST(CalculatorTest, TestExpression4) {
  s21::Model model;
  std::string expression = "sqrt(9)+2^3";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_TRUE(success);
  EXPECT_EQ(model.GetCalculationResult(), 11.0);
}

TEST(CalculatorTest, TestExpression5) {
  s21::Model model;
  std::string expression = "sin(45)+cos(30)/tan(60)";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_TRUE(success);
  EXPECT_NEAR(model.GetCalculationResult(), 1.33287847209, 1e-5);
}

TEST(CalculatorTest, TestExpression6) {
  s21::Model model;
  std::string expression = "9.87E-4";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_TRUE(success);
  EXPECT_NEAR(model.GetCalculationResult(), 0.000987, 1e-5);
}

TEST(CalculatorTest, TestScientificNotation) {
  s21::Model model;
  std::string expression = "9.87E4";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_TRUE(success);
  EXPECT_DOUBLE_EQ(model.GetCalculationResult(), 9.87E4);
}

TEST(CalculatorTest, TestInvalidScientificNotation) {
  s21::Model model;
  std::string expression = "9.8.7E4";
  bool success = model.ParsingExpressions(expression);
  ASSERT_FALSE(success);
}

TEST(CalculatorTest, TestInvalidExpression1) {
  s21::Model model;
  std::string expression = "4/sin(5)^^(6-4)";
  bool success = model.ParsingExpressions(expression);
  ASSERT_FALSE(success);
}

TEST(CalculatorTest, TestInvalidExpression2) {
  s21::Model model;
  std::string expression = "3++4*2/(1-5)^2";
  bool success = model.ParsingExpressions(expression);
  ASSERT_FALSE(success);
}

TEST(CalculatorTest, TestInvalidExpression3) {
  s21::Model model;
  std::string expression = "sqrt(9)+2^3))";
  bool success = model.ParsingExpressions(expression);
  ASSERT_FALSE(success);
}

TEST(CalculatorTest, TestInvalidExpression4) {
  s21::Model model;
  std::string expression = "sin(45+cos(30)/tan(60)";
  bool success = model.ParsingExpressions(expression);
  ASSERT_FALSE(success);
}

TEST(CalculatorTest, TestInvalid256) {
  s21::Model model;
  std::string expression =
      "sin(45+cos(30)/tan(60)+sin(45+cos(30)/tan(60)+sin(45+cos(30)/"
      "tan(60)+sin(45+cos(30)/tan(60)+sin(45+cos(30)/tan(60)+sin(45+cos(30)/"
      "tan(60)+sin(45+cos(30)/tan(60)+sin(45+cos(30)/tan(60)+sin(45+cos(30)/"
      "tan(60)+sin(45+cos(30)/tan(60)+sin(45+cos(30)/tan(60)+sin(45+cos(30)/"
      "tan(60)+sin(45+cos(30)/tan(60)+sin(45+cos(30)/tan(60)+sin(45+cos(30)/"
      "tan(60)+sin(45+cos(30)/tan(60)+sin(45+cos(30)/tan(60)+sin(45+cos(30)/"
      "tan(60)+sin(45+cos(30)/tan(60)+sin(45+cos(30)/tan(60)+sin(45+cos(30)/"
      "tan(60)";
  bool success = model.ParsingExpressions(expression);
  ASSERT_FALSE(success);
}

TEST(CalculatorTest, UnaryPlusExpression) {
  s21::Model model;
  std::string expression = "(+1)";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_TRUE(success);
  EXPECT_DOUBLE_EQ(model.GetCalculationResult(), 1.0);
}

TEST(CalculatorTest, UnaryMinusExpression) {
  s21::Model model;
  std::string expression = "-(-1)";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_TRUE(success);
  EXPECT_DOUBLE_EQ(model.GetCalculationResult(), 1.0);
}

TEST(CalculatorTest, InvalidExpressionDoublePlus) {
  s21::Model model;
  std::string expression = "1++1";
  bool success = model.ParsingExpressions(expression);
  ASSERT_FALSE(success);
}

TEST(CalculatorTest, TestExpression) {
  s21::Model model;
  std::string expression = "asin(0.5)";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_TRUE(success);
  EXPECT_DOUBLE_EQ(model.GetCalculationResult(), 0.52359877559829882);
}

TEST(CalculatorTest, SinExpression) {
  s21::Model model;
  std::string expression = "sin(x)";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  double x = 1.0;
  model.RewriteToList();
  success = model.Calculations(x);
  ASSERT_TRUE(success);
  double expected = std::sin(x);
  EXPECT_NEAR(model.GetCalculationResult(), expected, 0.00001);
}

TEST(CalculatorTest, InvalidExpressionBinary) {
  s21::Model model;
  std::string expression = "1$1";
  bool success = model.ParsingExpressions(expression);
  ASSERT_FALSE(success);
}

TEST(CalculatorTest, ArccosineOf1) {
  s21::Model model;
  std::string expression = "acos(1)";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_TRUE(success);
  EXPECT_DOUBLE_EQ(model.GetCalculationResult(), 0.0);
}

TEST(CalculatorTest, ArctangentOfMinus1) {
  s21::Model model;
  std::string expression = "atan(-1)";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_TRUE(success);
  EXPECT_NEAR(model.GetCalculationResult(), -0.785398, 1e-6);
}

TEST(CalculatorTest, InvalidExpression) {
  s21::Model model;
  std::string expression = "asca()";
  bool success = model.ParsingExpressions(expression);
  ASSERT_FALSE(success);
}

TEST(CalculatorTest, InvalidExpressionNegativeValue) {
  s21::Model model;
  std::string expression = "sqrt(-1)";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_FALSE(success);
}

TEST(CalculatorTest, InvalidExpressionZeroDivision) {
  s21::Model model;
  std::string expression = "1/0";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_FALSE(success);
}

TEST(CalculatorTest, ComplexExpression) {
  s21::Model model;
  std::string expression = "2^2^2 - 200 / 2";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_TRUE(success);
  EXPECT_DOUBLE_EQ(model.GetCalculationResult(), -84.0);
}

TEST(CalculatorTest, TestPostfixExpression) {
  s21::Model model;
  std::string expression = "(2 2 +)";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_TRUE(success);
  EXPECT_DOUBLE_EQ(model.GetCalculationResult(), 4);
}

TEST(CalculatorTest, ModuloOperation) {
  s21::Model model;
  std::string expression = "10mod4";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_TRUE(success);
  EXPECT_DOUBLE_EQ(model.GetCalculationResult(), 2.0);
}

TEST(CalculatorTest, NaturalLogarithm) {
  s21::Model model;
  std::string expression = "ln(1)";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_TRUE(success);
  EXPECT_DOUBLE_EQ(model.GetCalculationResult(), 0.0);
}

TEST(CalculatorTest, LogarithmBase10) {
  s21::Model model;
  std::string expression = "log(1)";
  bool success = model.ParsingExpressions(expression);
  ASSERT_TRUE(success);
  model.RewriteToList();
  success = model.Calculations(0);
  ASSERT_TRUE(success);
  EXPECT_DOUBLE_EQ(model.GetCalculationResult(), 0.0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
