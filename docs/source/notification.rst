Notification Module
===================
This module provides bindings for the class BNotification and the notification_type constants defined in Haiku's Application Kit, specifically from the ``<app/Notification.h>`` header. 

notification_type Codes
-----------------------------

.. autoclass:: Be.Notification.notification_type
   :members:
   :undoc-members:

Notification  constructors
-------------------------------
.. rubric:: `Constructors`

.. function:: BNotification(type)

   Construct an empty message, with the specified ``type``.
   The type influences the style of the notification view.

   :param type: The type of the notification.
   :type type: notification_type

.. function:: BNotification(archive)

   Construct a notification from an archive.

   :param archive: The ``BMessage`` containing the archived notification.
   :type archive: BMessage


BNotification functions
-------------------------------
.. rubric:: `Functions`

.. autoclass:: Be.BNotification
   :members:
   :undoc-members:
   :show-inheritance:
