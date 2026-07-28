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
    BGridView,
    BRect,
    BWindow,
    B_NOT_RESIZABLE,
    window_type,
)


application = BApplication(
    "application/x-vnd.haiku-pyapi-bgridview-holder-test"
)

window = BWindow(
    BRect(100.0, 100.0, 360.0, 260.0),
    "BGridView holder test",
    window_type.B_TITLED_WINDOW,
    B_NOT_RESIZABLE,
)

grid = BGridView()

window.AddChild(grid, None)
window.Quit()

del grid
gc.collect()

del window
del application
gc.collect()

print("BGRIDVIEW HOLDER OWNERSHIP REGRESSION TEST: PASS")
