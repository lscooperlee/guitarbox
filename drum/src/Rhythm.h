#ifndef RHYTHM_H
#define RHYTHM_H

#include <chrono>
#include <functional>
#include <thread>
#include <vector>

class Rhythm {

public:
  Rhythm() = default;
  void start();
  void stop();
  void update(const auto &, int);

private:
  std::chrono::milliseconds duration = {};
  std::vector<std::tuple<std::function<void(void)>, int>> actions = {};
  std::thread timer = {};
  bool is_running = false;
  int bpm = {};
};

#endif /* RHYTHM_H */
