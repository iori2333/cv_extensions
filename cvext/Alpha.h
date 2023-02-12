#pragma once

#include <Base.h>
#include <iostream>

namespace cv_ext {

auto alpha_composite(Image &fg, Image &bg) -> Image;

} // namespace cv_ext
