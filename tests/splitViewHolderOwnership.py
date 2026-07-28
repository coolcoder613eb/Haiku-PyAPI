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
    BRect,
    BSplitView,
    BWindow,
    B_HORIZONTAL,
    B_NOT_RESIZABLE,
    window_type,
)


application = BApplication(
    "application/x-vnd.haiku-pyapi-bsplitview-holder-test"
)

window = BWindow(
    BRect(100.0, 100.0, 360.0, 260.0),
    "BSplitView holder test",
    window_type.B_TITLED_WINDOW,
    B_NOT_RESIZABLE,
)

split = BSplitView(B_HORIZONTAL)

window.AddChild(split, None)
window.Quit()

del split
gc.collect()

del window
del application
gc.collect()

print("BSPLITVIEW HOLDER OWNERSHIP REGRESSION TEST: PASS")
