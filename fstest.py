import os, sys, struct#, ctypes
from Be import BApplication,BNode,BEntry,BBitmap
from Be.Entry import entry_ref
from Be import BMimeType,BRect
from Be.Mime import icon_size
from Be.GraphicsDefs import *
#from Be.GraphicsDefs import color_space
from Be.fs_attr import attr_info

class card:
	def __init__(self,path):
		self.path = path
		self.attribs = []
	def addattrib(self,n,v):
		att=(n,v)
		self.attribs.append(att) 
	def retattrib(self):
		return self.attribs

def attr(node):
	al = []
	while 1:
		#try:
			#atri=str("")
			#a = node.GetNextAttrName()
		#except:
		#	a = None #no more attributes
		an = node.GetNextAttrName()
		if not an[1]:
			a = an[0]
		else:
			a = None
		if a is None:
			node.RewindAttrs()
			break
		else:
			# you can do this way:
			#tmp = attr_info()
			#nfo = node.GetAttrInfo(a,tmp)
			# or this way:
			pnfo = node.GetAttrInfo(a)
			if not pnfo[1]:
				nfo = node.GetAttrInfo(a)[0]
				
			type_string = get_type_string(nfo.type)
			#print(get_type_int(type_string),nfo.type)
			#my_obj = ctypes.py_object()
			#print(type(my_obj),my_obj)
			print("Attr_name:",a,"Type:",type_string,"Size:", nfo.size,"Value:",node.ReadAttr(a, nfo.type, 0, None,nfo.size))
			if a == "Media:Width":
				print("Attempt to change AttribName")
				node.RenameAttr("Media:Width", "media:width")# <- not working
				print("Name after RenameAttr:",a)
				
			al.append((a,("Type:",type_string,"Size:",nfo.size),node.ReadAttr(a, nfo.type, 0, None,nfo.size)))#my_obj,
			#node.RemoveAttr("Media:Width") <- works
	return al

def get_type_int(stringa):
	value=0
	for i in range(4):
		value |= ord(stringa[i]) << (8*(3-i))
	return value

def get_type_string(value):
	#type_string = ''.join([chr((value >> (8*i)) & 0xFF) for i in range(4)]) #<--- this works better if the binary representation of the integer contains bytes that are not valid for UTF-8 encoding
	type_string = struct.pack('>I', value).decode('utf-8')
	return type_string
	
	

class App(BApplication):
	def __init__(self):
		BApplication.__init__(self, "application/x-python")
	def ReadyToRun(self):
		f=os.path.abspath(sys.argv[1])
		#f=os.path.abspath("WPLaura.pdf")
		#f=os.path.abspath("/boot/system/Tracker")#Haiku-friûl.png")#fstest.py")
		carta=card(f)
		#print(f)
		nf = BNode(f)
		print(attr(nf))
		en=BEntry(f)
		ref=entry_ref()
		en_ref=en.GetRef(ref)
		static = BMimeType()
		mime = BMimeType.GuessMimeType(f,static)
		if mime == 0:
			print(static.Type())
		#TESTING MIMETYPE GETICON
		## testing geticon with raw data, most similar to c++ func
		dataicon = []
		dim = 0
		static.GetIcon(dataicon,dim)# <--- dim is 0
		############################
		## testing with BBitmap, most similar to c++ func
		icnbrdr = BRect(0.0, 0.0, 15.0, 15.0)
		icon=BBitmap(icnbrdr,color_space.B_RGBA32)
		bitti= icon.Bits()
		static.GetIcon(icon,icon_size.B_MINI_ICON)
		ribitti=icon.Bits()
		if bitti == ribitti:
			print("nothing changed")
		else:
			print("the new bitmap bits are:",ribitti)
		#############################
		## test geticon with BBitmap, return tuple
		#vale,icona=static.GetIcon(icon_size.B_MINI_ICON)
		#if vale:
		#	print("icona bitmap ottuenuta")
		#	print(icona)
		#############################
		## test geticon with raw data, return tuple <--- this works
		#vale,iconaraw=static.GetIcon()
		#if vale==0:
		#	print("icona raw ottenuta")
		#	print(iconaraw)
		self.Quit()
	
	
	
#for n, i, v in attr(nf):
#	carta.addattrib(n,v)
#	#if n[:5]=="META:":
#	#	z = v.find('\000')
#	#	if z >= 0:
#	#		v = v[:z]
#	#	carta.addattrib(n[5:],v)
#print(carta.attribs)
def main():
    global be_app
    be_app = App()
    be_app.Run()
 
if __name__ == "__main__":
    main()
