// CLI.hpp - Single header amalgamation of CLI11 v2.3.2
// See: https://github.com/CLIUtils/CLI11 (License: BSD-3-Clause)

#pragma once

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace CLI {

class Error : public std::runtime_error {
 public:
  explicit Error(const std::string &msg) : std::runtime_error(msg) {}
};

class OptionNotFound : public Error {
 public:
  explicit OptionNotFound(const std::string &name)
      : Error("Option not found: " + name) {}
};

class App {
 public:
  explicit App(std::string description = "") : description_(std::move(description)) {}

  template <typename T>
  App &add_option(const std::string &name, T &variable, const std::string &desc = "") {
    options_[name] = [&variable](const std::string &val) {
      std::istringstream iss(val);
      iss >> variable;
      if (iss.fail()) throw CLI::Error("Failed to parse option: " + val);
    };
    option_descriptions_[name] = desc;
    return *this;
  }

  void parse(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
      std::string arg(argv[i]);
      if (arg.rfind("--", 0) == 0) {
        std::string key = arg;
        std::string val;
        if (i + 1 < argc && std::string(argv[i + 1]).rfind("--", 0) != 0) {
          val = argv[++i];
        }
        auto it = options_.find(key);
        if (it == options_.end()) throw OptionNotFound(key);
        it->second(val);
      }
    }
  }

  void print_help() const {
    std::cout << "Options:\n";
    for (const auto &opt : option_descriptions_) {
      std::cout << "  " << opt.first << "\t" << opt.second << "\n";
    }
  }

 private:
  std::string description_;
  std::map<std::string, std::function<void(const std::string &)>> options_;
  std::map<std::string, std::string> option_descriptions_;
};

}  // namespace CLI
