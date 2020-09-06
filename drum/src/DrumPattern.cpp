#include "DrumPattern.h"

#include <algorithm>
#include <filesystem>
#include <functional>
#include <iostream>
#include <tuple>

#include <sndfile.h>

void DrumPattern::load_res_files() {
  namespace fs = std::filesystem;
  namespace ranges = std::ranges;

  const auto path = fs::path("data/GMRockKit");
  std::array<std::vector<float>, res_types::DrumTotal> data_array = {};

  for (const auto &beat : resource) {
    hit_per_beat = std::max(hit_per_beat, beat.size());

    for (const auto &hit : beat) {
      size_t max_buf_size = 0;
      for (const auto &k : hit) {
        if (data_array[k].empty()) {

          SF_INFO sf_info = {};
          auto name = path / res_types::source[k];

          SNDFILE *sf_wav = sf_open(name.c_str(), SFM_READ, &sf_info);
          if (sf_wav == nullptr) {
            std::cout << "err" << std::endl;
          };

          size_t buf_size = sf_info.channels * sf_info.frames;

          data_array[k].resize(buf_size);

          sf_read_float(sf_wav, data_array[k].data(), buf_size);
          sf_close(sf_wav);

          max_buf_size = std::max(max_buf_size, buf_size);
        } else {
          max_buf_size = std::max(max_buf_size, data_array[k].size());
        }
      }

      audio_data.emplace_back(
          std::make_shared<std::vector<float>>(max_buf_size, 0.0));
      // audio_data.emplace_back(std::shared_ptr<std::vector<float>>(max_buf_size,
      // 0.0)); audio_data.emplace_back(audio_type(max_buf_size, 0.0));
      auto &out = *audio_data.back();
      for (const auto &k : hit) {
        //        std::transform(out.begin(), out.end(), data_array[k].begin(),
        //        out.begin(), std::plus<float>{});
        ranges::transform(out, data_array[k], out.begin(), std::plus<float>{});
      }
    }
  }
}
