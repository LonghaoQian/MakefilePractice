#include <iostream>
#include "TopologyAnalysis.h"

int main(void) {
  std::cout << "Hello World\n";
  Eigen::MatrixXd m(2, 2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  TopologyAnalysis top1(m);
  double i = 2.0;
  // int a = static_cast<int>(i);
  int a = i;
  std::cout<<a<<'\n';
  return 0;
}