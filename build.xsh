#!/usr/bin/env xonsh
from sys import argv
def do(src,dst):
    g++ -shared -std=c++14 -pipe -fPIC -I/system/lib/python3.9/vendor-packages/pybind11/include/ -I/system/develop/headers/python3.9/ @(src) -lbe -o @(dst)

ARCH=$(uname -p).strip()

cd bindings
files={('interface','InterfaceKit'):('InterfaceDefs','Alert','Button','Control',
 'Rect','StringView','TextControl',
 'View','Window','Font'),
 ('app','AppKit'):('AppDefs','Application','Clipboard',
'Cursor','Handler','Invoker',
'Key','KeyStore','Looper',
'Message','MessageFilter','MessageQueue',
'MessageRunner','Messenger','Notification',
'PropertyInfo','Roster'),
}
todo=files.keys()
if len(argv) > 1:
    todo=[]
    for x in argv[1:]:
        for y in files.keys():
            if y[0] == x:
                todo.append(y)

sources=[]
for dir in todo:
	sources.extend([dir[0]+'/'+file+'.cpp' for file in files[dir]])

do(sources,'Be.so')
mv Be.so @('../bin/'+ARCH)
cd @('../bin/'+ARCH)
for file in sources:
    ln -s Be.so @(file.split('/')[-1].removesuffix('.cpp')+'.so')
cd ..

