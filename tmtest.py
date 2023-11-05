from Be import BApplication, BWindow,BBox, BRect, BView,BMenu, BMenuBar, BMenuItem,BSeparatorItem,BStringView,BMessage,window_type,  B_NOT_RESIZABLE, B_QUIT_ON_WINDOW_CLOSE
from Be import InterfaceDefs
from Be import AppDefs


class Window(BWindow):
	Menus = (
		('File', ((1, 'asd'),(2, 'lol'),(5, 'bubu'),(None, None),(AppDefs.B_QUIT_REQUESTED, 'Quit'))),
		('Help', ((8, 'Help'),(3, 'About')))
		)
	def __init__(self):
		BWindow.__init__(self, BRect(100,100,200,150), "Hello Haiku!", window_type.B_TITLED_WINDOW,  B_NOT_RESIZABLE | B_QUIT_ON_WINDOW_CLOSE)
		self.panel = BView(self.Bounds(), "panel", 8, 20000000)
		self.underbox = BBox(self.panel.Bounds(),"underbox",0x0202|0x0404,InterfaceDefs.border_style.B_FANCY_BORDER)
		self.box = BBox(BRect(10,20,90,45),"MYBox",0x0202|0x0404,InterfaceDefs.border_style.B_FANCY_BORDER)
		self.bar = BMenuBar(self.box.Bounds(), 'Bar')
		self.testo = BStringView(BRect(5,5,75,20), 'Test','prova')
		self.box.AddChild(self.testo,None)
		self.underbox.AddChild(self.box,None)
		self.underbox.AddChild(self.bar,None)
		self.panel.AddChild(self.underbox,None)
		for menu, items in self.Menus:
			menu = BMenu(menu)
			for k, name in items:
				if k is None:
						menu.AddItem(BSeparatorItem())
				else:
						msg = BMessage(k)
						menu.AddItem(BMenuItem(name, msg,name[1],0))
			self.bar.AddItem(menu)
		if self.bar.FindItem("bubu"):
			print("yay")
		else:
			print("noo")
		print(self.bar.FindItem("lol"))#.SetMarked(0) not working not found 
		self.AddChild(self.panel,None)
		
	def MessageReceived(self, msg):
		print(msg)
		BWindow.MessageReceived(self, msg)
		
	def QuitRequested(self):
		print ("So long and thanks for all the fish")
		be_app.PostMessage(BMessage(AppDefs.B_QUIT_REQUESTED))
		return 1
		
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
