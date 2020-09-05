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
  void set_bpm(int bpm_);
  void update(std::function<void(void)>, int);

private:
  std::chrono::milliseconds duration = {};
  std::vector<std::tuple<std::function<void(void)>, const int, int>> actions =
      {};
  std::thread timer = {};
  bool is_stop = false;
  int bpm = 60;
  int common_product = 1;
};

#endif /* RHYTHM_H */
