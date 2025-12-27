BMessenger Class Reference
==================================

.. currentmodule:: Be


BMessenger constructors
--------------------------------------------
.. rubric:: `Constructors`

.. function:: BMessenger()

   Create an uninitialized ``BMessenger``.

.. function:: BMessenger(signature,team)

   Creates a ``BMessenger`` and initializes it to target the already running 
   application identified by its signature and/or team ID.

   When only a signature is given, and multiple instances of the application 
   are running it is indeterminate which one is chosen as the target. In case 
   only a team ID is passed, the target application is identified uniquely. 
   If both are supplied, the application identified by the team ID must have 
   a matching signature, otherwise the initialization fails.

   :param signature: The target application's signature. May be ``None``.
   :type signature: str
   :param team: The target application's team ID. May be < ``0``.
   :type team: team_id

.. function:: BMessenger(handler,looper)

   Creates a ``BMessenger`` and initializes it to target the local ``BHandler`` 
   and/or ``BLooper``.

   When a ``None`` handler is supplied, the preferred handler in the looper 
   is targeted. If no looper is supplied the looper that handler belongs to 
   is used instead  that means in particular, that the handler must already 
   belong to a looper. If both are supplied the handler must belong to the looper.

   :param handler: The target handler. May be ``None``.
   :type handler: BHandler
   :param looper: The target looper. May be ``None``.
   :type looper: BLooper

.. function:: BMessenger(other)

   Creates a ``BMessenger`` and initializes it to have the same target as 
   the supplied messenger.

   :param other: 
   :type other: BMessenger


========================

BMessenger functions
-----------------------------------------
.. rubric:: `Functions`

.. autoclass:: BMessenger
   :members:
   :undoc-members:
   :show-inheritance:
