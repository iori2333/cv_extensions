#include "Mat.h"
#include <cvext.h>
#include <pybind11/pybind11.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

int add(int i, int j) { return i + j; }

PYBIND11_MODULE(cv_extensions, m) {
  m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: cv_extensions

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

  m.def("add", &add, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");

  m.def(
      "subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers

        Some other explanation about the subtract function.
    )pbdoc");

  m.def(
      "alpha_composite",
      [](PyImage &im1, PyImage &im2) {
        auto fg = convertMat(im1);
        auto bg = convertMat(im2);
        auto out = cv_ext::alpha_composite(fg, bg);
        return convertImage(out);
      },
      R"pbdoc(
        Alpha composite two images

        Some other explanation about the alpha_composite function.
    )pbdoc");

#ifdef VERSION_INFO
  m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  m.attr("__version__") = "dev";
#endif
}
