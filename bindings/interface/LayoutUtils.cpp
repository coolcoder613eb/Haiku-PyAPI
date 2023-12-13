#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/LayoutUtils.h>
#include <Alignment.h>
#include <Rect.h>
#include <Size.h>
#include <String.h>
#include <View.h>
#include <LayoutItem.h>

namespace py = pybind11;


PYBIND11_MODULE(LayoutUtils,m)
{
py::class_<BLayoutUtils>(m, "BLayoutUtils")
.def_static("AddDistances", py::overload_cast<float, float>(&BLayoutUtils::AddDistances), "", py::arg("a"), py::arg("b"))
.def_static("AddDistances", py::overload_cast<float, float, float>(&BLayoutUtils::AddDistances), "", py::arg("a"), py::arg("b"), py::arg("c"))
.def_static("AddSizesInt32", py::overload_cast<int32, int32>(&BLayoutUtils::AddSizesInt32), "", py::arg("a"), py::arg("b"))
.def_static("AddSizesInt32", py::overload_cast<int32, int32, int32>(&BLayoutUtils::AddSizesInt32), "", py::arg("a"), py::arg("b"), py::arg("c"))
.def_static("SubtractSizesInt32", &BLayoutUtils::SubtractSizesInt32, "", py::arg("a"), py::arg("b"))
.def_static("SubtractDistances", &BLayoutUtils::SubtractDistances, "", py::arg("a"), py::arg("b"))
.def_static("FixSizeConstraints", [](BLayoutUtils& self) {
    float  min;
float  max;
float  preferred;
    //static void r = self.FixSizeConstraints(min, max, preferred);
    self.FixSizeConstraints(min, max, preferred);
    return std::make_tuple(min,max,preferred);
}
, "")
.def_static("FixSizeConstraints", [](BLayoutUtils& self) {
    BSize  min;
BSize  max;
BSize  preferred;
    //static void r = self.FixSizeConstraints(min, max, preferred);
    self.FixSizeConstraints(min, max, preferred);
    return std::make_tuple(min,max,preferred);
}
, "")
.def_static("ComposeSize", &BLayoutUtils::ComposeSize, "", py::arg("size"), py::arg("layoutSize"))
.def_static("ComposeAlignment", &BLayoutUtils::ComposeAlignment, "", py::arg("alignment"), py::arg("layoutAlignment"))
.def_static("AlignInFrame", py::overload_cast<BRect, BSize, BAlignment>(&BLayoutUtils::AlignInFrame), "", py::arg("frame"), py::arg("maxSize"), py::arg("alignment"))
.def_static("AlignInFrame", py::overload_cast<BView *, BRect>(&BLayoutUtils::AlignInFrame), "", py::arg("view"), py::arg("frame"))
.def_static("AlignOnRect", &BLayoutUtils::AlignOnRect, "", py::arg("rect"), py::arg("size"), py::arg("alignment"))
.def_static("MoveIntoFrame", &BLayoutUtils::MoveIntoFrame, "", py::arg("rect"), py::arg("frameSize"))
.def_static("GetLayoutTreeDump", py::overload_cast<BView *>(&BLayoutUtils::GetLayoutTreeDump), "", py::arg("view"))
.def_static("GetLayoutTreeDump", py::overload_cast<BLayoutItem *>(&BLayoutUtils::GetLayoutTreeDump), "", py::arg("item"))
;


}
