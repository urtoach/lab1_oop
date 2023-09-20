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

T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
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


// количество цифр в записи которых превышает среднее количество
// цифр в записи всех элементов данной строки матрицы

bool compFunc(Matrix &matrix, Unit &unit){
  int count = 0;
  double sum = 0;
  Unit *ptr = matrix.unit;
  if (!ptr){ return false; }
  while (ptr && ptr->point.x != unit.point.x){
    ptr = ptr->next; 
  }
  if (!ptr){ return false; }
  while (ptr && ptr->point.x == unit.point.x){
    count++;
    sum += (std::ceil(std::log10(ptr->value)));
    ptr = ptr->next;
  }
  sum += (matrix.size.x - count);
  if (std::round(sum/matrix.size.x) < std::ceil(std::log10(unit.value + 1))){
    return true;
  }
  else{
    return 0;
  }
}


namespace matrix {
  namespace unit {

    void pushBack(Matrix &matrix, Unit *cell) {
      if (matrix.unit == nullptr) {
        matrix.unit = cell;
      } 
      else {
        Unit *cur = matrix.unit;
        while (cur->next) {
          cur = cur->next;
        }
        cur->next = cell;
      }
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
        ptr = ptr->next;
        delete del_ptr;
      }
      //if (!matrix.unit) { delete matrix.unit; }
      matrix.unit = nullptr;
  }

  Unit *isExist(Matrix matrix, int x, int y){
    Unit *ptr = matrix.unit;
    while (ptr){
      if (ptr->point.x == x && ptr->point.y == y){
        return ptr;
      }
      ptr = ptr->next;
    }
    return nullptr;
  }
  
  void outputFull(Matrix matrix){
    std::cout << "full output:" << std::endl;
    for (int i = 0; i < matrix.size.x; i++){
      for (int j = 0; j < matrix.size.y; j++){
        Unit *ptr = isExist(matrix, i, j);
        if (ptr){
          std::cout << ptr->value << " ";
        }
        else{
          std::cout << "0 ";
        }
      }
      std::cout << std::endl;
    }
  }

  void outputShort(Matrix matrix) {
    std::cout << "short output:" << std::endl;
    if (matrix.unit == nullptr){ 
      std::cout << "ur table table consists entirely of zeros" << std::endl;
      return;
    }
    Unit *ptr = matrix.unit;
    std::cout << "  size (mxn): " << matrix.size.x << "x" << matrix.size.y << std::endl;
    while (ptr) { 
      std::cout << "  " << ptr->value << ": (" << ptr->point.x << "," << ptr->point.y << ")" << std::endl;
      ptr = ptr->next;
    }
  }

  Matrix input() {
    Matrix matrix;
    try {
      std::cout << "enter number of rows:" << std::endl;
      matrix.size.x = getNum<int>();
      if (matrix.size.x <= 0){ throw 0; }
      std::cout << "enter number of columns:" << std::endl;
      matrix.size.y = getNum<int>();
      if (matrix.size.y <= 0){ throw 0; }
      for (int i = 0; i < matrix.size.x; i++) {
        for (int j = 0; j < matrix.size.y; j++) {
          int val;
          std::cout << "enter num:" << std::endl;
          val = getNum<int>();
          if (val == 0) {
            continue;
          }
          Unit *cell = new Unit;
          *cell = {val, {i, j}, nullptr}; 
          unit::pushBack(matrix, cell);
        }
      }
    }
    catch(int){
      std::cout << "it seems like the table dimensions should be positive" << std::endl;
    }
    catch (...) {
      erase(matrix);
      throw;
    }
    return matrix;
  }

  void checkCoord(Matrix &matrix){
    Unit *ptr = matrix.unit;
    int count = 0;
    int checker = 0;
    while (ptr){
      if (ptr->point.x == checker){
        ptr->point.y = count;
        count++;
        ptr = ptr->next;
      }
      else{
        count = 0;
        checker++;
      }
      if (checker > matrix.size.x){ break; }
    }
    int max = 1;
    ptr = matrix.unit;
    while(ptr){
      if (ptr->point.y + 1 > max){
        max = ptr->point.y + 1;
      }
      ptr = ptr->next;
    }
    matrix.size.y = max;
  }
  
  Matrix newMatrix(Matrix &init_matrix, bool (callback(Matrix&, Unit&))){
    Matrix new_matrix;
    new_matrix.size.x = init_matrix.size.x;
    Unit *ptr = init_matrix.unit;
    while (ptr){
      if (callback(init_matrix, *ptr)){
        Unit *cell = new Unit;
        *cell = {ptr->value, {ptr->point.x, ptr->point.y}, nullptr};
        unit::pushBack(new_matrix, cell);
      }
      ptr = ptr->next;
    }
    checkCoord(new_matrix);
    return new_matrix;
  }
  
} // namespace matrix




int main() {
  Matrix matrix = matrix::input();
  matrix::outputShort(matrix);
  std::cout << "====================" << std::endl;
  matrix::outputFull(matrix);
  Matrix new_matrix = matrix::newMatrix(matrix, compFunc);
  std::cout << "====================" << std::endl;
  matrix::outputShort(new_matrix);
  matrix::erase(matrix);
  matrix::erase(new_matrix);
  //delete &matrix;
}