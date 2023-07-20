from haiku import BApplication, BWindow, BRect, BMessage, BView, BButton, window_type
 
class Window(BWindow):
    def __init__(self):
        BWindow.__init__(self, BRect(100,100,400,400), "Hola PyBind11", window_type.B_TITLED_WINDOW, 0)
        self.say_hi = BMessage(1)
        self.panel = BView(self.Bounds(), "panel", 8, 20000000)
        self.button = BButton(BRect(10,10,50,50), "hi", "Hola", self.say_hi)
        self.panel.AddChild(self.button, None)
        self.AddChild(self.panel, None)
        self.Show()
 
    def MessageReceived(self, msg):
        if msg.what == self.say_hi.what:
            print("SAY hi!")
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
