cmake_minimum_required(VERSION 3.20)
project(RPN_Calculator
    VERSION 0.1.0
    DESCRIPTION "A modern RPN Calculator built with C++20, CMake, and GitHub Actions"
    LANGUAGES CXX
)

# Настройка стандарта C++ и политик компиляции
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Используем стандартный C++, а не GNU-расширения

# Глобальные флаги компиляции (можно переопределять извне)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Wpedantic -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

# Опция для использования компилятора Clang вместо GCC
option(USE_CLANG "Use Clang compiler" OFF)
if(USE_CLANG)
    set(CMAKE_CXX_COMPILER clang++)
endif()

# Включаем тестирование
enable_testing()

# Сначала создаем СТАТИЧЕСКУЮ БИБЛИОТЕКУ из нашей основной логики
add_library(rpn_lib STATIC src/rpn.cpp)
# Делаем include директорию публичной (доступной для всех, кто линкуется с этой библиотекой)
target_include_directories(rpn_lib PUBLIC include)

# Затем создаем исполняемый файл и линкуем его с библиотекой
add_executable(rpn_calculator src/main.cpp)
# Линкуем исполняемый файл с нашей библиотекой
target_link_libraries(rpn_calculator PRIVATE rpn_lib)

# Добавляем поддиректорию с тестами (после определения rpn_lib!)
add_subdirectory(tests)