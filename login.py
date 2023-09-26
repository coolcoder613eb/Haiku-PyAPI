from Be import (
    BApplication,
    BWindow,
    BRect,
    BMessage,
    BView,
    BButton,
    BMessenger,
    window_type,
    B_TITLED_WINDOW,
    B_NOT_RESIZABLE,
    B_QUIT_REQUESTED,
    B_QUIT_ON_WINDOW_CLOSE,
)
import sys


class Window(BWindow):
    def __init__(self):
        BWindow.__init__(
            self,
            BRect(100, 100, 200, 150),
            "Hello Haiku!",
            B_TITLED_WINDOW,
            0,
            #B_NOT_RESIZABLE | B_QUIT_ON_WINDOW_CLOSE,
        )
        self.say_hi = BMessage(1)
        self.panel = BView(self.Bounds(), "panel", 8, 20000000)
        self.button = BButton(
            self.panel.Bounds(), "hi", "Say Hello!", self.say_hi
        )  # BRect(10,10,100,50)
        self.panel.AddChild(self.button, None)
        self.AddChild(self.panel, None)

    def MessageReceived(self, msg):
        # print(msg)
        if msg.what == self.say_hi.what:
            print("Hello World!")
        else:
            BWindow.MessageReceived(self, msg)

    def QuitRequested(self):
        print("PyQUIT")
        #app.Lock()
        app.Quit()
        return True


class App(BApplication):
    def __init__(self):
        BApplication.__init__(self, "application/x-python")

    def ReadyToRun(self):
        self.window = Window()
        self.window.Show()
        
    def QuitRequested(self):
        print("PyAppQUIT")
        return True


def main():
    app = App()
    print(app.Run())
    print("Ran")
    app.Quit()


if __name__ == "__main__":
    app = App()
    print(app.Run())
    print("Ran")
    print("returned")
    # sys.exit()
print("done")
