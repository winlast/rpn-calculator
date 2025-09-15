#include <iostream>
#include "rpn.h"
#include <stdexcept>

int main() {
    std::string expression;
    
    std::cout << "=== RPN Calculator (C++20, CMake, GitHub Actions) ===\n";
    std::cout << "Operators: +, -, *, /, ^ (power)\n";
    std::cout << "Example: '2 3 ^ 5 +' => (2^3) + 5 = 13\n";
    std::cout << "Enter 'quit' to exit.\n" << std::endl;

    while (true) {
        std::cout << "Enter RPN expression: ";
        std::getline(std::cin, expression);

        if (expression == "quit" || expression == "exit") {
            break;
        }

        // Удаляем пробелы в начале и конце
        size_t start = expression.find_first_not_of(" \t");
        if (start == std::string::npos) {
            std::cout << "Empty expression. Try again." << std::endl;
            continue;
        }
        size_t end = expression.find_last_not_of(" \t");
        expression = expression.substr(start, end - start + 1);

        try {
            double result = evaluate_rpn(expression);
            std::cout << "Result: " << result << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        std::cout << "---" << std::endl;
    }
    return 0;
}