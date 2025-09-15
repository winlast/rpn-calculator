#include "rpn.h"

#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>    // для std::pow (возведение в степень)
#include <cctype>   // для std::isdigit
#include <iostream> // для отладки (можно убрать later)

// Вспомогательная функция для разбиения строки на токены
namespace {
std::vector<std::string> tokenize(const std::string& expression) {
    std::vector<std::string> tokens;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Вспомогательная функция для проверки, является ли строка числом
bool is_number(const std::string& s) {
    if (s.empty()) return false;
    
    std::istringstream iss(s);
    double d;
    // Пытаемся прочитать число из строки
    iss >> d;
    // Проверяем, что мы прочитали число и дошли до конца строки
    return !iss.fail() && iss.eof();
}
} // namespace

double evaluate_rpn(const std::string& expression) {
    std::stack<double> stack;
    std::vector<std::string> tokens = tokenize(expression);

    for (const auto& token : tokens) {
        if (is_number(token)) {
            // Преобразуем строку в число и помещаем в стек
            stack.push(std::stod(token));
        } else {
            // Обрабатываем оператор
            if (stack.size() < 2) {
                throw std::invalid_argument("Not enough operands for operator '" + token + "'");
            }

            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            double result = 0.0;

            if (token == "+") {
                result = a + b;
            } else if (token == "-") {
                result = a - b;
            } else if (token == "*" || token == "x") { // Добавим синоним
                result = a * b;
            } else if (token == "/") {
                if (b == 0.0) {
                    throw std::invalid_argument("Division by zero");
                }
                result = a / b;
            } else if (token == "^") { // РЕАЛИЗУЕМ ДОП. ФУНКЦИЮ №1 (Возведение в степень)
                result = std::pow(a, b);
            } else {
                throw std::invalid_argument("Invalid operator: '" + token + "'");
            }
            stack.push(result);
        }
    }

    if (stack.size() != 1) {
        throw std::invalid_argument("Invalid expression: too many operands or missing operators");
    }

    return stack.top();
}