def do(src,dst):
    g++ -shared -std=c++14 -fPIC -I/system/lib/python3.9/vendor-packages/pybind11/include/ -I/system/develop/headers/python3.9/ @(src) -lbe -o @(dst)

cd bindings
files={'app':('AppDefs','Application','Clipboard',
'Cursor','Handler','Invoker',
'Key','KeyStore','Looper',
'Message','MessageFilter','MessageQueue',
'PropertyInfo','Roster'),
'interface':('Window','Rect','View',
'Button')}
for dir in files.keys():
    cd @(dir)
    for file in files[dir]:
        do(file+'.cpp',file+'.so')
    mv *.so @('../../bin/'+dir)
    cd ..
cd ..
