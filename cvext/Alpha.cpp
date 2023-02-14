#include <Operations.h>

namespace cv_ext {

using cv::Point;
using cv::Rect;
using std::max;
using std::min;

auto alpha_composite(const Image &bg, const Image &fg) -> Image {
  if (bg.channels() != 4 || fg.channels() != 4) { // check RGB-A
    throw std::runtime_error("Unsupported image type");
  }
  if (bg.rows != fg.rows || bg.cols != fg.cols) {
    throw std::runtime_error("Image size mismatch");
  }

  auto out = Image(bg.rows, bg.cols, CV_8UC4);
  for (auto i = 0; i < bg.rows; ++i) {
    for (auto j = 0; j < bg.cols; ++j) {
      const auto &dst_pixel = bg.at<cv::Vec4b>(i, j);
      const auto &src_pixel = fg.at<cv::Vec4b>(i, j);
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

auto paste(Image &bg, int x, int y, const Image &fg) -> Image {
  if (bg.channels() != 4 || fg.channels() != 4) { // check RGB-A
    throw std::runtime_error("Unsupported image type");
  }
  auto b = y;
  auto t = y + fg.rows;
  auto l = x;
  auto r = x + fg.cols;

  auto fgCrop =
      Rect(Point(max(-b, 0), max(-l, 0)),
           Point(max(bg.rows - b, fg.rows), max(bg.cols - l, fg.cols)));
  auto fgCropped = fg(fgCrop);

  auto bgCrop = Rect(Point(max(b, 0), max(l, 0)),
                     Point(min(t, bg.rows), min(r, bg.cols)));
  auto bgCropped = bg(bgCrop);

  auto ret = alpha_composite(bgCropped, fgCropped);
  ret.copyTo(bg(bgCrop));
  return bg;
}
} // namespace cv_ext
