#include <iostream>
#include "lab1.h"

using namespace Lab1;

int main() {
  Matrix matrix;
  Matrix new_matrix;
  while (true){
    try{
      std::cout << "enter new matrix" << std::endl;
      matrix = matrix::input();
      matrix::outputFull(matrix);
      //matrix::outputShort(matrix);
    
      std::cout << "form a new matrix:" << std::endl;
      std::cout << "\t[the function forms a new matrix by\n\tplacing in its i-th row those elements from\n\tthe i-th row of the original matrix\n\twhose entry exceeds the average number\n\tdigits in the record of all\n\telements of a given row of the matrix]" << std::endl;
    
      new_matrix = matrix::newMatrix(matrix, compFunc1);
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
    catch(const std::bad_alloc &ba) {
      std::cerr << "Not enough memory" << std::endl;
      matrix::erase(matrix);
      matrix::erase(new_matrix);
      return 1;
    }
    catch (const std::exception& e) {
      std::cerr << "an exception occurred: " << e.what() << std::endl;
      matrix::erase(matrix);
      matrix::erase(new_matrix);
      return 1;
    }
  }
  return 0;
}