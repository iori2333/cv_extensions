#include <Alpha.h>

namespace cv_ext {
auto alpha_composite(Image &fg, Image &bg) -> Image {
  if (fg.channels() != 4 || bg.channels() != 4) { // check RGB-A
    throw std::runtime_error("Unsupported image type");
  }
  if (fg.rows != bg.rows || fg.cols != bg.cols) {
    throw std::runtime_error("Image size mismatch");
  }

  auto out = Image(fg.rows, fg.cols, CV_8UC4);
  for (auto i = 0; i < fg.rows; ++i) {
    for (auto j = 0; j < fg.cols; ++j) {
      const auto &dst_pixel = fg.at<cv::Vec4b>(i, j);
      const auto &src_pixel = bg.at<cv::Vec4b>(i, j);
      auto &out_pixel = out.at<cv::Vec4b>(i, j);

      if (src_pixel[3] == 0) {
        out_pixel = dst_pixel;
        continue;
      }
      auto blend = dst_pixel[3] * (255 - src_pixel[3]);
      auto outa255 = blend + src_pixel[3] * 255;
      auto coef1 = src_pixel[3] * 255 * 255 / outa255;
      auto coef2 = 255 - coef1;

      auto tmpr = src_pixel[0] * coef1 + dst_pixel[0] * coef2;
      auto tmpg = src_pixel[1] * coef1 + dst_pixel[1] * coef2;
      auto tmpb = src_pixel[2] * coef1 + dst_pixel[2] * coef2;

      out_pixel[0] = tmpr / 255;
      out_pixel[1] = tmpg / 255;
      out_pixel[2] = tmpb / 255;
      out_pixel[3] = outa255 / 255;
    }
  }
  return out;
}
} // namespace cv_ext
