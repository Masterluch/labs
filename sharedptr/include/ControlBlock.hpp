// Copyright 2021 Masterluch <atim2203@gmail.com>

#ifndef INCLUDE_CONTROLBLOCK_HPP_
#define INCLUDE_CONTROLBLOCK_HPP_

#include <atomic>

struct ControlBlock {
  std::atomic_uint _link_counter = 0;
};

#endif  // INCLUDE_CONTROLBLOCK_HPP_
