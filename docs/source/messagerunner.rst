BMessageRunner Class Reference
==================================

.. currentmodule:: Be


BMessageRunner constructors
--------------------------------------------
.. rubric:: `Constructors`

.. function:: BMessageQueue(target,message,interval,count)

   Creates a new ``BMessageRunner``.

:param target: The message recipient.
:type target: BMessenger
:param message: The message to be sent.
:type message: BMessage
:param interval: Time interval between messages (in microseconds).
:type interval: int
:param count: Number of times the message is sent (-1 for infinite).
:type count: int


.. function:: BMessageQueue(target,message,interval,count,replyTo)

   Creates a new BMessageRunner with a reply target.

:param target: The message recipient.
:type target: BMessenger
:param message: The message to be sent.
:type message: BMessage
:param interval: Time interval between messages (in microseconds).
:type interval: int
:param count: Number of times the message is sent (-1 for infinite).
:type count: int
:param replyTo: Messenger to receive replies.
:type replyTo: BMessenger


========================

BMessageRunner functions
-----------------------------------------
.. rubric:: `Functions`

.. autoclass:: BMessageRunner
   :members:
   :undoc-members:
   :show-inheritance:
