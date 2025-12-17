BHandler Class Reference
========================
This class handles messages that are passed on by a BLooper.
The BHandler class implements two important pieces of functionality: 
- the foundations for handling messages 
- keeping track of the current state of thing for sending out notifications.

.. currentmodule:: Be


BHandler constructors
------------------------
.. rubric:: `Constructors`

.. function:: BHandler(name)

   Construct a new handler with a name.

   The newly constructed handler is not associated with a looper until you explicitly request this to happen.

   :param name: name of the handler. Defaults to ``None``
   :type name: str
   
.. function:: BHandler(data)
   
   Construct a handler from an archived message.

   .. note::
      This data has to be created using the BHandler::Archive() method. Note that only the name is stored. The filters, the associated looper and the observers are not stored, and should be manually added when you are using this object.

   :param data: The message containing the archived data.
   :type data: BMessage

========================

BHandler functions
------------------------
.. rubric:: `Functions`

.. autoclass:: BHandler
   :members:
   :undoc-members:
   :show-inheritance: