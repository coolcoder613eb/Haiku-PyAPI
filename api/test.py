from haiku import BApplication, BWindow, BRect, BMessage, BView, BButton, BTextControl, B_NOT_RESIZABLE, window_type
from sys import exit
 
class Window(BWindow):
    def __init__(self):
        BWindow.__init__(self, BRect(100,100,350,300), "Hello Haiku", window_type.B_TITLED_WINDOW, B_NOT_RESIZABLE)
        self.say_hi = BMessage(1)
        self.SEND_MSG = BMessage(2)
        self.panel = BView(self.Bounds(), "panel", 8, 20000000)
        self.button = BButton(BRect(30,90,100,50), "hi", "Say hi", self.say_hi)
        self.textinput = BTextControl(BRect(30 , 30, 200, 50), "textinput", None, "Sample text.",self.SEND_MSG)
        self.panel.AddChild(self.button, None)
        self.panel.AddChild(self.textinput, None)
        self.AddChild(self.panel, None)
        self.Show()
 
    def MessageReceived(self, msg):
        if msg.what == self.say_hi.what:
            print("hi!")
        elif msg.what == self.SEND_MSG.what:
            print('You said',self.textinput.Text())
        else:
            BWindow.MessageReceived(self, msg)
 
    def QuitRequested(self):
        print("PyQUIT")
        return True
 
class App(BApplication):
    def __init__(self):
        BApplication.__init__(self, "application/x-python")
        self.window = Window()
 
def main():
    a = App()
    a.Run()
 
if __name__ == "__main__":
    main()
