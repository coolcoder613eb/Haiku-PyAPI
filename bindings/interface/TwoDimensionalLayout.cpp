#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/TwoDimensionalLayout.h>
#include <AbstractLayout.h>

namespace py = pybind11;

class PyBTwoDimensionalLayout : public BTwoDimensionalLayout{
	public:
        using BTwoDimensionalLayout::BTwoDimensionalLayout;
        BSize				BaseMinSize() override {
        	PYBIND11_OVERLOAD(BSize, BTwoDimensionalLayout, BaseMinSize);
        }
		BSize				BaseMaxSize() override {
        	PYBIND11_OVERLOAD(BSize, BTwoDimensionalLayout, BaseMaxSize);
        }
		BSize				BasePreferredSize() override {
        	PYBIND11_OVERLOAD(BSize, BTwoDimensionalLayout, BasePreferredSize);
        }
		BAlignment			BaseAlignment() override {
        	PYBIND11_OVERLOAD(BAlignment, BTwoDimensionalLayout, BaseAlignment);
        }
		bool				HasHeightForWidth() override {
        	PYBIND11_OVERLOAD(bool, BTwoDimensionalLayout, HasHeightForWidth);
        }
		void				GetHeightForWidth(float width, float* min, float* max, float* preferred) override {
        	PYBIND11_OVERLOAD(void, BTwoDimensionalLayout, GetHeightForWidth, width, min, max, preferred);
        }
		void				SetFrame(BRect frame) override {
        	PYBIND11_OVERLOAD(void, BTwoDimensionalLayout, SetFrame, frame);
        }
		status_t			Archive(BMessage* into, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BTwoDimensionalLayout, Archive, into, deep);
        }
		status_t			Perform(perform_code d, void* arg) override {
        	PYBIND11_OVERLOAD(status_t, BTwoDimensionalLayout, Perform, d, arg);
        }
        int32				InternalCountColumns() override {
        	PYBIND11_OVERLOAD_PURE(int32, BTwoDimensionalLayout, InternalCountColumns);
        }
        int32				InternalCountRows() override {
        	PYBIND11_OVERLOAD_PURE(int32, BTwoDimensionalLayout, InternalCountRows);
        }
        void				GetColumnRowConstraints(orientation orientation, int32 index, ColumnRowConstraints* constraints) override {
        	PYBIND11_OVERLOAD_PURE(void, BTwoDimensionalLayout, GetColumnRowConstraints, orientation, index, constraints);
        }
		void				GetItemDimensions(BLayoutItem* item, Dimensions* dimensions) override {
        	PYBIND11_OVERLOAD_PURE(void, BTwoDimensionalLayout, GetItemDimensions, item, dimensions);
        }
};

PYBIND11_MODULE(TwoDimensionalLayout,m)
{
py::class_<BTwoDimensionalLayout,PyBTwoDimensionalLayout, BAbstractLayout>(m, "BTwoDimensionalLayout")
.def(py::init(), "")
.def(py::init<BMessage *>(), "", py::arg("from"))
.def("SetInsets", py::overload_cast<float, float, float, float>(&BTwoDimensionalLayout::SetInsets), "", py::arg("left"), py::arg("top"), py::arg("right"), py::arg("bottom"))
.def("SetInsets", py::overload_cast<float, float>(&BTwoDimensionalLayout::SetInsets), "", py::arg("horizontal"), py::arg("vertical"))
.def("SetInsets", py::overload_cast<float>(&BTwoDimensionalLayout::SetInsets), "", py::arg("insets"))
.def("GetInsets", &BTwoDimensionalLayout::GetInsets, "", py::arg("left"), py::arg("top"), py::arg("right"), py::arg("bottom"))
.def("AlignLayoutWith", &BTwoDimensionalLayout::AlignLayoutWith, "", py::arg("other"), py::arg("orientation"))
.def("BaseMinSize", &BTwoDimensionalLayout::BaseMinSize, "")
.def("BaseMaxSize", &BTwoDimensionalLayout::BaseMaxSize, "")
.def("BasePreferredSize", &BTwoDimensionalLayout::BasePreferredSize, "")
.def("BaseAlignment", &BTwoDimensionalLayout::BaseAlignment, "")
.def("HasHeightForWidth", &BTwoDimensionalLayout::HasHeightForWidth, "")
.def("GetHeightForWidth", &BTwoDimensionalLayout::GetHeightForWidth, "", py::arg("width"), py::arg("min"), py::arg("max"), py::arg("preferred"))
.def("SetFrame", &BTwoDimensionalLayout::SetFrame, "", py::arg("frame"))
.def("Archive", &BTwoDimensionalLayout::Archive, "", py::arg("into"), py::arg("deep")=true)
.def("Perform", &BTwoDimensionalLayout::Perform, "", py::arg("d"), py::arg("arg"))
;
}
