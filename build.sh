cd bindings
echo Compiling bindings...
g++ -shared -std=c++11 -fPIC -I/system/lib/python3.9/vendor-packages/pybind11/include/ -I/system/develop/headers/python3.9/ haiku.cpp -lbe -o _haiku.so
echo Finishing up...
cp _haiku.so ../api
mv _haiku.so ../bin
cd ..
