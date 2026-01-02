AppDefs Module
==============
This module provides bindings for key constants and system message codes defined in Haiku's Application Kit, specifically from the ``<app/AppDefs.h>`` header. These constants are essential for message passing (BMessage) and basic application behavior in Haiku.

System Message Codes
--------------------

.. autoclass:: Be.AppDefs.system_message_code
   :members:
   :undoc-members:

Command Message Codes
---------------------

.. autoclass:: Be.AppDefs.command_code
   :members:
   :undoc-members:

Cursor Definitions
-------------------

The Haiku-PyAPI module `Be.AppDefs` provides several predefined cursors, both old-style
(byte arrays) and new-style (system constants). These cursors can be used in applications
to set the mouse cursor.

.. currentmodule:: Be.Roster

.. rubric:: `Old-style cursors (arrays of bytes)`

.. data:: B_HAND_CURSOR
   :value: (bytes)

   Hand-shaped cursor. Represented as a byte array containing:
   
      - A 4-byte header
      - Image data
      - Transparency mask

.. data:: B_I_BEAM_CURSOR
   :value: (bytes)

   I-beam cursor (vertical line). Represented as a byte array containing:

      - A 4-byte header
      - Image data
      - Transparency mask

.. rubric:: `New-style cursors (system constants)`

.. data:: B_CURSOR_SYSTEM_DEFAULT
   :value: (BCursor)

   System default cursor. Managed internally by Haiku, does not require a byte array.

.. data:: B_CURSOR_I_BEAM
   :value: (BCursor)

   Standard text I-beam cursor (new-style). Compatible with the Haiku system cursor API.