BMessage Class Reference
========================

BMessage definitions and constants
------------------------------------
.. currentmodule:: Be.Message

.. rubric:: `Name lengths`

.. data:: B_FIELD_NAME_LENGTH
   :value: 255

   Maximum length for the field name

.. data:: B_PROPERTY_NAME_LENGTH
   :value:

   Maximum length for the property name

.. rubric:: `Scripting specifiers`

.. data:: B_NO_SPECIFIER
   :value: 0

   Indicates that no specifier is present.

.. data:: B_DIRECT_SPECIFIER
   :value: 1

   The simplest specifier. It targets the object or property directly by name, 
   equivalent to saying "the property itself."

.. data:: B_INDEX_SPECIFIER
   :value: 2

   Targets an item within a collection using a zero-based index.

.. data:: B_REVERSE_INDEX_SPECIFIER
   :value: 3

   Targets an item within a collection using an index starting from the end.

.. data:: B_RANGE_SPECIFIER
   :value: 4

   Targets a range of items within a collection.

.. data:: B_REVERSE_RANGE_SPECIFIER
   :value: 5

   Targets a range of items starting from the end of a collection.

.. data:: B_NAME_SPECIFIER
   :value: 6

   Targets an item within a collection by its specific name string.

.. data:: B_ID_SPECIFIER
   :value: 7

   Targets an item using a unique system-assigned ID.

.. data:: B_SPECIFIERS_END
   :value: 128

   A marker used to define the boundary for user-defined or custom specifier 
   constants. Values above this are reserved for application-specific use.


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
   :type other_message: BMessage

========================

BMessage functions
------------------------
.. rubric:: `Functions`

.. autoclass:: BMessage
   :members:
   :undoc-members:
   :show-inheritance: