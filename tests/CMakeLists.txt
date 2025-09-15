# Настраиваем загрузку GoogleTest через FetchContent (современный способ в CMake)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Создаем исполняемый файл для тестов
add_executable(rpn_tests test_rpn.cpp)
# Линкуем его с GoogleTest и нашей основной библиотекой rpn_lib
target_link_libraries(rpn_tests PRIVATE gtest_main rpn_lib) # <- КЛЮЧЕВОЕ ИЗМЕНЕНИЕ: добавлен rpn_lib
target_include_directories(rpn_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
# Добавляем тест в CTest
add_test(NAME rpn_tests COMMAND rpn_tests)