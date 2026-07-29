import faulthandler
import gc

faulthandler.enable()

try:
    import resource
    resource.setrlimit(resource.RLIMIT_CORE, (0, 0))
except Exception:
    pass

from Be import (
    BApplication,
    BButton,
    BInvoker,
    BMessage,
)


SENTINEL = 23117


class SafeButton(BButton):
    def __init__(self):
        super().__init__(
            "safe default-argument button",
            BMessage(0x71646274),
        )
        self.received = "not-called"

    def Invoke(self, message=None):
        self.received = message
        return SENTINEL


class SafeInvoker(BInvoker):
    def __init__(self):
        super().__init__()
        self.received = "not-called"

    def Invoke(self, message=None):
        self.received = message
        return SENTINEL


application = BApplication(
    "application/x-vnd.haiku-pyapi-invoke-default-test"
)

button = SafeButton()

button_result = BButton.Invoke(button)

if button_result != SENTINEL:
    raise RuntimeError(
        f"BButton trampoline returned {button_result!r}"
    )

if button.received is not None:
    raise RuntimeError(
        f"BButton received {button.received!r}"
    )

print("BBUTTON INVOKE DEFAULT REGRESSION: PASS")


invoker = SafeInvoker()

invoker_result = BInvoker.Invoke(invoker)

if invoker_result != SENTINEL:
    raise RuntimeError(
        f"BInvoker trampoline returned {invoker_result!r}"
    )

if invoker.received is not None:
    raise RuntimeError(
        f"BInvoker received {invoker.received!r}"
    )

print("BINVOKER INVOKE DEFAULT REGRESSION: PASS")


del invoker
del button
del application

gc.collect()

print("INVOKE MESSAGE DEFAULT REGRESSION TEST: PASS")
