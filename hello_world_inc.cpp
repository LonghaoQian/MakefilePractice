#include <Eigen/Core>
#include <iostream>

int main(void) {
  Eigen::Matrix3d mat = Eigen::Matrix3d::Random();
  std::cout << "Hello world, I included the Eigen Library, "
               "here is a matrix\n"
            << mat << "\n";
}