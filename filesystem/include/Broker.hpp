// Copyright 2021 Masterluch <atim2203@gmail.com>

#ifndef INCLUDE_BROKER_HPP_
#define INCLUDE_BROKER_HPP_

#include <Account.hpp>
#include <iostream>
#include <string>
#include <vector>

class Broker {
 public:
  std::string _name;
  std::vector<Account> _accounts;

  explicit Broker(const std::string& name) : _name(name) {}

  std::string parse_account_name(const std::string& string_account) const {
    std::string account_name = "";
    for (size_t i = 8; i < 16; ++i) {
      account_name += string_account[i];
    }

    return account_name;
  }

  int parse_file_date(const std::string& string_account) const {
    std::string file_date = "";
    for (size_t i = 17; i < 25; ++i) {
      file_date += string_account[i];
    }

    return std::stoi(file_date);
  }

  void check_account(std::string& string_account) {
    std::string account_name = parse_account_name(string_account);
    for (auto& account : _accounts) {
      if (account._name == account_name) {
        account.add_file(parse_file_date(string_account));
        return;
      }
    }
    _accounts.push_back(Account(account_name, parse_file_date(string_account)));
  }

  void print_account_data() const {
    for (auto& account : _accounts) {
      std::cout << "broker:" << _name << " account:" << account._name
                << " files:" << account._number_of_files
                << " lastdate:" << account._last_date << std::endl;
    }
  }
};

#endif  // INCLUDE_BROKER_HPP_
