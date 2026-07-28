from Be import BApplication, BMenu, BMenuField


EXPECTED_CALLBACKS = [
    "DetachedFromWindow",
    "AllDetached",
]


class CallbackProbe(BMenuField):
    def __init__(self):
        self.menu = BMenu("callback-probe-menu")

        BMenuField.__init__(
            self,
            "callback-probe",
            "Callback probe",
            self.menu,
        )

        self.calls = []

    def AllAttached(self):
        self.calls.append("AllAttached")

    def DetachedFromWindow(self):
        self.calls.append("DetachedFromWindow")

    def AllDetached(self):
        self.calls.append("AllDetached")


def main():
    application = BApplication(
        "application/x-vnd.haiku-pyapi-"
        "menufield-detach-callback-test"
    )

    field = CallbackProbe()

    # Enter the C++ virtual trampolines through the bound
    # base methods instead of calling Python overrides directly.
    BMenuField.DetachedFromWindow(field)
    BMenuField.AllDetached(field)

    if field.calls != EXPECTED_CALLBACKS:
        raise SystemExit(
            "FAIL: incorrect BMenuField detach callback "
            f"dispatch: {field.calls!r}"
        )

    print("callbacks =", field.calls)
    print(
        "BMENUFIELD DETACH CALLBACK "
        "REGRESSION TEST: PASS"
    )

    del field
    del application


if __name__ == "__main__":
    main()
