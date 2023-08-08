from .haiku import *

DEBUG = True


class Place(BRect):
    def __init__(self, x, y, width=None, height=None):
        super().__init__(x, y, x + width if width else 0, y + height if height else 0)


class Button(BButton):
    def __init__(self, parent, place, label='', callback=object):
        self.parent = parent
        self.msg = BMessage(len(self.parent.window.messages))
        super().__init__(place, None, label, self.msg)
        self.parent.window.messages.append(callback)
        self.parent.window.panel.AddChild(self, None)


class TextInput(BTextControl):
    def __init__(self, parent, place, label=None, text=None, callback=object):
        self.parent = parent
        self.msg = BMessage(len(self.parent.window.messages))
        super().__init__(place, None, label, text, self.msg)
        self.parent.window.messages.append(callback)
        self.parent.window.panel.AddChild(self, None)

    @property
    def text(self):
        return self.Text()

    @text.setter
    def text(self, text):
        self.SetText(text)


class Label(BStringView):
    def __init__(self, parent, place, text=None):
        self.parent = parent
        super().__init__(place, None, text)
        self.parent.window.panel.AddChild(self, None)

    @property
    def text(self):
        return self.Text()

    @text.setter
    def text(self, text):
        self.SetText(text)


class Window(BWindow):
    def __init__(self, place, title, resizable=True):
        if resizable:
            BWindow.__init__(self, place, title, window_type.B_TITLED_WINDOW, 0)
        else:
            BWindow.__init__(self, place, title, window_type.B_TITLED_WINDOW, B_NOT_RESIZABLE)

        self.messages = []

        self.panel = BView(self.Bounds(), "panel", 8, 20000000)

        self.AddChild(self.panel, None)
        self.Show()

    def MessageReceived(self, msg):
        # print(self.messages, msg.what)
        if len(self.messages) > msg.what:
            self.messages[msg.what]()
        else:
            BWindow.MessageReceived(self, msg)

    def QuitRequested(self):
        if DEBUG: print("PyQUIT")
        return True


class App(BApplication):
    def __init__(self, place, title="Python", signature="application/x-python"):
        super().__init__(signature)
        self.window = Window(place, title)

    def run(self):
        self.Run()
