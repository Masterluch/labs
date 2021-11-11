// Copyright 2021 Masterluch <atim2203@gmail.com>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>

class Experiment {
 protected:
  std::vector<size_t> _vector_buffer_sizes;  // in mb

  void warming_up_array(int *array, size_t array_size) const;
  void generate_random_vector_of_indexes(std::vector<size_t> &vec_indexes,
                                         size_t array_size) const;
  int direct_method(int *array, size_t array_size) const;
  int reverse_method(int *array, size_t array_size) const;
  int random_method(int *array, size_t array_size) const;
  void print_experiment_data(size_t number_of_experiment, size_t buffer_size,
                             int duration_of_method) const;

 public:
  explicit Experiment(std::vector<size_t> vector_buffer_sizes);
  void start_experiment() const;
};

#endif  // INCLUDE_HEADER_HPP_