#ifndef DRUMPATTERN_H
#define DRUMPATTERN_H

#include <array>
#include <cstdint>
#include <memory>
#include <string_view>
#include <vector>

namespace res_types {

enum Drumkit {
  Kick = 0, // Bass
  SideStick,
  Snare,
  SnareRimshot,
  TomFloor,
  HatClosed,
  Tom2,
  HatPedal,
  Tom1,
  HatOpen,
  Cowbell,
  Ride,
  Crash,
  Ride2,
  Splash,
  HatSemiOpen,
  Bell,
  HandClap,
  DrumTotal,
};

static constexpr std::array<const char *, res_types::DrumTotal> source = {
    "Kick-Med.wav",         "SideStick-Med.wav", "Snare-Med.wav",
    "SnareRimshot-Med.wav", "TomFloor-Med.wav",  "HatClosed-Med.wav",
    "Tom2-Med.wav",         "HatPedal-Med.wav",  "Tom1-Med.wav",
    "HatOpen-Med.wav",      "Cowbell-Med.wav",   "Ride-Med.wav",
    "Crash-Med.wav",        "Ride2-Med.wav",     "Splash-Med.wav",
    "HatSemiOpen-Med.wav",  "Bell-Med.wav",      "HandClap-Med.wav",
};

static_assert(source[res_types::Kick] == std::string_view("Kick-Med.wav"));
static_assert(source[res_types::SideStick] ==
              std::string_view("SideStick-Med.wav"));
static_assert(source[res_types::Snare] == std::string_view("Snare-Med.wav"));
static_assert(source[res_types::SnareRimshot] ==
              std::string_view("SnareRimshot-Med.wav"));
static_assert(source[res_types::TomFloor] ==
              std::string_view("TomFloor-Med.wav"));
static_assert(source[res_types::HatClosed] ==
              std::string_view("HatClosed-Med.wav"));
static_assert(source[res_types::Tom2] == std::string_view("Tom2-Med.wav"));
static_assert(source[res_types::HatPedal] ==
              std::string_view("HatPedal-Med.wav"));
static_assert(source[res_types::Tom1] == std::string_view("Tom1-Med.wav"));
static_assert(source[res_types::HatOpen] ==
              std::string_view("HatOpen-Med.wav"));
static_assert(source[res_types::Cowbell] ==
              std::string_view("Cowbell-Med.wav"));
static_assert(source[res_types::Ride] == std::string_view("Ride-Med.wav"));
static_assert(source[res_types::Crash] == std::string_view("Crash-Med.wav"));
static_assert(source[res_types::Ride2] == std::string_view("Ride2-Med.wav"));
static_assert(source[res_types::Splash] == std::string_view("Splash-Med.wav"));
static_assert(source[res_types::HatSemiOpen] ==
              std::string_view("HatSemiOpen-Med.wav"));
static_assert(source[res_types::Bell] == std::string_view("Bell-Med.wav"));
static_assert(source[res_types::HandClap] ==
              std::string_view("HandClap-Med.wav"));

} // namespace res_types

class DrumPattern {
public:
  using DrumGroup = std::vector<res_types::Drumkit>;
  using Hit = std::vector<DrumGroup>;
  using audio_type = std::shared_ptr<std::vector<float>>;

  DrumPattern() = default;

  DrumPattern(std::initializer_list<Hit> l) : resource(l) { load_res_files(); };

  // load(const std::string& config_file);
  // load(const std::vector<Hit>& );

private:
  std::vector<Hit> resource = {};
  std::vector<audio_type> audio_data = {};
  void load_res_files();
};

#endif /* DRUMPATTERN_H */
