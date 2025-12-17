Cursor Module
=============
This module provides bindings for the class BCursor and the cursor ID constants defined in Haiku's Application Kit, specifically from the ``<app/Cursor.h>`` header. 

BCursorID Codes
--------------------

.. autoclass:: Be.Cursor.BCursorID
   :members:
   :undoc-members:

Cursor  constructors
--------------------
.. rubric:: `Constructors`

.. function:: BCursor(cursorData)

   Initializes a new cursor from raw cursor data.

   If the cursorData parameter is not ``None`` then the cursor is initialized with the cursor data.

   :param cursorData: The cursor data.
   :type cursorData: py::buffer (e.g. bytes, bytearray, numpy.ndarray)

.. function:: BCursor(other)

   Initializes a new cursor object from another cursor object.

   :param other: Some other cursor object.
   :type other: BCursor

.. function:: BCursor(id)

   Initializes a new cursor object from a predefined cursor id.

   :param id: An ID from BCursorID enum, see above.
   :type id: int

.. function:: BCursor(data)

   Initializes a new cursor object from a message archive.

   :param data: A message containing the archived data.
   :type data: BMessage

.. function:: BCursor(bitmap,hotspot)

   Initializes a new cursor object from a bitmap object and a point object.

   :param bitmap: The bitmap object to initialize from.
   :type bitmap: BBitmap
   :param data: The cursor hotspot.
   :type data: BPoint


BCursor functions
------------------------
.. rubric:: `Functions`

.. autoclass:: Be.BCursor
   :members:
   :undoc-members:
   :show-inheritance:
