// Copyright 2021 Artem Artemov <theartemka6@mail.ru>

#include <cache.hpp>

/* AMD Ryzen 7 5700U
 * cache_sizes['1'] = 512 KB
 * cache_sizes['2'] = 4096 KB
 * cache_sizes['3'] = 8192 KB
 * cache_sizes['1']*1/2 = 256 KB
 * cache_sizes['3']*3/2 = 12288
 * 256 KB < 512 KB < 4096 KB < 8192 KB < 12288 KB
 */

CacheDiagnostics::CacheDiagnostics() {
  seed = 11111;
  sizes[0] = 262144 / 4;
  sizes[1] = 524288 / 4;
  sizes[2] = 4194304 / 4;
  sizes[3] = 8388608 / 4;
  sizes[4] = 12582912 / 4;
  statistics[0].bufferSize = sizes[0];
  statistics[1].bufferSize = sizes[1];
  statistics[2].bufferSize = sizes[2];
  statistics[3].bufferSize = sizes[3];
  statistics[4].bufferSize = sizes[4];
}
void CacheDiagnostics::create_array(int num_size) {
  arr = new int[sizes[num_size]];
  for (int i = 0; i < sizes[num_size]; i++) {
    arr[i] = rand_r(&seed);
  }
}

void CacheDiagnostics::front_diagnostics(int num_size) {
  create_array(num_size);
  //  ПРОГРЕВ
  for (int i = 0; i < sizes[num_size]; i += 16) {
    read_value = arr[i];
  }
  // ЧТЕНИЕ + ПОДСЧЕТ ВРЕМЕНИ
  auto start = static_cast<double>(clock());

  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < sizes[num_size]; j += 16) {
      read_value = arr[j];
    }
  }

  auto end = static_cast<double>(clock());
  statistics[num_size].duration_front = ((end - start) / CLOCKS_PER_SEC) * 1000;
  statistics[num_size].experimentNumber_front = num_size + 1;
}

void CacheDiagnostics::reverse_diagnostics(int num_size) {
  create_array(num_size);
  //  ПРОГРЕВ
  for (int i = 0; i < sizes[num_size]; i += 16) {
    read_value = arr[i];
  }
  // ЧТЕНИЕ + ПОДСЧЕТ ВРЕМЕНИ
  auto start = static_cast<double>(clock());

  for (int i = 0; i < 1000; i++) {
    for (int j = sizes[num_size]; j > 0; j -= 16) {
      read_value = arr[j];
    }
  }
  auto end = static_cast<double>(clock());
  statistics[num_size].duration_reverse =
      ((end - start) / CLOCKS_PER_SEC) * 1000;
  statistics[num_size].experimentNumber_reverse = num_size + 6;
}

void CacheDiagnostics::random_diagnostics(int num_size) {
  create_array(num_size);
  //  ПРОГРЕВ
  for (int i = 0; i < sizes[num_size]; i += 16) {
    read_value = arr[i];
  }
  std::vector<int> ins;
  for (int i = 0; i < sizes[num_size]; i += 16) {
    ins.push_back(i);
  }
  std::random_shuffle(ins.begin(), ins.end());
  // ЧТЕНИЕ + ПОДСЧЕТ ВРЕМЕНИ
  auto start = static_cast<double>(clock());

  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < sizes[num_size] / 16; j++) {
      read_value = arr[ins[j]];
    }
  }
  auto end = static_cast<double>(clock());
  statistics[num_size].duration_random =
      ((end - start) / CLOCKS_PER_SEC) * 1000;
  statistics[num_size].experimentNumber_random = num_size + 11;
}
void CacheDiagnostics::formatting_output() {
  std::cout << "  investigaion:\n"
            << "    travel_order: \"front\"\n"
            << "    experiments:\n";
  for (int i = 0; i < 5; i++) {
    std::cout << "    - experiment: " << statistics[i].experimentNumber_front
              << "\n";
    std::cout << "        input_data:\n"
                 "          buffer_size: \""
              << statistics[i].bufferSize * 4 / 1024 << "Kb\"\n";
    std::cout << "        results:\n"
                 "          duration: \""
              << statistics[i].duration_front << "ms\"\n";
  }

  std::cout << "  investigaion:\n"
            << "    travel_order: \"reverse\"\n"
            << "    experiments:\n";
  for (int i = 0; i < 5; i++) {
    std::cout << "    - experiment: " << statistics[i].experimentNumber_reverse
              << "\n";
    std::cout << "        input_data:\n"
                 "          buffer_size: \""
              << statistics[i].bufferSize * 4 / 1024 << "Kb\"\n";
    std::cout << "        results:\n"
                 "          duration: \""
              << statistics[i].duration_reverse << "ms\"\n";
  }

  std::cout << "  investigaion:\n"
            << "    travel_order: \"random\"\n"
            << "    experiments:\n";
  for (int i = 0; i < 5; i++) {
    std::cout << "    - experiment: " << statistics[i].experimentNumber_random
              << "\n";
    std::cout << "        input_data:\n"
                 "          buffer_size: \""
              << statistics[i].bufferSize * 4 / 1024 << "Kb\"\n";
    std::cout << "        results:\n"
                 "          duration: \""
              << statistics[i].duration_random << "ms\"\n";
  }
}

void CacheDiagnostics::full_diagnostics() {
  for (int i = 0; i < 5; i++) {
    front_diagnostics(i);
  }

  for (int i = 0; i < 5; i++) {
    reverse_diagnostics(i);
  }
  for (int i = 0; i < 5; i++) {
    random_diagnostics(i);
  }
}
CacheDiagnostics::~CacheDiagnostics() { delete[] arr; }
