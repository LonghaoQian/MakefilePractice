#include "HelloWorld.h"

HelloWorld::HelloWorld(const std::string &message) : message_(message){};

const std::string &HelloWorld::msg() const { return message_; }

std::string &HelloWorld::msg() { return message_; }

void HelloWorld::reverse_msg() {
  std::string reversed(message_.rbegin(), message_.rend());
  message_ = reversed;
}