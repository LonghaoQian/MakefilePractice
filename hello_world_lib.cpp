#include "include/HelloWorld.h"

int main(void) {
  HelloWorld greeter("Howdy world");

  std::cout << "message is " << greeter.msg() << "\n";

  greeter.msg() = "Sekai konnichiwa";
  std::cout << "message is " << greeter.msg() << "\n";

  greeter.msg() = "Hello world";

  greeter.reverse_msg();
  std::cout << "message is " << greeter.msg() << "\n";
}