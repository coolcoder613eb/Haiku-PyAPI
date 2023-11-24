import os, struct
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
			al.append((a,("Type:",type_string,"Size:",nfo.size),node.ReadAttr(a, 0, 0, None, 1024)))
			
	return al


def get_type_string(value):
	type_string = struct.pack('>I', value).decode('utf-8')
	return type_string

f=os.path.abspath("WPLaura.pdf")#Haiku-friûl.png")#fstest.py")
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