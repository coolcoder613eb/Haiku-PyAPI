from struct import unpack
from .AppDefs import *
from .Clipboard import *
from .Cursor import *
from .Handler import *
from .Invoker import *
from .Key import *
from .KeyStore import *
from .Looper import *
from .Application import * # has to be after looper
from .Message import *
from .MessageFilter import *
from .MessageQueue import *
from .MessageRunner import *
from .Messenger import *
from .Notification import *
from .PropertyInfo import *
from .Roster import *
from .Window import *
from .Rect import *
from .GraphicsDefs import *
from .Screen import *
from .Point import *
from .InterfaceDefs import *
from .View import *
from .Control import *
from .Button import *
from .TextControl import *
from .Font import *
from .StringView import *
from .Alert import *
from .TextView import *
from .Menu import *
from .MenuItem import *
from .MenuField import *
from .LayoutItem import *
from .Layout import *
from .AbstractLayout import *
from .TwoDimensionalLayout import *
from .GridLayout import *
from .PopUpMenu import *
from .Box import *
from .SeparatorItem import *
from .Alignment import *
from .SeparatorView import *
from .MenuBar import *
from .StatusBar import *
from .CheckBox import *
from .ColorControl import *
from .RadioButton import *
from .ListView import *
from .ScrollView import *
from .SupportDefs import *
from .TypeConstants import *
from .Archivable import *
from .ListItem import *
from .Bitmap import *
from .Picture import *
from .PictureButton import *
from .StringItem import *
from .TabView import *
from .ScrollBar import *
from .Shape import *
from .Size import *
from .Slider import *
from .Beep import *
from .Architecture import *
from .Locker import *
from .Autolock import *
from .DateTime import *
from .parsedate import *
from .List import *
from .String import *
from .Flattenable import *
from .StringList import *
from .DataIO import *

from .fs_attr import *

from .StorageDefs import *
from .Entry import *
from .Node import *
from .SymLink import *
from .Directory import *
from .File import *
from .Volume import *
from .VolumeRoster import *
from .Path import *
from .Statable import *
from .Resources import *
from .ResourceStrings import *
from .Query import *
#from .FilePanel import *

_BWindow=BWindow
_BApplication=BApplication
def MessageReceived(self, msg, parent):
    if msg.what in self.events:
        self.events[msg.what](msg)
    elif msg in self.events:
        self.events[msg](msg)
    else:
        print(parent,parent.MessageReceived)
        parent.MessageReceived(self, msg)

class BWindow(_BWindow):
    events={}
    MessageReceived=lambda self, msg: MessageReceived(self, msg,_BWindow)

class BApplication(_BApplication):
    events={}
    MessageReceived=lambda self, msg: MessageReceived(self, msg,_BApplication)


def int32(bytestr):
	return unpack('i',bytestr)[0]
