# Tests that a Python class subclassing BLooper is not "forgotten" as soon as
# Python no longer holds any references to it, even though C++ is still using
# it.
#
# The more complicated, fuller explanation:
# This "forgetting" is caused by Python being unaware that C++ holds a
# reference to the Python subclass. So, once Python no longer holds any
# references, it frees the subclass. This, in effect, removes all of the method
# overrides of the base class and leads to methods of the base class being
# called directly.

from Be import BLooper, BMessenger, B_QUIT_REQUESTED
import time

looper_quit_called = False
looper_deleted = False

# The main character of this test is TestLooper
class TestLooper(BLooper):
	def __init__(self):
		BLooper.__init__(self, "TestLooper")
		
	def Quit(self):
		global looper_quit_called
		looper_quit_called = True
		BLooper.Quit(self)
	
	def __del__(self):
		global looper_deleted
		looper_deleted = True
		# give_me_exception() # FIXME: causes program to crash with ugly error message

testLooper = TestLooper()
testLooper.Run()

# Make C++ obtain a reference to testLooper
messenger = BMessenger(None, testLooper)

# Remove Python's reference to testLooper
# One of two things will now happen:
# 1. Python will know C++ has a reference and not delete testLooper yet
#    (correct)
# 2. Python will not realize that C++ still has a reference to testLooper and
#    will free it (incorrect)
del testLooper

# Now tell the looper to quit. In effect, this calls the Quit function
# One of two things will now happen:
# 1. C++ will see that TestLooper exists and that its Quit function overrides
#    BLooper.Quit, and will call TestLooper.Quit instead (correct)
# 2. C++ will see that nothing extends BLooper.Quit (since TestLooper.Quit has
#    been freed) and call BLooper.Quit directly (incorrect)
messenger.SendMessage(B_QUIT_REQUESTED, None)

# Free the messenger. Now we have no references to it either directly (through
# testLooper), or indirectly. This means that as soon as testLooper quits it
# should call its destructor. Otherwise, there is likely a memory leak.
del messenger

# Give the looper a bit time to receive and process the message, quit, and
# clean up
time.sleep(.1)

if looper_quit_called and looper_deleted:
	print("Test passed!")

if not looper_quit_called:
	print("TestLooper.Quit wasn't called. This likely means that TestLooper "
		" was freed too early, which probably means that something either"
		" did not obtain a reference to it when it should have, or else"
		" released it too early.")

if not looper_deleted:
	print("TestLooper.__del__ wasn't called. This likely signifies a memory"
		" leak. Something that obtained a reference to TestLooper likely never"
		" released it.")
