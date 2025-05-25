#include <opencv2/core.hpp>

namespace objects_vis {

// matplotlib tableau palette
// https://matplotlib.org/stable/gallery/color/named_colors.html
inline cv::Vec3b random_color(int idx) {
  const int NCOLORS = 10;
  static cv::Vec3b COLOR_TABLE[NCOLORS] = {
      cv::Vec3b(180, 119, 31),   //
      cv::Vec3b(14, 127, 255),   //
      cv::Vec3b(44, 160, 44),    //
      cv::Vec3b(40, 39, 214),    //
      cv::Vec3b(189, 103, 148),  //
      cv::Vec3b(75, 86, 140),    //
      cv::Vec3b(194, 119, 227),  //
      cv::Vec3b(127, 127, 127),  //
      cv::Vec3b(34, 189, 188),   //
      cv::Vec3b(207, 190, 23),   //

  };
  return COLOR_TABLE[idx % NCOLORS];
}

}  // namespace objects_vis