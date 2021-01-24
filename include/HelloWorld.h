#include <iostream>

class HelloWorld {
  std::string message_;

 public:
  HelloWorld(const std::string &message = "hello world");

  const std::string &msg() const;
  std::string &msg();

  void reverse_msg();
};