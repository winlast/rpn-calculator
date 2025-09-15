#include <gtest/gtest.h>
#include "rpn.h"
#include <stdexcept>

TEST(RPNTest, BasicOperations) {
    EXPECT_DOUBLE_EQ(evaluate_rpn("2 3 +"), 5.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("10 5 -"), 5.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("3 4 *"), 12.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("20 4 /"), 5.0);
}

TEST(RPNTest, ComplexExpression) {
    // (15 / (7 - (1 + 1))) * 3 - (2 + (1 + 1))
    EXPECT_NEAR(evaluate_rpn("15 7 1 1 + - / 3 * 2 1 1 + + -"), 5.0, 1e-9);
}

TEST(RPNTest, PowerOperation) { // ТЕСТ ДЛЯ ДОП. ФУНКЦИИ №1
    EXPECT_DOUBLE_EQ(evaluate_rpn("2 3 ^"), 8.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("5 2 ^"), 25.0);
    EXPECT_DOUBLE_EQ(evaluate_rpn("2 0 ^"), 1.0);
}

TEST(RPNTest, DivisionByZero) {
    EXPECT_THROW(evaluate_rpn("1 0 /"), std::invalid_argument);
}

TEST(RPNTest, InvalidOperator) {
    EXPECT_THROW(evaluate_rpn("2 3 $"), std::invalid_argument);
}

TEST(RPNTest, NotEnoughOperands) {
    EXPECT_THROW(evaluate_rpn("2 +"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("+"), std::invalid_argument);
}

TEST(RPNTest, TooManyOperands) {
    EXPECT_THROW(evaluate_rpn("2 3 4 +"), std::invalid_argument);
}