Key Module
==============
This module provides bindings for BKey and BPasswordKey classes, as well as BKeyPurpose and BKeyType enums, which are defined in Haiku's Application Kit, specifically from the ``<app/Key.h>`` header.

Haiku R1 introduces the first version of a system-wide key store service, allows you as developer to outsource some of the credential and certificate management, as well as providing an infrastructure that enables sharing these artifacts between applications.

The implementation is based around the following concepts:

- The **keystore** is the centralized repository for your keys. It is managed by the **keystore_server** and it contains one or more **keyrings**.
- A **keyring** is a collection of keys. There is always a **master keyring**, which cannot be removed. Access is organized around keyrings. From a user's perspective, when an application wants to access keys in a keyring, the user will have to grant permission to that application to access the keyring. A keyring is identified by a name, which needs to be unique on the user's system.
- A keyring contains **keys**. These are the smallest unit in the system. A key can be anything that you want to safeguard in the keystore. Keys are identified by the combination of an identifier and a secondary identifier. These should be unique within a keyring.
- The final piece is the concept of **permissions**. In the current implementation, an application needs to ask permission to access a keyring. The keystore_server will validate the permissions, and if necessary prompt the user to grant one-time or a permant access. If the user only allows it once, access is granted until the application terminates.

The current implementation of this API should be considered **low-security**. The most important thing to know is that there is **no encryption** applied when storing the keys and keyrings to the drive.
The current locking mechanism is unsafe too.  Please read Haiku's documentation.

BKeyPurpose Codes
--------------------

.. autoclass:: Be.Key.BKeyPurpose
   :members:
   :undoc-members:

BKeyType Codes
---------------------

.. autoclass:: Be.Key.BKeyType
   :members:
   :undoc-members:

BKey Class Reference
--------------------------
.. currentmodule:: Be

.. rubric:: `Constructors:`

.. function:: BKey()

   Constructor for an empty password key.
   
   An empty key has no data associated with it, other than that it has a generic purpose and a password key type.

.. function:: BKey(purpose, identifier, secondaryIdentifier,data)

   Constructor for a generic key with the provided data.

   :param purpose: The purpose of this key
   :type purpose: BKeyPurpose (int)
   :param identifier: A unique identifier for this key
   :type identifier: str
   :param secondaryIdentifier: An (optional) secondary identifier for this key, default is ``None``
   :type secondaryIdentifier: str or ``None``, optional
   :param data: An optional Buffer that contains the value of the key, such as the password or the certificate data, default is ``None``
   :type data: py::buffer (e.g. bytes, bytearray etc.) or ``None``, optional

.. function:: BKey(other)

   Copy constructor that makes a copy of an other BKey.

   :param other: the BKey to copy into this one.
   :type other: BKey

-------------------------

.. rubric:: `Functions:`

.. autoclass:: BKey
   :members:
   :undoc-members:
   :show-inheritance:


BPasswordKey Class Reference
--------------------------
.. currentmodule:: Be

.. rubric:: `Constructors:`

.. function:: BPasswordKey()

   Constructor for an empty password key.
   
   An empty key has no data associated with it, other than that it 
   has a generic purpose and a password key type.

.. function:: BPasswordKey(password,purpose,identifier,secondaryIdentifier)

   Constructor for a password key with the provided data.

   :param password: A null-terminated string that contains the password.
   :type password: str
   :param purpose: The purpose of this key.
   :type purpose: BKeyPurpose (int)
   :param identifier: A unique identifier for this key.
   :type identifier: str
   :param secondaryIdentifier: An (optional) secondary identifier for this key.
   :type secondaryIdentifier: str, optional

.. function:: BPasswordKey(other)

   Copy constructor that makes a copy of an other BPasswordKey.

   :param other: the BPasswordKey to copy into this one.
   :type other: BPasswordKey

------------------------

.. rubric:: `Functions:`

.. autoclass:: BPasswordKey
   :members:
   :undoc-members:
   :show-inheritance:
