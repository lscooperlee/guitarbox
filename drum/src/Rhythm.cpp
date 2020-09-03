#include "Rhythm.h"

#include <chrono>
#include <thread>

namespace chrono = std::chrono;

void Rhythm::start() {
  is_running = false;
  std::thread t([&]() {
    while (true) {
      if (is_running)
        return;
      std::this_thread::sleep_for(duration);
      if (is_running)
        return;
    }
  });
  t.detach();
}

void Rhythm::stop() {}

void Rhythm::update(const auto &func, int d) {
  actions.emplace_back({func, d});
}
