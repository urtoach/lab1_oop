#include <cstring>
#include <iostream>
#include <limits>
#include <string>
#include <cmath>
#include <iomanip>

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
  Unit *head = nullptr;
  Unit *tail = nullptr;
};

template <class T>

T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
  T val;
  while (true) {
    std::cin >> val;
    if (std::cin.eof()) {
      throw std::runtime_error("find eof");
    } 
    else if (std::cin.bad()) {
      throw std::runtime_error(std::string("failed to read number: ") + strerror(errno));
    } 
    else if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore();
      std::cout << "error. repeat" << std::endl;
    } 
    else if (val >= min && val <= max) {
      return val;
    }
    else{
      std::cin.clear();
      std::cin.ignore();
      std::cout << "error. repeat" << std::endl;
    }
  }
}


// количество цифр в записи которых превышает среднее количество
// цифр в записи всех элементов данной строки матрицы

bool compFunc1(Matrix &matrix, Unit &unit){
  int count = 0;
  double sum = 0;
  Unit *ptr = matrix.head;
  if (!ptr){ return false; }
  while (ptr && ptr->point.x != unit.point.x){
    ptr = ptr->next; 
  }
  if (!ptr){ return false; }
  while (ptr && ptr->point.x == unit.point.x){
    count++;
    sum += (std::ceil(std::log10(ptr->value + 1)));
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

bool compFunc2(Matrix &matrix, Unit &unit){
  if (unit.value % 2 == unit.point.y % 2){
    return true;
  }
  return false;
}


namespace matrix {
  namespace unit {

    void pushBack(Matrix &matrix, Unit *cell) {
      try {
        if (matrix.head == nullptr) {
          matrix.head = cell;
          matrix.tail = cell;
        } 
        else {
          matrix.tail->next = cell;
          matrix.tail = cell;
        }
      } 
      catch (const std::exception &e) {
        std::cerr << "error in pushBack: " << e.what() << std::endl;
        throw;
      }
    }
  }
  void erase(Matrix &matrix) {
    try {
      Unit *ptr = matrix.head;
      while (ptr) {
        Unit *del_ptr = ptr;
        ptr = ptr->next;
        delete del_ptr;
      }
      //if (!matrix.unit) { delete matrix.unit; }
      matrix.head = nullptr;
    }
    catch (...) {
      matrix.head = nullptr;
      throw;
    }
  }

  Unit *isExist(Matrix matrix, int x, int y){
    try {
      Unit *ptr = matrix.head;
      while (ptr){
        if (ptr->point.x == x && ptr->point.y == y){
          return ptr;
        }
        ptr = ptr->next;
      }
      return nullptr;
    }
    catch(...) {
      std::cerr << "an error occurred in isExist function." << std::endl;
      return nullptr;
    }
  }
  
  void outputFull(Matrix matrix){
    if (matrix.head == nullptr && (matrix.size.x == 0 || matrix.size.y == 0)){
      std::cout << "there is no matrix" << std::endl;
      return;
    }
    std::cout << "full output:" << std::endl;
    try {
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
    catch (const std::exception &e) {
      std::cerr << "exception caught: " << e.what() << std::endl;
    } 
    catch (...) {
      std::cerr << "unknown exception caught" << std::endl;
    }
  }

  void outputShort(Matrix matrix) {
    if (matrix.head == nullptr && (matrix.size.x == 0 || matrix.size.y == 0)){
      std::cout << "there is no matrix" << std::endl;
      return;
    }
    std::cout << "short output:" << std::endl;
    try {
      if (matrix.head == nullptr){ 
        std::cout << "there is no matrix/the matrix is filled with zeros" << std::endl;
        return;
      }
      Unit *ptr = matrix.head;
      std::cout << "  size (mxn): " << matrix.size.x << "x" << matrix.size.y << std::endl;
      while (ptr) { 
        std::cout << "  " << ptr->value << ": (" << ptr->point.x << "," << ptr->point.y << ")" << std::endl;
        ptr = ptr->next;
      }
    }
    catch (const std::exception &e) {
      std::cerr << "error: " << e.what() << std::endl;
    }
  }

  Matrix input() {
    Matrix matrix;
    try {
      std::cout << "enter number of rows:" << std::endl;
      matrix.size.x = getNum<int>(1);
      std::cout << "enter number of columns:" << std::endl;
      matrix.size.y = getNum<int>(1);
      for (int i = 0; i < matrix.size.x; i++) {
        for (int j = 0; j < matrix.size.y; j++) {
          int val;
          std::cout << "enter num:" << std::endl;
          val = getNum<int>(0);
          if (val == 0) {
            continue;
          }
          Unit *cell = new Unit;
          *cell = {val, {i, j}, nullptr}; 
          unit::pushBack(matrix, cell);
        }
      }
    }
    catch (...) {
      erase(matrix);
      throw;
    }
    return matrix;
  }

  void checkCoord(Matrix &matrix){
    try {
      Unit *ptr = matrix.head;
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
      ptr = matrix.head;
      while(ptr){
        if (ptr->point.y + 1 > max){
          max = ptr->point.y + 1;
        }
        ptr = ptr->next;
      }
      matrix.size.y = max;
    }
    catch (...) {
      std::cerr << "error" << std::endl;
    }
  }
  
  Matrix newMatrix(Matrix &init_matrix, bool (callback(Matrix&, Unit&))){
    Matrix new_matrix;
    new_matrix.size = init_matrix.size;
    try {
      Unit *ptr = init_matrix.head;
      while (ptr){
        if (callback(init_matrix, *ptr)){
          Unit *cell = new Unit;
          *cell = {ptr->value, {ptr->point.x, ptr->point.y}, nullptr};
          unit::pushBack(new_matrix, cell);
        }
        ptr = ptr->next;
      }
      //checkCoord(new_matrix);
    }
    catch (...) {
      erase(new_matrix);
      throw;
    }
    return new_matrix;
  }
  
} // namespace matrix

int main() {
  Matrix matrix;
  while (true){
    try{
      std::cout << "enter new matrix" << std::endl;
      matrix = matrix::input();
      matrix::outputFull(matrix);
      //matrix::outputShort(matrix);
    
      std::cout << "form a new matrix:" << std::endl;
      std::cout << "\t[the function forms a new matrix by\n\tplacing in its i-th row those elements from\n\tthe i-th row of the original matrix\n\twhose entry exceeds the average number\n\tdigits in the record of all\n\telements of a given row of the matrix]" << std::endl;
    
      Matrix new_matrix = matrix::newMatrix(matrix, compFunc1);
      matrix::outputFull(new_matrix);
      matrix::erase(new_matrix);

      std::cout << "form a new matrix:" << std::endl;
      std::cout << "\t[the function forms a new matrix by\n\tplacing in its i-th row those elements from\n\tthe i-th row of the original matrix\n\twhose parity coincides with the parity\n\tof the column in which it is located]" << std::endl;

      new_matrix = matrix::newMatrix(matrix, compFunc2);
      matrix::outputFull(new_matrix);
      matrix::erase(new_matrix);
      
      matrix::erase(matrix);
    
      std::cout << "are u want to continue?\nyes/no = 1/0" << std::endl;
      if (!getNum(0,1)){ break; }
    }
    catch (const std::exception& e) {
      std::cerr << "an exception occurred: " << e.what() << std::endl;
      break;
    }
  }
}
