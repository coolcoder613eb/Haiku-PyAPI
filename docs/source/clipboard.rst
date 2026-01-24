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

.. function:: get_be_clipboard()

   This convenient method returns the global variable ``be_clipboard`` which holds 
   the ``BClipboard`` created for you by your ``BApplication`` object.

   .. warning::
      Remember that you need a ``BApplication`` to obtain a valid ``be_clipboard``
      otherwise it will return a ``None``.
   
   .. note::
      This is an example how to use this function:
   
      .. code-block:: python
         
         from Be import BApplication, get_be_clipboard
         # script stuff
      
         # BApplication creation
      
         global be_clipboard
         be_clipboard=get_be_clipboard()
      
         # your example code ...
         if be_clipboard.Lock():
            clip = be_clipboard.Data()
            b = bytes("test", 'utf-8')
            clip.AddData("text/plain",B_MIME_TYPE,b,len(b))
            be_clipboard.Commit()
            be_clipboard.Unlock()
   
      As you can see, you don't even need to import ``BClipboard`` module to get and 
      use ``be_clipboard`` clipboard. 
   
   :return: The global variable ``be_clipboard`` of the ``BApplication``.
   :rtype: BClipboard("system")
