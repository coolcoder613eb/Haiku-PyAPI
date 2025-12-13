BApplication Class Reference
==============================
Base classes
------------

- BLooper
- BHandler

.. currentmodule:: Be


BApplication constructors
--------------------------
.. rubric:: `Constructors`

.. function:: BApplication(signature)

   Create a new application with the given application signature.

:param signature: A MIME type string that must have the supertype "application".
:type signature: str
   
.. function:: BApplication(signature,error)
   
   Create a new application and return an error code if initialization fails.

:param signature: A MIME type string that must have the supertype "application".
:type signature: str
:param error: Pointer to a status_t variable that receives the initialization status.
:type error: int
   
.. function:: BApplication(data)
   
   Reconstruct an application from archived data stored in a BMessage.

:param data: BMessage containing archived application state.
:type data: BMessage

------------------------

BApplication functions
------------------------
.. rubric:: `Functions`

.. autoclass:: BApplication
   :members:
   :undoc-members:
   :show-inheritance: