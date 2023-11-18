from Be import BApplication, BWindow, BListItem, BTabView, BTab, BFont, BPicture, BStringItem, BAlert, BPoint, BBox, BListView, BScrollView, BRadioButton, BColorControl, BCheckBox, BRect, BTextControl, BView,BMenu,BStatusBar, BMenuBar, BMenuItem,BSeparatorItem,BStringView,BMessage,window_type,  B_NOT_RESIZABLE, B_QUIT_ON_WINDOW_CLOSE
#from Be import BListItem #BStringItem
from Be.GraphicsDefs import *#rgb_color
from Be.ListView import list_view_type
from Be.Alert import alert_type
from Be.ColorControl import color_control_layout
from Be import InterfaceDefs
from Be.InterfaceDefs import border_style
from Be import AppDefs

class StrangeItem(BStringItem):
	nocolor = (0, 0, 0, 0)
	gcolor = (0, 200, 0, 0)
	def __init__(self, testo,colore):
		self.testo = testo
		self.color = colore
		BStringItem.__init__(self,testo)
	def Text(self):
		return self.testo
	def Color(self):
		return self.color
	def DrawItem(self,owner,frame,complete):
		print("dissegno StrangeItem")
		if self.IsSelected() or complete:
			color = (50,50,50,255)
			owner.SetHighColor(50,50,50,255)
			owner.SetLowColor(50,50,50,255)
			#owner.FillRect(frame)
			self.color=self.nocolor
		owner.SetHighColor(0, 200, 0, 0)
		#owner.MovePenTo(0,frame.Height()-2)
		#owner.DrawString(self.testo)
		owner.SetLowColor(255,255,255,255)
		BStringItem.DrawItem(self,owner,frame,complete)

class NewsItem(BListItem):
	nocolor = (0, 0, 0, 0)

	def __init__(self, name,color):
		self.name = name
		self.color=color
		BListItem.__init__(self)

	def DrawItem(self, owner, frame, complete):
		if self.IsSelected() or complete:
			color = (200,200,200,255)
			owner.SetHighColor(200,200,200,255)
			owner.SetLowColor(200,200,200,255)
			paternale=Pattern()
			paternale.data=[0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff]
			#paternale = [0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff]
			BView.FillRect(frame,paternale.toPattern())
			#owner.FillRect(frame)
			self.color=self.nocolor
#		#owner.SetHighColor(self.color)
#		#if self.color == (200,0,0,0):
#		#	self.font = be_bold_font
#		#	owner.SetFont(self.font)
#		#else:	
#		#	self.font = be_plain_font
#		#	owner.SetFont(self.font)
		frame.PrintToStream()
		owner.MovePenTo(0,frame.Height()-2)
		owner.DrawString("->"+self.name,None)
#		#owner.SetLowColor((255,255,255,255))
		#BListItem.DrawItem(self,owner,frame,complete)

	def Text(self):
		return self.name


class ScrollView:
	HiWhat = 32 #Doppioclick
	def __init__(self, rect, name):
		self.lv = BListView(rect, name, list_view_type.B_SINGLE_SELECTION_LIST)
		self.sv = BScrollView('ScrollView', self.lv)#, 0x0202,0,False,False, border_style.B_FANCY_BORDER)#|0x1030

	def topview(self):
		return self.sv

	def listview(self):
		return self.lv

class Window(BWindow):
	Menus = (
		('File', ((1, 'asd'),(2, 'lol'),(5, 'bubu'),(None, None),(AppDefs.B_QUIT_REQUESTED, 'Quit'))),
		('Help', ((8, 'Help'),(3, 'About')))
		)
	CLRCTL = 4
	
	def __init__(self):
		BWindow.__init__(self, BRect(100,100,600,750), "Hello Haiku!", window_type.B_TITLED_WINDOW,  B_NOT_RESIZABLE | B_QUIT_ON_WINDOW_CLOSE)
		bounds=self.Bounds()
		self.bckgnd = BView(self.Bounds(), "background", 8, 20000000)
		self.maintabview = BTabView(BRect(2.0, 2.0, bounds.Width()-2.0, bounds.Height()-2.0), 'tabview')
		print(bounds.LeftTop())
		self.panel = BView(self.Bounds(), "panel", 8, 20000000)
		self.box = BBox(BRect(10,26,90,51),"MYBox",0x0202|0x0404,InterfaceDefs.border_style.B_FANCY_BORDER)
		#self.box.SetHighColor(0, 200, 0, 0)
		#paternale=Pattern()
		#paternale.data=[0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff]
		#self.box.FillRect(self.box.Bounds(),paternale.toPattern())
		self.bar = BMenuBar(self.box.Bounds(), 'Bar')
		self.testo = BStringView(BRect(5,5,75,20), 'Test','prova')
		self.box.AddChild(self.testo,None)
		self.statbar = BStatusBar(BRect(10,70,bounds.Width()/3-15,144), 'progress','0%', '100%')
		self.statbar.SetMaxValue(100.0)
		self.tachetest=BTextControl(BRect(57,bounds.Height()-30,bounds.Width()-57,bounds.Height()-12),'TxTView', "prova:",None,BMessage(1),0x0202|0x0404)
		self.tachetest.SetDivider(55.0)
		self.startimer= BCheckBox(BRect(10,30,290,50),'Testbox','Test Checkbox',BMessage(612))
		self.point=BPoint()
		self.cc= BColorControl(BPoint(8, 128), color_control_layout.B_CELLS_32x8, 8.0,'colors', BMessage(self.CLRCTL), 0)
		self.sixradio = BRadioButton(BRect(8,220,24,236),'hotradio', 'hot', BMessage(6))
		self.sevenradio = BRadioButton(BRect(8,236,24,252),'tepidradio', 'tepid', BMessage(7))
		self.nineradio = BRadioButton(BRect(8,252,24,268),'coolradio', 'cool', BMessage(9))
		self.list = ScrollView(BRect(18 , 300, bounds.Width() - 18 , bounds.Height() - 40 ), 'ScrollView')
		colore=self.list.lv.HighColor()
		print("colore è:",colore.red,colore.green,colore.blue,colore.alpha)
		colore.set_to(10,200,100,255)
		print("colore modificato è:",colore.red,colore.green,colore.blue,colore.alpha)
		self.list.lv.SetHighColor(colore)
		self.list.lv.SetLowColor(colore)
		lollo=BPicture()
		self.list.sv.Hide()
		global newsitem
			# TODO: newsitem (defined below) seems to be freed by Python as soon
			# as Python is finished with the __init__ function. But we still
			# need to have it around afterwards. The goal of this hack is to
			# make it that Python never frees NewsItem. The actual fix would
			# involve something like Haiku-PyAPI telling Python that it has a
			# reference to NewsItem and so cannot free it until Haiku-PyAPI
			# is finished with it
		newsitem = NewsItem("Nuova",(255,0,0,0))
		self.elementolista=BStringItem("Questo è un BStringItem")
		#global strano
		strano = StrangeItem("Questo è un StrangeItem",(0,200,0,0))
		print(type(self.list.lv))
		print(self.list.lv.Items())
		print(self.list.lv.CountItems())
		self.list.lv.AddItem(newsitem)
		self.list.lv.AddItem(self.elementolista)
		self.list.lv.AddItem(strano)
		print(self.list.lv.Items())
		print(self.list.lv.IndexOf(self.elementolista))
		self.list.sv.Show()
		#self.panel.AddChild(self.list.topview(),None)
		self.panel.AddChild(self.sixradio,None)
		self.panel.AddChild(self.sevenradio,None)
		self.panel.AddChild(self.nineradio,None)
		self.panel.AddChild(self.cc,None)
		self.panel.AddChild(self.startimer,None)
		self.panel.AddChild(self.tachetest,None)
		self.panel.AddChild(self.statbar,None)
		self.panel.AddChild(self.bar,None)
		for menu, items in self.Menus:
			menu = BMenu(menu)
			for k, name in items:
				if k is None:
						menu.AddItem(BSeparatorItem())
				else:
						menu.AddItem(BMenuItem(name, BMessage(k),name[1],0))
			self.bar.AddItem(menu)
		self.tabslabels=[]
		self.tabsviews=[]
		self.tabsviews.append(self.panel)
		#testotab=[]
		#for char in "Principale":
		#	testotab.append(char)
		#outarray=[]
		#BFont.GetStringWidths(testotab,len(testotab),1,outarray)#StringWidth(chr(ord("P")))
		#print(outarray)
		tabrect=BRect(3.0, 3.0, 30.0, self.maintabview.TabHeight()-3.0)
		#bviewtab=BStringView(tabrect,"scheda1","Princpiale")
		scheda=BTab(None)#bviewtab)#self.maintabview)
		scheda.SetLabel("Principale")
		self.tabslabels.append(scheda)
		self.maintabview.AddTab(self.tabsviews[0],scheda)#self.tabsviews[0],self.tabslabels[0])
		self.bckgnd.AddChild(self.maintabview,None)
		scheda.SetLabel("Principale")
		self.AddChild(self.bckgnd,None)
		self.panel.AddChild(self.list.topview(),None)
		
	def MessageReceived(self, msg):
		if msg.what == 1:
			self.startimer.SetValue(not(self.startimer.Value()))
		elif msg.what == 2:
			x=round(self.statbar.CurrentValue())
			if x<100:
				outtxt=str(x+1)+"%"
				self.statbar.Update(1.0,outtxt,"100%")
		elif msg.what == 8:
			ask = BAlert('Whoa!', 'Are you sure you need help?', 'Yes','No', None, InterfaceDefs.B_WIDTH_AS_USUAL, alert_type.B_IDEA_ALERT)
			answ=ask.Go()
			if answ==0:
				risp = BAlert('lol', 'Well there\'s no help manual here', 'Bummer', None,None,InterfaceDefs.B_WIDTH_AS_USUAL,alert_type.B_INFO_ALERT)
				risp.Go()
			else:
				risp = BAlert('lol', 'If you think so...', 'Poor me', None,None,InterfaceDefs.B_WIDTH_AS_USUAL,alert_type.B_WARNING_ALERT)
				risp.Go()
		BWindow.MessageReceived(self, msg)
		
	def QuitRequested(self):
		print ("So long and thanks for all the fish")
		return BWindow.QuitRequested(self)
		
class App(BApplication):
    def __init__(self):
        BApplication.__init__(self, "application/x-python")
    def ReadyToRun(self):
        self.window = Window()
        self.window.Show()

def main():
    global be_app
    be_app = App()
    be_app.Run()
    print('so said dolphins...')
 
if __name__ == "__main__":
    main()
