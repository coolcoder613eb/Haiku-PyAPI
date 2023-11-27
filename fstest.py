import os, struct, ctypes
from Be import BNode
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
		try:
			atri=str("")
			a = node.GetNextAttrName()
		except:
			a = None #no more attributes
		if a is None:
			node.RewindAttrs()
			break
		else:
			# you can do this way:
			#tmp = attr_info()
			#nfo = node.GetAttrInfo(a,tmp)
			#al.append((a,(tmp.type,tmp.size)))
			# or this way:
			nfo = node.GetAttrInfo(a)
			type_string = get_type_string(nfo.type)
			#print(get_type_int(type_string),nfo.type)
			my_obj = ctypes.py_object()
			#print(type(my_obj),my_obj)
			print(type_string, nfo.size)
			print(node.ReadAttr(a, nfo.type, 0, None,nfo.size))
			al.append((a,("Type:",type_string,"Size:",nfo.size),node.ReadAttr(a, nfo.type, 0, None,nfo.size)))#my_obj,
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

f=os.path.abspath("WPLaura.pdf")
#f=os.path.abspath("/boot/system/Tracker")#Haiku-friûl.png")#fstest.py")
carta=card(f)
#print(f)
nf = BNode(f)
print(attr(nf))
#for n, i, v in attr(nf):
#	carta.addattrib(n,v)
#	#if n[:5]=="META:":
#	#	z = v.find('\000')
#	#	if z >= 0:
#	#		v = v[:z]
#	#	carta.addattrib(n[5:],v)
#print(carta.attribs)
