BInvoker Class Reference
========================
BInvoker is a convenience class that bundles up everything you 
need to create a handy message-sending package.

The BInvoker contains:
- a BMessage
- a BMessenger (that identifies a target handler)
- an optional BHandler that handles replies. (be_app by default)

.. currentmodule:: Be


BInvoker constructors
------------------------
.. rubric:: `Constructors`

.. function:: BInvoker()

   Initializes a BInvoker without a message or target.

.. function:: BInvoker(message,handler,looper)
   
   Initializes the BInvoker with message and sets the target to 
   either a local handler or as the preferred handler of a local 
   looper where the message is sent when ``Invoke()`` is called.

   .. note::
      It is not necessary to specify both the handler and the 
      looper, the unused parameter should be passed in as ``None``.
   
   :param message: The message to send.
   :type message: BMessage
   :param handler: The local handler to receive the message, or ``None``.
   :type handler: BHandler
   :param looper: The local looper to receive the message, or ``None``, defaults to ``None``.
   :type looper: BLooper

.. function:: BInvoker(message,target)

   Initializes the BInvoker with message and sets the target 
   messenger where the message is sent when ``Invoke()`` is called.
   A BMessenger can target either local or remote objects.

   :param message: The message to send.
   :type message: BMessage
   :param target: The messenger where the message is sent when ``Invoke()`` is called.
   :type target: BMessenger

========================

BInvoker functions
------------------------
.. rubric:: `Functions`

.. autoclass:: BInvoker
   :members:
   :undoc-members:
   :show-inheritance: