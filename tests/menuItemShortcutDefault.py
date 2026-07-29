import gc

from Be import BMenuItem, BMessage


message = BMessage(0x716D6903)

item = BMenuItem(
    "default shortcut",
    message,
)

if item.Label() != "default shortcut":
    raise RuntimeError(
        f"unexpected menu item label: {item.Label()!r}"
    )

del item
del message

gc.collect()

print("BMENUITEM DEFAULT SHORTCUT REGRESSION TEST: PASS")
