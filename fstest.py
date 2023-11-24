import os
from Be import BNode
from Be.fs_attr import attr_info
#from structuple import Structuple

#class Battr_info(Structuple):
#	_members = ('type', 'size')
#	def typegen(self):
#		return (None, None)

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
		#if True:
		try:
			atri=str("")
			a = node.GetNextAttrName()
			#info=attr_info()
			#size = node.GetAttrInfo(a,info)
			#print(a,atri,size)
			#b+=1
			#if b==5:
			#	break
		except:
			#print("no next attr name")
			a = None
		if a is None:
			node.RewindAttrs()
			break
		else:
			#info = Battr_info(node.GetAttrInfo(a)) 
			#info = node.GetAttrInfo(a)
			al.append((a))#, info,  node.ReadAttr(atri, 0, 0, 1024)))
	return al

f=os.path.abspath("fstest.py")
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
