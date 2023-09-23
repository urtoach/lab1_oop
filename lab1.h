#ifndef LAB1_H
#define LAB1_H

#include <cstring>
#include <iostream>
#include <limits>
#include <string>
#include <cmath>
#include <iomanip>


namespace Lab1{

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


  bool compFunc1(Matrix &matrix, Unit &unit);
  bool compFunc2(Matrix &matrix, Unit &unit);
  void pushBack(Matrix &matrix, Unit *cell);
  void erase(Matrix &matrix);
  Unit *isExist(Matrix matrix, int x, int y);
  void outputFull(Matrix matrix);
  void outputShort(Matrix matrix);
  Matrix input();
  void checkCoord(Matrix &matrix);
  Matrix newMatrix(Matrix &init_matrix, bool (callback(Matrix&, Unit&)));
  
}

#endif //LAB1_H