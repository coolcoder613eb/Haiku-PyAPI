BClipboard Class Reference
==========================
.. currentmodule:: Be

BClipboard constructor
------------------------
.. rubric:: `Constructor`

.. function:: BClipboard(name,transient)

   Create a BClipboard object with the given name.
   
   If the name parameter is None then the "system" BClipboard object 
   is constructed instead.

:param name: The name of the clipboard.
:type name: str
:param transient: If True, lose data after a reboot (currently unused). Defaults to False
:type transient: bool

========================

BClipboard functions
------------------------
.. rubric:: `Functions`

.. autoclass:: BClipboard
   :members:
   :undoc-members:
   :show-inheritance: