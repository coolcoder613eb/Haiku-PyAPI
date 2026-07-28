from Be import BApplication, BRect, BScrollBar, B_HORIZONTAL


EXPECTED_CALLBACKS = [
    (123.5, 45.25),
]


class CallbackProbe(BScrollBar):
    def __init__(self):
        BScrollBar.__init__(
            self,
            BRect(0.0, 0.0, 100.0, 20.0),
            "frame-resized-probe",
            None,
            0.0,
            100.0,
            B_HORIZONTAL,
        )

        self.calls = []

    def FrameResized(self, new_width, new_height):
        self.calls.append((new_width, new_height))


def main():
    application = BApplication(
        "application/x-vnd.haiku-pyapi-"
        "scrollbar-frame-resized-test"
    )

    scroll_bar = CallbackProbe()

    # Enter the C++ virtual trampoline through the bound
    # base method instead of calling the Python override directly.
    BScrollBar.FrameResized(scroll_bar, 123.5, 45.25)

    if scroll_bar.calls != EXPECTED_CALLBACKS:
        raise SystemExit(
            "FAIL: incorrect BScrollBar FrameResized "
            f"callback arguments: {scroll_bar.calls!r}"
        )

    print("callbacks =", scroll_bar.calls)
    print(
        "BSCROLLBAR FRAMERESIZED CALLBACK "
        "REGRESSION TEST: PASS"
    )

    del scroll_bar
    del application


if __name__ == "__main__":
    main()
