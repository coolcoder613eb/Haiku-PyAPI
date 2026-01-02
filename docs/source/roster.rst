Roster Module
=============
This module provides bindings for the class ``BRoster``, the struct ``app_info`` and the ``watching_request_flags`` constants defined in Haiku's Application Kit, specifically from the ``<app/Roster.h>`` header. 

BRoster definitions and constants
----------------------------------
.. currentmodule:: Be.Roster

.. rubric:: `Application launch flags`

.. data:: B_SINGLE_LAUNCH
   :value: 0x0

   Similar to :meth:`B_EXCLUSIVE_LAUNCH`, with the exception that it is per file location, copying the file to a second location therefore allows the application to be started a second time.

   Attempts to launch the same application from the same path again will result in a ``B_ARGV_RECEIVED`` or ``B_REFS_RECEIVED`` message delivered to the existing instance. The application should take care of handling these messages correctly. Applications which can't or don't want to handle this should use :meth:`B_MULTIPLE_LAUNCH` instead.

   .. note::

      This flag only ensures exclusive launches when started via ``BRoster``, launching an application in another way, for example with fork+exec will allow the application to run a second time. This should not be relied on for applications that need to run exclusively in all cases. 

.. data:: B_MULTIPLE_LAUNCH
   :value: 0x1

   The application can have multiple instances running simultaneously.

.. data:: B_EXCLUSIVE_LAUNCH
   :value: 0x2

   This will make the registrar ensure only one application with this application signature is running at any given time.

   Attempts to launch the same application again will result in a ``B_ARGV_RECEIVED`` or ``B_REFS_RECEIVED`` message delivered to the existing instance. The application should take care of handling these messages correctly. Applications which can't or don't want to handle this should use :meth:`B_MULTIPLE_LAUNCH` instead.

   .. note::
      
      This flag only ensures exclusive launches when started via BRoster, launching an application in another way, for example with fork+exec will allow the application to run a second time. This should not be relied on for applications that need to run exclusively in all cases. 

.. rubric:: `Application launch mask`

.. data:: B_LAUNCH_MASK
   :value: 0x3

   Bitwise and this with ``app_info.flags`` to get at the flags above. 
   
.. rubric:: `Application type flags`

.. data:: B_BACKGROUND_APP
   :value: 0x4

   The application is a daemon or service (no user interfae). It won't appear in the Deskbar's running applications list.

.. data:: B_ARGV_ONLY
   :value: 0x8

    The application does not use the standard BApplication message loop for arguments. It expects to receive command-line arguments.

.. rubric:: `Reserved fields`

.. data:: _B_APP_INFO_RESERVED1_
   :value: 0x10000000

   Internal reserved slot for future expansion. This should not be used.


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
