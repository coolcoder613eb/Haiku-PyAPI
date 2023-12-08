#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
//#include <pybind11/numpy.h>

#include <Resources.h>

namespace py = pybind11;
//using namespace BPrivate;
//using namespace BPrivate::Storage;
//using namespace BPrivate::Storage::Mime;
//using namespace BPackageKit;
/*
std::vector<char*> convertConstCharPtrArray(const char** constCharPtrArray, std::size_t size) {
    std::vector<char*> charPtrVector;

    for (std::size_t i = 0; i < size; ++i) {
        // Copia ogni stringa di caratteri nel vettore
        charPtrVector.push_back(const_cast<char*>(constCharPtrArray[i]));
    }

    return charPtrVector;
}*/

PYBIND11_MODULE(Resources, m)
{
//m.attr("ResourcesContainer") = py::cast(ResourcesContainer);

//m.attr("ResourceFile") = py::cast(ResourceFile);

py::class_<BResources>(m, "BResources")
.def(py::init(), "")
.def(py::init<const BFile *, bool>(), "", py::arg("file"), py::arg("clobber")=false)
.def(py::init<const char *, bool>(), "", py::arg("path"), py::arg("clobber")=false)
.def(py::init<const entry_ref *, bool>(), "", py::arg("ref"), py::arg("clobber")=false)
.def("SetTo", py::overload_cast<const BFile *, bool>(&BResources::SetTo), "", py::arg("file"), py::arg("clobber")=false)
.def("SetTo", py::overload_cast<const char *, bool>(&BResources::SetTo), "", py::arg("path"), py::arg("clobber")=false)
.def("SetTo", py::overload_cast<const entry_ref *, bool>(&BResources::SetTo), "", py::arg("ref"), py::arg("clobber")=false)
.def("SetToImage", py::overload_cast<image_id, bool>(&BResources::SetToImage), "", py::arg("image"), py::arg("clobber")=false)
.def("SetToImage", py::overload_cast<const void *, bool>(&BResources::SetToImage), "", py::arg("codeOrDataPointer"), py::arg("clobber")=false)
.def("Unset", &BResources::Unset, "")
.def("InitCheck", &BResources::InitCheck, "")
.def("File", &BResources::File, "")
.def("LoadResource", py::overload_cast<type_code, int32, size_t *>(&BResources::LoadResource), "", py::arg("type"), py::arg("id"), py::arg("_size")) // should we keep these 2 functions? they return const void *
.def("LoadResource", py::overload_cast<type_code, const char *, size_t *>(&BResources::LoadResource), "", py::arg("type"), py::arg("name"), py::arg("_size")) //
.def("PreloadResourceType", &BResources::PreloadResourceType, "", py::arg("type")=0)
.def("Sync", &BResources::Sync, "")
.def("MergeFrom", &BResources::MergeFrom, "", py::arg("fromFile"))
.def("WriteTo", &BResources::WriteTo, "", py::arg("file"))
.def("AddResource", &BResources::AddResource, "", py::arg("type"), py::arg("id"), py::arg("data"), py::arg("length"), py::arg("name")=NULL) // to change <- cannot pass void* data from python
.def("HasResource", py::overload_cast<type_code, int32>(&BResources::HasResource), "", py::arg("type"), py::arg("id"))
.def("HasResource", py::overload_cast<type_code, const char *>(&BResources::HasResource), "", py::arg("type"), py::arg("name"))
//.def("GetResourceInfo", py::overload_cast<int32, type_code *, int32*, const char * *, size_t *>(&BResources::GetResourceInfo), "", py::arg("byIndex"), py::arg("typeFound"), py::arg("idFound"), py::arg("nameFound"), py::arg("lengthFound"))
/*.def("GetResourceInfo", [](BResources& self, int32 byIndex) {
    type_code typeFound;
    int32 idFound;
    const char* nameFound;
    size_t lengthFound;
    bool result = self.GetResourceInfo(byIndex, &typeFound, &idFound, &nameFound, &lengthFound);

    // Creare una lista Python per contenere i risultati
    py::list resultList;

    // Iterare attraverso i dati restituiti estrarre ciascun blocco
    size_t currentIndex = 0;
    while (currentIndex < lengthFound) {
        // Trova la lunghezza del blocco corrente
        size_t currentBlockLength = strlen(nameFound + currentIndex);

        // Estrai il blocco corrente
        std::string currentBlock(nameFound + currentIndex, currentBlockLength);

        // Aggiungi il blocco alla lista Python
        resultList.append(py::bytes(currentBlock));

        // Passa al prossimo blocco
        currentIndex += currentBlockLength + 1;  // +1 per includere il terminatore nullo
    }

    return py::make_tuple(result, static_cast<int>(typeFound), idFound, resultList);
}, "", py::arg("byIndex"))*/
.def("GetResourceInfo", [](BResources& self, int32 byIndex){
    type_code typeFound;
    int32 idFound;
    const char * nameFound;
    size_t lengthFound;
    bool result = self.GetResourceInfo(byIndex, &typeFound, &idFound, &nameFound, &lengthFound);
    
    py::bytes byteSequence(nameFound, lengthFound);

    return py::make_tuple(result, static_cast<int>(typeFound), idFound, byteSequence, lengthFound);
}, "", py::arg("byIndex")) //<- this works
//.def("GetResourceInfo", py::overload_cast<type_code, int32, int32*, const char * *, size_t *>(&BResources::GetResourceInfo), "", py::arg("byType"), py::arg("andIndex"), py::arg("idFound"), py::arg("nameFound"), py::arg("lengthFound"))
.def("GetResourceInfo_byTypeAndIndex", [](BResources& self, type_code byType, int32 andIndex){
    int32 idFound;
    const char * nameFound;
    size_t lengthFound;
    bool result = self.GetResourceInfo(byType, andIndex, &idFound, &nameFound, &lengthFound);

    py::bytes byteSequence(nameFound, lengthFound);

    return py::make_tuple(result, idFound, byteSequence, lengthFound);
}, "", py::arg("byType"), py::arg("andIndex"))
//.def("GetResourceInfo", py::overload_cast<type_code, int32, const char * *, size_t *>(&BResources::GetResourceInfo), "", py::arg("byType"), py::arg("andID"), py::arg("nameFound"), py::arg("lengthFound"))
.def("GetResourceInfo_byTypeAndID", [](BResources& self, type_code byType, int32 andID){
    const char * nameFound;
    size_t lengthFound;
    bool result = self.GetResourceInfo(byType, andID, &nameFound, &lengthFound);

    py::bytes byteSequence(nameFound, lengthFound);

    return py::make_tuple(result, byteSequence, lengthFound);
}, "", py::arg("byType"), py::arg("andID"))
//.def("GetResourceInfo", py::overload_cast<type_code, const char *, int32*, size_t *>(&BResources::GetResourceInfo), "", py::arg("byType"), py::arg("andName"), py::arg("idFound"), py::arg("lengthFound"))// <- TODO!!
.def("GetResourceInfo", [](BResources& self, type_code byType, const char* andName){
    int32 idFound;
    size_t lengthFound;
    bool result = self.GetResourceInfo(byType, andName, &idFound, &lengthFound);

    return py::make_tuple(result, idFound, lengthFound);
}, "", py::arg("byType"), py::arg("andName"))
//.def("GetResourceInfo", py::overload_cast<const void *, type_code *, int32*, size_t *, const char * *>(&BResources::GetResourceInfo), "", py::arg("byPointer"), py::arg("typeFound"), py::arg("idFound"), py::arg("lengthFound"), py::arg("nameFound")) //<- There's no pointer in Python
.def("RemoveResource", py::overload_cast<const void *>(&BResources::RemoveResource), "", py::arg("resource"))
.def("RemoveResource", py::overload_cast<type_code, int32>(&BResources::RemoveResource), "", py::arg("type"), py::arg("id"))
.def("WriteResource", &BResources::WriteResource, "", py::arg("type"), py::arg("id"), py::arg("data"), py::arg("offset"), py::arg("length"))
.def("ReadResource", &BResources::ReadResource, "", py::arg("type"), py::arg("id"), py::arg("data"), py::arg("offset"), py::arg("length"))
.def("FindResource", py::overload_cast<type_code, int32, size_t *>(&BResources::FindResource), "", py::arg("type"), py::arg("id"), py::arg("lengthFound"))
.def("FindResource", py::overload_cast<type_code, const char *, size_t *>(&BResources::FindResource), "", py::arg("type"), py::arg("name"), py::arg("lengthFound"))
;


}
