#include <iostream>
#include <limits>
#include <string>
#include <cstring>

struct Coordinates{
  int x, y;
};

struct Unit{
  int value;
  Coordinates point;
  Unit *next = nullptr;
};

struct Matrix{
  Coordinates size;
  Unit *unit = nullptr;
};

template <class T>

T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()){
  T val;
  while(true){
    std::cin >> val;
    if (std::cin.eof()){
      throw std::runtime_error("find eof");
    }
    else if (std::cin.bad()){
      throw std::runtime_error(std::string("failed to read number: ") + strerror(errno));
    }
    else if (std::cin.fail()){
      std::cin.clear();
      std::cin.ignore();
      std::cout << "error. repeat, please" << std::endl;
    }
    else if (val >= min && val <= max){
      return val;
    }
  }
  
}

namespace unit{

  Unit input(int val, int x, int y){
    Unit *cell = new Unit;
    cell->value = val;
    cell->point.x = x;
    cell->point.y = y;
    return *cell;
  }

  void pushback(Matrix &matrix, Unit &cell){
    Unit *cur = matrix.unit;
    Unit *ptr = nullptr;
    while (cur){
      ptr = cur;
      cur = cur->next;
    }
    ptr->next = &cell;
  }
}

void pushfront(Matrix &matrix, Unit &cell){
  cell.next = matrix.unit;
  matrix.unit = &cell;
}

namespace matrix{
  
  void erase(Matrix &matrix){
    Unit *ptr = matrix.unit;
    while (ptr){
      Unit *del_ptr = ptr;
      delete del_ptr;
      ptr = ptr->next;
    }
  }

  
  
  Matrix input(){
    Matrix matrix;
    try{
      std::cout << "enter number of columns:" << std::endl; //m: y, j
      matrix.size.y = getNum<int>();
      std::cout << "enter number of rows:" << std::endl; //n: x, i
      matrix.size.x = getNum<int>();
      for (int j = 0; j < matrix.size.y; j++){
        for (int i = 0; i < matrix.size.x; i++){
          int val;
          val = getNum<int>();
          if (val == 0){ continue; }
          Unit cell = unit::input(val, i, j);
          
        }
      }
    }
    catch(...){
      erase(matrix);
    }
    return matrix;
  }
  
}
int main(){
  
}