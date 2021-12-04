// Copyright 2021 Artem Artemov <theartemka6@mail.ru>

#ifndef INCLUDE_CACHE_HPP_
#define INCLUDE_CACHE_HPP_

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

struct Statistics {
  int experimentNumber_front;
  int experimentNumber_reverse;
  int experimentNumber_random;
  int bufferSize;
  double duration_front;
  double duration_reverse;
  double duration_random;
};

class CacheDiagnostics {
 private:
  unsigned int seed;
  int read_value;
  int sizes[5];
  Statistics statistics[5];
  int *arr;
  unsigned int timer;
  int last_size;
  void create_array(int num_size);

 public:
  CacheDiagnostics();
  void front_diagnostics(int num_size);
  void reverse_diagnostics(int num_size);
  void random_diagnostics(int num_size);
  void formatting_output();
  void full_diagnostics();
};

/* AMD Ryzen 7 5700U
 * cache_sizes['1'] = 512 KB
 * cache_sizes['2'] = 4096 KB
 * cache_sizes['3'] = 8192 KB
 * cache_sizes['1']*1/2 = 256 KB
 * cache_sizes['3']*3/2 = 12288
 * 256 KB < 512 KB < 4096 KB < 8192 KB < 12288 KB
 */

#endif  // INCLUDE_CACHE_HPP_
