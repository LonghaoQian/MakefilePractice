#include <boost/program_options.hpp>
#include <iostream>

int main(int argc, char **argv) {
  namespace po = boost::program_options;

  po::options_description opts("Project Description");

  opts.add_options()("help,h", "produce help message")(
      "dummy,d", po::value<int>()->default_value(100), "A integer value");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, opts), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << opts << "\n";
    return 1;
  }
  const bool is_default = vm.count("dummy") ? false : true;

  const int val = vm["dummy"].as<int>();

  std::cout << "Hello world, I linked the boost program_options library \n"
            << "I " << (is_default ? "did not provide" : "provided")
            << " a value on the command line and it is " << val << "\n";

  return 0;
}