Roster Module
=============
This module provides bindings for the class ``BRoster``, the struct ``app_info`` and the ``watching_request_flags`` constants defined in Haiku's Application Kit, specifically from the ``<app/Roster.h>`` header. 

watching_request_flags Codes
----------------------------

.. autoclass:: Be.Roster.watching_request_flags
   :members:
   :undoc-members:

Notification message "what" constants
-------------------------------------

.. currentmodule:: Be.Roster

.. data:: B_SOME_APP_LAUNCHED
   :value: 'BRAS'

   Sent whan an application has been launched in the system. 
   The notifying message will contain the ``team_id`` and the app's ``signature``.

.. data:: B_SOME_APP_QUIT
   :value: 'BRAQ'

   Sent when an application terminates its execution.

.. data:: B_SOME_APP_ACTIVATED
   :value: 'BRAW'

   Sent when an application activates (becomes the front app).

app_info constructors
----------------------
.. rubric:: `Constructors`

.. function:: app_info()

   Initialize an empty ``app_info`` object.

app_info functions
------------------------
.. rubric:: `Functions`

.. autoclass:: Be.Roster.app_info
   :members:
   :undoc-members:
   :show-inheritance:


BRoster  constructors
----------------------
.. rubric:: `Constructors`

.. function:: BRoster()

   Sets up the object's connection to the roster service.

   When an application constructs its ``BApplication`` object, the system 
   constructs a ``BRoster`` object and assigns it to the ``be_roster`` global 
   variable. A ``BRoster`` is therefore readily available from the time 
   the application is initialized until the time it quits; you don't have 
   to construct one. The constructor is public only to give programs that 
   don't have BApplication objects access to the roster.

BRoster functions
------------------------
.. rubric:: `Functions`

.. autoclass:: Be.BRoster
   :members:
   :undoc-members:
   :show-inheritance:
