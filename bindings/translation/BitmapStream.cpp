#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <translation/BitmapStream.h>
#include <Bitmap.h>

namespace py = pybind11;
/*
status_t DetachBitmap_wrapper(BBitmapStream& self, std::vector<BBitmap*> _bitmap) {
	return self.DetachBitmap(_bitmap.data());
}*/

class PyBBitmapStream : public BBitmapStream{
	public:
        using BBitmapStream::BBitmapStream;
        ssize_t				ReadAt(off_t offset, void* buffer, size_t size) override {
        	PYBIND11_OVERLOAD(ssize_t, BBitmapStream, ReadAt, offset, buffer, size);
        }
		ssize_t				WriteAt(off_t offset, const void* buffer, size_t size) override {
        	PYBIND11_OVERLOAD(ssize_t, BBitmapStream, WriteAt, offset, buffer, size);
        }
		off_t				Seek(off_t position, uint32 seekMode) override {
        	PYBIND11_OVERLOAD(off_t, BBitmapStream, Seek, position, seekMode);
        }
		off_t				Position() const override {
        	PYBIND11_OVERLOAD(off_t, BBitmapStream, Position);
        }
		off_t				Size() const override {
        	PYBIND11_OVERLOAD(off_t, BBitmapStream, Size);
        }
		status_t			SetSize(off_t size) override {
        	PYBIND11_OVERLOAD(status_t, BBitmapStream, SetSize, size);
        }
};

PYBIND11_MODULE(BitmapStream,m)
{
py::class_<BBitmapStream, PyBBitmapStream, BPositionIO>(m, "BBitmapStream")
.def(py::init<BBitmap *>(), "", py::arg("bitmap")=NULL)
//.def("ReadAt", &BBitmapStream::ReadAt, "", py::arg("offset"), py::arg("buffer"), py::arg("size")) //convert buffer
.def("ReadAt", [](BBitmapStream& self, off_t offset, size_t size)->py::tuple{
	std::vector<char>buffer(size);
	ssize_t bytesRead = self.ReadAt(offset, buffer.data(), size);
	py::bytes pyBytes(buffer.data(),bytesRead);
	return py::make_tuple(pyBytes, bytesRead);
},"", py::arg("offset"),py::arg("size"))
//.def("WriteAt", &BBitmapStream::WriteAt, "", py::arg("offset"), py::arg("buffer"), py::arg("size")) //convert buffer
.def("WriteAt", [](BBitmapStream& self, off_t offset, py::buffer buffer){
	py::buffer_info info = buffer.request();
	const void* data = info.ptr;
	size_t length = info.size;
	return self.WriteAt(offset,data,length);
}, "",py::arg("offset"),py::arg("buffer"))
.def("Seek", &BBitmapStream::Seek, "", py::arg("position"), py::arg("seekMode"))
.def("Position", &BBitmapStream::Position, "")
.def("Size", &BBitmapStream::Size, "")
.def("SetSize", &BBitmapStream::SetSize, "", py::arg("size"))
//.def("DetachBitmap", &BBitmapStream::DetachBitmap, "", py::arg("_bitmap"))
//.def("DetachBitmap", &DetachBitmap_wrapper, "", py::arg("_bitmap")) //ok, it compiles, but... How do we pass the std::vector<BBitmap*> called _bitmap?
.def("DetachBitmap", [](BBitmapStream& self) {
        BBitmap* bitmap = nullptr;
        status_t status = self.DetachBitmap(&bitmap);
        
        if (bitmap != nullptr) {
            return py::make_tuple(status, py::cast(bitmap));
        } else {
            return py::make_tuple(status, py::none());
        }
})

;


}
