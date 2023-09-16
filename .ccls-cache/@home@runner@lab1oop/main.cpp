#include <cstring>
#include <iostream>
#include <limits>
#include <string>
#include <cmath>

struct Coordinates {
  int x, y;
};

struct Unit {
  int value;
  Coordinates point;
  Unit *next = nullptr;
};

struct Matrix {
  Coordinates size;
  Unit *unit = nullptr;
};

template <class T>

T getNum(T min = std::numeric_limits<T>::min(),
         T max = std::numeric_limits<T>::max()) {
  T val;
  while (true) {
    std::cin >> val;
    if (std::cin.eof()) {
      throw std::runtime_error("find eof");
    } else if (std::cin.bad()) {
      throw std::runtime_error(std::string("failed to read number: ") + strerror(errno));
    } else if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore();
      std::cout << "error. repeat, please" << std::endl;
    } else if (val >= min && val <= max) {
      return val;
    }
  }
}

namespace matrix {
  namespace unit {

    void pushBack(Matrix &matrix, Unit &cell) {
      Unit *cur = matrix.unit;
      Unit *ptr = nullptr;
      while (cur) {
        ptr = cur;
        cur = cur->next;
      }
      ptr->next = &cell;
    }

    void pushFront(Matrix &matrix, Unit &cell) {
      cell.next = matrix.unit;
      matrix.unit = &cell;
    }
  } // namespace unit

  void erase(Matrix &matrix) {
    Unit *ptr = matrix.unit;
    while (ptr) {
      Unit *del_ptr = ptr;
      delete del_ptr;
      ptr = ptr->next;
    }
  }

  void outputFull(Matrix matrix) {
    Unit *ptr = matrix.unit;
    for (int i = 0; i < matrix.size.x; i++) {
      for (int j = 0; j < matrix.size.y; j++) {
        if (j == ptr->point.y && i == ptr->point.x) {
          std::cout << ptr->value << " ";
          ptr = ptr->next;
        } else {
          std::cout << "0 ";
        }
      }
      std::cout << std::endl;
    }
  }

  void outputShort(Matrix matrix) {
    Unit *ptr = matrix.unit;
    while (ptr) { // a : (x,y)
      std::cout << ptr->value << " : (" << ptr->point.x << "," << ptr->point.y << ")" << std::endl;
      ptr = ptr->next;
    }
  }

  Matrix input() {
    Matrix matrix;
    try {
      std::cout << "enter number of columns:" << std::endl; // m: y, j
      matrix.size.y = getNum<int>();
      std::cout << "enter number of rows:" << std::endl; // n: x, i
      matrix.size.x = getNum<int>();
      for (int i = 0; i < matrix.size.x; i++) {
        for (int j = 0; j < matrix.size.y; j++) {
          int val;
          val = getNum<int>();
          if (val == 0) {
            continue;
          }
          Unit *cell = new Unit; //???????
          *cell = {val, {i, j}}; 
          unit::pushBack(matrix, *cell);
        }
      }
    } catch (...) {
      erase(matrix);
    }
    return matrix;
  }

} // namespace matrix

// количество цифр в записи которых превышает среднее количество
// цифр в записи всех элементов данной строки матрицы

bool compFunc(Matrix &matrix, Unit &unit){
  int count = 0;
  double sum = 0;
  Unit *ptr = matrix.unit;
  while (ptr && ptr->point.x != unit.point.x){
    ptr = ptr->next;
  }
  if (!ptr){ return false; }
  while (ptr && ptr->point.x == unit.point.x){
    count++;
    sum += (std::ceil(std::log10(ptr->value)));
  }
  if (std::round(sum/count) < std::ceil(std::log10(unit.value))){
    return true;
  }
  else{
    return 0;
  }
}

int main() {}