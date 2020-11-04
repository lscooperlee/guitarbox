#ifndef RHYTHM_H
#define RHYTHM_H

#include <chrono>
#include <functional>
#include <thread>
#include <vector>

class Rhythm {

public:
  class RhythmType {
  public:
    virtual ~RhythmType() = default;
    virtual void callback() = 0;
  };

  Rhythm() = default;
  void start(bool);
  void stop();
  void set_bpm(int bpm_);
  void update(RhythmType *, int);
  void remove(RhythmType *);

private:
  void run(void);
  std::chrono::milliseconds duration{1000};
  std::vector<std::tuple<RhythmType *, int, int>> actions = {};
  std::thread timer = {};
  bool is_stop = false;
  int bpm = 60;
  int common_product = 1;
};

#endif /* RHYTHM_H */
