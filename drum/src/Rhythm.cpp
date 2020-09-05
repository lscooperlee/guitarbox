#include "Rhythm.h"

#include <chrono>
#include <numeric>
#include <thread>
#include <tuple>

namespace chrono = std::chrono;

void Rhythm::start() {
  is_stop = false;

  std::thread t([this]() {
    int count = common_product;
    while (true) {
      if (is_stop)
        return;
      std::this_thread::sleep_for(duration);
      if (is_stop)
        return;

      for (const auto &a : actions) {
        const auto check_count = std::get<2>(a);
        if (count % check_count == 0) {
          auto &func = std::get<0>(a);
          func();
        }
      }

      count--;
    }
  });
  t.detach();
}

void Rhythm::stop() {}

void Rhythm::set_bpm(int bpm_) {
  bpm = bpm_;
  duration = chrono::milliseconds(bpm * 1000 / 60 / common_product);
}

void Rhythm::update(std::function<void(void)> func, int d) {

  actions.emplace_back(func, d, 0);

  common_product = d > 1 ? common_product * d : common_product;

  for (auto &a : actions) {
    std::get<2>(a) = common_product / std::get<1>(a);
  }
}
