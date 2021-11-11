// Copyright 2021 Masterluch <atim2203@gmail.com>

#ifndef INCLUDE_ACCOUNT_HPP_
#define INCLUDE_ACCOUNT_HPP_

#include <string>

class Account {
 public:
  std::string _name;
  size_t _number_of_files;
  int _last_date;

  Account(const std::string& name, int last_date)
      : _name(name), _number_of_files(0), _last_date(last_date) {}

  void add_file(int file_date) {
    _number_of_files++;
    if (file_date > _last_date) {
      _last_date = file_date;
    }
  }
};

#endif  // INCLUDE_ACCOUNT_HPP_
