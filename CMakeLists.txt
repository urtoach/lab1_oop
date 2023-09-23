# установка версии CMake
cmake_minimum_required(VERSION 3.16)

# название проекта (обязательно)
project(ooplab1)

# установка стандарта языка - C++20
set(CMAKE_CXX_STANDARD 20)

# установка флагов компилятора: CMAKE_CXX_FLAGS += -Wall -Wextra
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# создание библиотеки prog1
add_library(lab1 lab1.h lab1.cpp)

# подключение библиотеки prog1 ко всем таргетам, создаваемым далее
# альтернатива: target_link_libraries(main prog1)
link_libraries(lab1)

# создание исполняемого файла
add_executable(lab1main lab1main.cpp)

# для сборки из консоли:
#
# mkdir build   # создание директории для файлов сборки
# cd build      # переход в директорию сборки
# cmake ..      # генерация файлов сборки на основе CMakeLists.txt
# make          # сборка проекта
