# There two ways to import Haiku-PyAPI
# First, you can import only the things you need
from Be import BApplication, BWindow, BRect, BMessage, BView, BButton, window_type,  B_NOT_RESIZABLE, B_QUIT_ON_WINDOW_CLOSE, int32, B_WILL_DRAW, B_FOLLOW_NONE
# Or import everything!
#from Be import *

# Usage of the API is extremely similar to how it is used in C++

class App(BApplication):
    def __init__(self):
        BApplication.__init__(
            self, # Any call to a constructor requires self as the first parameter
            "application/x-vnd.pyapi_test") # Application signature

    def ReadyToRun(self):
        # Display the main window
        window = MainWindow()
        window.Show()

class MainWindow(BWindow):
    def __init__(self):
        BWindow.__init__(
            self, # Any call to a constructor requires self as the first parameter
            BRect(100,100,200,150), # Window size
            "Hello Haiku!", # Window title
            window_type.B_TITLED_WINDOW, # Window type
            B_NOT_RESIZABLE | B_QUIT_ON_WINDOW_CLOSE) # Flags

        # The "Say Hello!" button's message code
        self.MSG_SAY_HI = int32(b"syhi")

        # The "Say Hello!" button
        self.button = BButton(
            self.Bounds(), # Button size
            "hi", # Internal name of button
            "Say Hello!", # Button text
            BMessage(self.MSG_SAY_HI)) # Message to send when button is pressed
        self.AddChild(self.button, None)

    def MessageReceived(self, msg):
        if msg.what == self.MSG_SAY_HI:
            # The "Say Hello!" button has been pressed!
            print("Hello World!")
        else:
            # We don't know what to do with this message. Pass it on to BWindow
            BWindow.MessageReceived(self, msg)

# Let's launch the application!
app = App()
app.Run()
