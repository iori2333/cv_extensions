#pragma once

#include <cvext.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

using PyImage = pybind11::array_t<uint8_t>;
using Image = cv_ext::Image;

inline auto convertMat(PyImage &im) -> Image {
  auto buf = im.request();
  int flag{};
  if (buf.ndim == 2) {
    flag = CV_8UC1;
  } else if (buf.ndim == 3) {
    flag = buf.shape[2] == 3 ? CV_8UC3 : CV_8UC4;
  } else {
    throw std::runtime_error("Unsupported image dimension");
  }
  return Image(buf.shape[0], buf.shape[1], flag, buf.ptr);
}

inline auto convertImage(const Image &im) -> PyImage {
  auto channels = im.channels();
  if (channels == 1) {
    return PyImage({im.rows, im.cols}, im.data);
  } else if (channels == 3 || channels == 4) {
    return PyImage({im.rows, im.cols, channels}, im.data);
  } else {
    throw std::runtime_error("Unsupported image type2");
  }
}
