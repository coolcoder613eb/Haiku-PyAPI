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
from .Polygon import *
from .Region import *
from .GraphicsDefs import *
from .Screen import *
from .Point import *
from .InterfaceDefs import *
from .View import *
from .Control import *
#from .OptionControl import *
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
from .AbstractLayoutItem import *
from .TwoDimensionalLayout import *
from .GridLayout import *
from .GridLayoutBuilder import *
from .GroupLayout import *
from .GroupLayoutBuilder import *
from .LayoutContext import *
from .LayoutUtils import *
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
from .OutlineListView import *
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
from .CardLayout import *
from .CardView import *
from .ChannelControl import *
from .ChannelSlider import *
from .ControlLook import *
from .Deskbar import *
from .Gradient import *
from .GradientConic import *
from .GradientDiamond import *
from .GradientLinear import *
from .GradientRadial import *
from .GradientRadialFocus import *
from .GridView import *
from .Dragger import *
#from .IconUtils import *
from .Input import *
from .PrintJob import *

from .Beep import *
from .Architecture import *
from .Locker import *
from .Autolock import *
from .DateTime import *
from .parsedate import *
from .List import *
from .String import *
from .Flattenable import *
from .AffineTransform import *
from .StringList import *
from .DataIO import *
from .Url import *

from .fs_attr import *

from .StorageDefs import *
from .Statable import *
from .Entry import *
from .Node import *
from .SymLink import *
from .File import *
from .Volume import *
from .VolumeRoster import *
from .Path import *
from .FindDirectory import *
from .PathFinder import *

from .Mime import *
from .MimeType import *
from .NodeInfo import *
from .AppFileInfo import *
from .Resources import *
from .ResourceStrings import *
from .EntryList import *
from .Directory import *
from .Query import *
from .NodeMonitor import *
from .NodeInfo import *
#from .DiskDeviceDefs import *
from .FilePanel import *

from .TranslationDefs import *
from .TranslatorRoster import *
from .TranslationUtils import *
from .Translator import *
from .stat import *

#from .ScreenSaver import *
#from .MimeSnifferAddon import *
#from .Accelerant import *
#from .GraphicsCard import *
#from .InputServerDevice import *
#from .InputServerFilter import *
#from .InputServerMethod import *
#from .MailFilter import *
#from .MailSettingsView import *
#from .MailProtocol import *
#from .NetworkProfile import *
#from .NetworkSettings import *
#from .NetworkSettingsAddOn import *

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
