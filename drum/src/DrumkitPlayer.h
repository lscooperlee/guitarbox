#ifndef DRUMKITPLAYER_H
#define DRUMKITPLAYER_H

class DrumPattern;

class DrumkitPlayer {
public:
  DrumkitPlayer() = default;
  void play(const DrumPattern &);
  void set_bpm(int new_bpm);

private:
  int bpm = 60;
};

#endif /* DRUMKITPLAYER_H */
