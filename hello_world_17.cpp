#include <any>
#include <iostream>
#include <string>

int main(void) {
  std::any val;

  double q[] = {0.0, 0.7071, 0.7071, 0.0};

  auto& [w, x, y, z] = q;

  std::cout << w << " " << x << " " << y << " " << z << "\n";

  val = std::string("Hello World");
  std::cout << std::any_cast<std::string>(val) << "\n";
}