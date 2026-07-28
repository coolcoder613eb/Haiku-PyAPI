import gc

from Be import (
    BApplication,
    BControl,
    BRect,
    BWindow,
    B_NOT_RESIZABLE,
    window_type,
)


application = BApplication(
    "application/x-vnd.haiku-pyapi-bcontrol-holder-test"
)

window = BWindow(
    BRect(100.0, 100.0, 320.0, 220.0),
    "BControl holder test",
    window_type.B_TITLED_WINDOW,
    B_NOT_RESIZABLE,
)

control = BControl(
    BRect(10.0, 10.0, 180.0, 40.0),
    "holder-probe",
    "probe",
    None,
    0,
    0,
)

window.AddChild(control, None)
window.Quit()

del control
gc.collect()

del window
del application
gc.collect()

print("BCONTROL HOLDER OWNERSHIP REGRESSION TEST: PASS")
