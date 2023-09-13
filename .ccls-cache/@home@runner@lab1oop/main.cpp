#include <iostream>
#include <limits>
#include <string>
#include <cstring>

struct Unit{
  int i, j;
  double value;
  Unit *next = nullptr;
};

struct Matrix{
  int n, m;
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
      std::cout << "enter number of columns:" << std::endl;
      matrix.m = getNum<int>();
      std::cout << "enter number of rows:" << std::endl;
      matrix.n = getNum<int>();
      for (int i = 0; i < matrix.m; i++){
        for (int j = 0; j < matrix.n; j++){
          double val;
          val = getNum<double>();
          if (val == 0){ continue; }
          Unit *cell = new Unit;
          cell->value = val;
          cell->i = i;
          cell->j = j;
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