from Be import BApplication, BView


EXPECTED_CALLBACKS = [
    "DetachedFromWindow",
    "AllDetached",
]


class CallbackProbe(BView):
    def __init__(self):
        BView.__init__(
            self,
            "callback-probe",
            0,
            None,
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
        "application/x-vnd.haiku-pyapi-view-detach-callback-test"
    )
    view = CallbackProbe()

    BView.DetachedFromWindow(view)
    BView.AllDetached(view)

    if view.calls != EXPECTED_CALLBACKS:
        raise SystemExit(
            "FAIL: incorrect detach callback dispatch: "
            f"{view.calls!r}"
        )

    print("callbacks =", view.calls)
    print("VIEW DETACH CALLBACK REGRESSION TEST: PASS")

    # Keep the BApplication alive until the probe has completed.
    del application


if __name__ == "__main__":
    main()
