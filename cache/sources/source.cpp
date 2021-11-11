// Copyright 2021 Masterluch <atim2203@gmail.com>

#include <header.hpp>

void Experiment::warming_up_array(int *array, size_t array_size) const {
  [[maybe_unused]] int k;

  for (size_t i = 0; i < array_size; i += 16) {
    k = array[i];
  }
}

void Experiment::generate_random_vector_of_indexes(
    std::vector<size_t> &vec_indexes, size_t array_size) const {

  for (size_t i = 0; i < array_size; i += 16) {
    vec_indexes.push_back(i);
  }

  for (size_t i = 0; i < vec_indexes.size(); ++i) {
    unsigned int seed = time(NULL);
    size_t new_index = i + rand_r(&seed) % (vec_indexes.size()-i);
    int value = vec_indexes[i];
    vec_indexes[i] = vec_indexes[new_index];
    vec_indexes[new_index] = value;
  }
}

int Experiment::direct_method(int *array, size_t array_size) const {
  warming_up_array(array, array_size);

  [[maybe_unused]] int k;
  auto start_time = std::chrono::high_resolution_clock::now();
  for (size_t j = 0; j < 1000; ++j) {
    for (size_t i = 0; i < array_size; i += 16) {
      k = array[i];
    }
  }
  auto finish_time = std::chrono::high_resolution_clock::now();
  int duration_of_method =
      static_cast<int>(std::chrono::duration_cast<std::chrono::microseconds>(
                           finish_time - start_time)
                           .count());

  return duration_of_method;
}

int Experiment::reverse_method(int *array, size_t array_size) const {
  warming_up_array(array, array_size);

  [[maybe_unused]] int k;
  auto start_time = std::chrono::high_resolution_clock::now();
  for (size_t j = 0; j < 1000; ++j) {
    for (size_t i = array_size; i > 0; i -= 16) {
      k = array[i];
    }
  }
  auto finish_time = std::chrono::high_resolution_clock::now();
  int duration_of_method =
      static_cast<int>(std::chrono::duration_cast<std::chrono::microseconds>(
                           finish_time - start_time)
                           .count());

  return duration_of_method;
}

int Experiment::random_method(int *array, size_t array_size) const {
  std::vector<size_t> vec_indexes;
  generate_random_vector_of_indexes(vec_indexes, array_size);

  warming_up_array(array, array_size);

  [[maybe_unused]] int k;
  auto start_time = std::chrono::high_resolution_clock::now();
  for (size_t j = 0; j < 1000; ++j) {
    for (auto i : vec_indexes) {
      k = array[i];
    }
  }
  auto finish_time = std::chrono::high_resolution_clock::now();
  int duration_of_method =
      static_cast<int>(std::chrono::duration_cast<std::chrono::microseconds>(
                           finish_time - start_time)
                           .count());

  return duration_of_method;
}

void Experiment::print_experiment_data(size_t number_of_experiment,
                                       [[maybe_unused]] size_t buffer_size,
                                       int duration_of_method) const {
  std::cout << std::endl
            << "  - experiment:" << std::endl
            << "      number: " << number_of_experiment + 1 << std::endl
            << "      input_data:" << std::endl
            << "        buffer_size: "
            << _vector_buffer_sizes[number_of_experiment] << "mb" << std::endl
            << "      results:" << std::endl
            << "        duration: " << duration_of_method << "mcs";
}

Experiment::Experiment(std::vector<size_t> vector_buffer_sizes) {
  if (vector_buffer_sizes.size() == 0)
    throw std::invalid_argument("Vector is empty");
  for (auto i : vector_buffer_sizes) {
    if (i > 1000)
      throw std::invalid_argument("The value is too large");
    else if (i == 0)
      throw std::invalid_argument("The value is uncorrect");
  }

  _vector_buffer_sizes = vector_buffer_sizes;
}

void Experiment::start_experiment() const {
  // Direction method

  std::cout << "investigaion:" << std::endl
            << "  travel_order: direction" << std::endl
            << "  experiments:";

  for (size_t i = 0; i < _vector_buffer_sizes.size(); ++i) {
    size_t array_size = _vector_buffer_sizes[i] * 1024 * 1024 / 4;
    int *array = new int[array_size];
    int duration_of_method = direct_method(array, array_size);
    delete[] array;

    print_experiment_data(i, _vector_buffer_sizes[i], duration_of_method);
  }

  // Reverse method

  std::cout << std::endl
            << std::endl
            << "investigaion:" << std::endl
            << "  travel_order: reverce" << std::endl
            << "  experiments:";

  for (size_t i = 0; i < _vector_buffer_sizes.size(); ++i) {
    size_t array_size = _vector_buffer_sizes[i] * 1024 * 1024 / 4;
    int *array = new int[array_size];
    int duration_of_method = reverse_method(array, array_size);
    delete[] array;

    print_experiment_data(i, _vector_buffer_sizes[i], duration_of_method);
  }

  // Random method

  std::cout << std::endl
            << std::endl
            << "investigaion:" << std::endl
            << "  travel_order: random" << std::endl
            << "  experiments:";

  for (size_t i = 0; i < _vector_buffer_sizes.size(); ++i) {
    size_t array_size = _vector_buffer_sizes[i] * 1024 * 1024 / 4;
    int *array = new int[array_size];
    int duration_of_method = random_method(array, array_size);
    delete[] array;

    print_experiment_data(i, _vector_buffer_sizes[i], duration_of_method);
  }
}