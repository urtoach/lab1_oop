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


namespace matrix {
  namespace unit {

    void pushBack(Matrix &matrix, Unit &cell) {
      Unit *cur = matrix.unit;
      Unit *prev = cur;
      while (cur) {
        prev = cur;
        cur = cur->next;
      }
      if (prev == nullptr){ matrix.unit = &cell; }
      else{ prev->next = &cell; }
    }

    void pushFront(Matrix &matrix, Unit &cell) {
      cell.next = matrix.unit;
      matrix.unit = &cell;
    }
  } // namespace unit

  void erase(Matrix &matrix) {
    try {
      Unit *ptr = matrix.unit;
      while (ptr) {
        Unit *del_ptr = ptr;
        ptr = ptr->next;
        delete del_ptr;
      }
    }
    catch(...){
      std::cout << "wataheeeeeeeeell" << std::endl;
    }
    //delete &matrix;
  }

  /*void outputFull(Matrix matrix) {
    std::cout << "full output:" << std::endl;
    Unit *ptr = matrix.unit;
    try{
      for (int i = 0; i < matrix.size.x; i++){
        for (int j = 0; j < matrix.size.y; j++){
          if (!ptr){ throw; }
          if (i == ptr->point.x && j == ptr->point.y){
            std::cout << ptr->value << " ";
            ptr = ptr->next;
          }
          else{
            std::cout << "0 ";
          }
          std::cout << std::endl;
        }
      }
    }
    catch(...){
      std::cout << "blya" << std::endl;
    }
  }*/

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
    Unit *ptr = matrix.unit;
    std::cout << "  size (mxn): " << matrix.size.x << "x" << matrix.size.y << std::endl;
    while (ptr) { // a: (x,y)
      std::cout << "  " << ptr->value << ": (" << ptr->point.x << "," << ptr->point.y << ")" << std::endl;
      ptr = ptr->next;
    }
  }

  Matrix input() {
    Matrix matrix;// = new Matrix;
    try {
      std::cout << "enter number of rows:" << std::endl; // n: x, i
      matrix.size.x = getNum<int>();
      std::cout << "enter number of columns:" << std::endl; // m: y, j
      matrix.size.y = getNum<int>();
      for (int i = 0; i < matrix.size.x; i++) {
        for (int j = 0; j < matrix.size.y; j++) {
          int val;
          std::cout << "enter num:" << std::endl;
          val = getNum<int>();
          if (val == 0) {
            continue;
          }
          //break;
          
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
  }
  
  Matrix newMatrix(Matrix &init_matrix, bool (*callback(Matrix&, Unit&))){
    Matrix *new_matrix = new Matrix;
    new_matrix->size.x = init_matrix.size.x;
    Unit *ptr = init_matrix.unit;
    while (ptr){
      if (callback(init_matrix, *ptr)){
        unit::pushBack(init_matrix, *ptr);
      }
      ptr = ptr->next;
    }
    checkCoord(*new_matrix);
    return *new_matrix;
  }
  
} // namespace matrix




int main() {
  Matrix matrix = matrix::input();
  std::cout << "vrode vse ok" << std::endl;
  matrix::outputShort(matrix);
  std::cout << "==============" << std::endl;
  matrix::outputFull(matrix);
  matrix::erase(matrix);
  std::cout << "vrode udalilos'" << std::endl;
}