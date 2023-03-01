#include <Function.h>
#include <Operations.h>
#include <pybind11/pybind11.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

PYBIND11_MODULE(cv_extensions, m) {
  m.doc() = R"pbdoc(
        OpenCV with additional functions
        -----------------------

        .. currentmodule:: cv_extensions

        .. autosummary::
           :toctree: _generate

           alpha_composite
           paste
    )pbdoc";

  m.def("alpha_composite", cv_ext::pyFunction(cv_ext::alpha_composite),
        R"pbdoc(
        Alpha composite two images

        Some other explanation about the alpha_composite function.
    )pbdoc");

  m.def("paste", cv_ext::pyFunction(cv_ext::paste),
        R"pbdoc(
        Paste an image to another image

        Some other explanation about the paste function.
    )pbdoc");

#ifdef VERSION_INFO
  m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  m.attr("__version__") = "dev";
#endif
}
