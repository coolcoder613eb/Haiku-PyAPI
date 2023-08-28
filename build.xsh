#!/usr/bin/env xonsh
def do(src,dst):
    g++ -shared -std=c++14 -pipe -fPIC -I/system/lib/python3.9/vendor-packages/pybind11/include/ -I/system/develop/headers/python3.9/ @(src) -lbe -o @(dst)

cd bindings
files={('app','AppKit'):('AppDefs','Application','Clipboard',
'Cursor','Handler','Invoker',
'Key','KeyStore','Looper',
'Message','MessageFilter','MessageQueue',
'PropertyInfo','Roster'),
('interface','InterfaceKit'):('Button',
 'Control',
 'Rect',
 'StringView',
 'TextControl',
 'View',
 'Window')}
for dir in files.keys():
    cd @(dir[0])
    do([file+'.cpp' for x in files[dir]],dir[1]+'.so')
    mv *.so @('../../bin/'+dir[0])
    for file in files[dir]:
        ln -s @(dir[1]+'.so') @(file+'.so')
    cd ..
cd ..
