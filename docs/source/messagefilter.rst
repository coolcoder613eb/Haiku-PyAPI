MessageFilter Module
====================
This module provides bindings for the class ``BMessageFilter``, the ``filter_result`` constants, the ``message_delivery`` constants and the ``message_source`` constants defined in Haiku's Application Kit, specifically from the ``<app/MessageFilter.h>`` header. 

filter_result Codes
-----------------------

.. autoclass:: Be.MessageFilter.filter_result
   :members:
   :undoc-members:

message_delivery Codes
-----------------------

.. autoclass:: Be.MessageFilter.message_delivery
   :members:
   :undoc-members:

message_source Codes
------------------------

.. autoclass:: Be.MessageFilter.message_source
   :members:
   :undoc-members:

MessageFilter  constructors
-------------------------------------
.. rubric:: `Constructors`

.. function:: BMessageFilter(what)

   Creates and returns a new ``BMessageFilter``.

   :param what: A command constant, the ``what`` value of the incoming message must match this value.
   :type what: int

.. function:: BMessageFilter(delivery,source)

   Creates and returns a new ``BMessageFilter``.

   :param delivery: specify how message must arrive.
   :type delivery: message_delivery
   :param source: specify how should be the sender.
   :type source: message_source

.. function:: BMessageFilter(delivery,source,what)

   Creates and returns a new ``BMessageFilter``.

   :param delivery: specify how message must arrive.
   :type delivery: message_delivery
   :param source: specify how should be the sender.
   :type source: message_source
   :param what: A command constant, the ``what`` value of the incoming message must match this value.
   :type what: int


BMessageFilter functions
------------------------
.. rubric:: `Functions`

.. autoclass:: Be.BMessageFilter
   :members:
   :undoc-members:
   :show-inheritance:
