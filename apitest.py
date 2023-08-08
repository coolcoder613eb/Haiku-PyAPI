import os
import shlex
import subprocess
from api import App, Place, Button, TextInput, Label

ENTRY_LVL = 350


def run():
    text = textinput.text
    print('You entered', text)
    messages_label.text += os.getcwd() + '> ' + text + '\n'
    textinput.text = ''
    cmds = shlex.split(text)
    if cmds[0] == 'cd':
        os.chdir(cmds[1])
    elif text:
        output = subprocess.run(cmds, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, shell=True).stdout.decode()
        messages_label.text += output + '\n'


app = App(Place(100, 100, 500, 400), 'PyTerm')

messages_label = Label(app, Place(30, 20, 450, 340), 'Hello!\nWelcome to PyTerm\n')
button = Button(app, Place(400, ENTRY_LVL, 50), "OK", run)
textinput = TextInput(app, Place(30, ENTRY_LVL, 350), callback=run)
app.run()
