import gc
import faulthandler

faulthandler.enable()

try:
    import resource
    resource.setrlimit(resource.RLIMIT_CORE, (0, 0))
except Exception:
    pass

from Be import (
    BApplication,
    BSeparatorView,
    BRect,
    BWindow,
    B_HORIZONTAL,
    B_NOT_RESIZABLE,
    window_type,
)


application = BApplication(
    "application/x-vnd.haiku-pyapi-bseparatorview-holder-test"
)

window = BWindow(
    BRect(100.0, 100.0, 360.0, 260.0),
    "BSeparatorView holder test",
    window_type.B_TITLED_WINDOW,
    B_NOT_RESIZABLE,
)

separator = BSeparatorView(B_HORIZONTAL)

window.AddChild(separator, None)
window.Quit()

del separator
gc.collect()

del window
del application
gc.collect()

print("BSEPARATORVIEW HOLDER OWNERSHIP REGRESSION TEST: PASS")
