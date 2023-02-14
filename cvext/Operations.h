#pragma once

#include <Base.h>

namespace cv_ext {

auto alpha_composite(const Image &bg, const Image &fg) -> Image;

auto paste(const Image &bg, int x, int y, const Image &fg) -> Image;

} // namespace cv_ext
