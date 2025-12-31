BHandler Class Reference
========================
This class handles messages that are passed on by a BLooper.
The BHandler class implements two important pieces of functionality: 
- the foundations for handling messages 
- keeping track of the current state of thing for sending out notifications.


BHandler definitions and constants
-----------------------------------
.. currentmodule:: Be.Handler

.. data:: B_OBSERVE_WHAT_CHANGE
   :value: "be:observe_change_what"

   Message field key used to identify the specific 'what' code of a change 
   notification.

.. data:: B_OBSERVE_ORIGINAL_WHAT
   :value: "be:observe_orig_what"

   Message field key used to store the original 'what' code of an event.

.. data:: B_OBSERVER_OBSERVE_ALL
   :value: 0xffffffff

   A special bitmask used with :meth:`StartWatching`. Passing this constant 
   indicates that the observer wants to receive notifications for every 
   possible event, effectively disabling filtering for that subscription.

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

   .. warning::
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
   
