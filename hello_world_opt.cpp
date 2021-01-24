#include <Eigen/Dense>
#include <iostream>
#include <chrono>

int main(void) {
  namespace clk = std::chrono;
  Eigen::MatrixXd mat = Eigen::MatrixXd::Random(1000, 1000);

  Eigen::MatrixXd eye = Eigen::MatrixXd::Identity(1000, 1000);
  auto t0 = clk::steady_clock::now();
  Eigen::MatrixXd soln = mat.ldlt().solve(eye);
  auto t1 = clk::steady_clock::now();

  double dt = clk::duration_cast<clk::milliseconds>(t1 - t0).count();
  
  std::cout << "Solution took " << dt << " milliseconds\n";
}