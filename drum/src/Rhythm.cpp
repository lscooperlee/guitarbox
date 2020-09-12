#include "Rhythm.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <thread>
#include <tuple>

namespace chrono = std::chrono;
namespace ranges = std::ranges;

void Rhythm::run() {
  is_stop = false;

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
        auto &t = std::get<0>(a);
        t->callback();
      }
    }

    count--;
    if (count == 0) {
      count = common_product;
    }

    std::cout << "bpm: " << bpm << std::endl;
  }
}

void Rhythm::start(bool use_thread) {
  if (use_thread) {
    std::thread t([this]() { run(); });
    t.detach();
  } else {
    run();
  }
}

void Rhythm::stop() {}

void Rhythm::set_bpm(int bpm_) {
  bpm = bpm_;
  duration = chrono::milliseconds(60 * 1000 / bpm / common_product);
}

void Rhythm::update(RhythmType *t, int d) {

  actions.emplace_back(t, d, 0);

  common_product = d > 1 ? common_product * d : common_product;

  for (auto &a : actions) {
    std::get<2>(a) = common_product / std::get<1>(a);
  }

  set_bpm(bpm);
}

void Rhythm::remove(RhythmType *t) {
  auto _ = [t](const auto &a) { return std::get<0>(a) == t; };
  ranges::remove_if(actions, _);
}
