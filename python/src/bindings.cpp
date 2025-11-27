#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;

NB_MODULE(bindings, m) {
    m.doc() = "cecxx bindings";
    m.def("sub", [](int a, int b) { return a - b; }, "a"_a, "b"_a);
}
