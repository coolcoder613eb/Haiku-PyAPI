BMessage Class Reference
========================
.. currentmodule:: Be


BMessage constructors
------------------------
.. rubric:: `Constructors`

.. function:: BMessage()

   Create an empty BMessage.

   The message will have no fields and a `what` code equal to zero.
   
.. function:: BMessage(what)
   
   Create a BMessage with a specific `what` code.

:param what: The 'what' command identifier associated with this message.
:type what: int
.. function:: BMessage(other_message)

Create a copy of an existing BMessage.

This performs a deep copy of all fields and metadata.

:param other_message: The message to copy.
:type other: BMessage

========================

BMessage functions
------------------------
.. rubric:: `Functions`

.. autoclass:: BMessage
   :members:
   :undoc-members:
   :show-inheritance: