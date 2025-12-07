BMessage Class Reference
========================
.. currentmodule:: Be

.. rubric:: `Constructors`
.. function:: BMessage()

   Create an empty BMessage.

   The message will have no fields and a `what` code equal to zero.
   
.. function:: BMessage(what)
   
   Create a BMessage with a specific `what` code.

:param what: The 'what' command identifier associated with this message.
:type what: int
.. function:: BMessage(altro_messaggio)

   Create a copy of an existing BMessage.

   This performs a deep copy of all fields and metadata.

:param other: The message to copy.
:type other: BMessage

========================

.. autoclass:: BMessage
   :members:
   :undoc-members:
   :show-inheritance: