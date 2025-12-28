PropertyInfo Module
===================
This module provides bindings for class BPropertyInfo, value_kind constants,  compound_type struct with its field_pair struct, property_info struct and value_info struct defined in Haiku's Application Kit, specifically from the ``<app/PropertyInfo.h>`` header. 

value_kind Codes
-----------------
.. autoclass:: Be.PropertyInfo.value_kind
   :members:
   :undoc-members:

compound_type class
--------------------
.. autoclass:: Be.PropertyInfo.compound_type
   :members:
   :undoc-members:
   :show-inheritance:

compound_type.field_pair class
-------------------------------
.. autoclass:: Be.PropertyInfo.field_pair
   :members:
   :undoc-members:
   :show-inheritance:


property_info class
--------------------
.. autoclass:: Be.PropertyInfo.property_info
   :members:
   :undoc-members:
   :show-inheritance:

value_info class
-----------------
.. autoclass:: Be.PropertyInfo.value_info
   :members:
   :undoc-members:
   :show-inheritance:


PropertyInfo  constructors
---------------------------
.. rubric:: `Constructors`

.. function:: BPropertyInfo(prop,value,freeOnDelete)
   
   Initializes the object with the specified ``propertyInfo`` and ``valueInfo``.
   
   :param prop: The properties array.
   :type prop: property_info
   :param value: The values array.
   :type value: value_info
   :param freeOnDelete: if ``True``, free the memory associated with ``propertyInfo`` and ``valueInfo`` when the object is destroyed.
   :type freeOnDelete: bool


BPropertyInfo functions
--------------------------
.. rubric:: `Functions`

.. autoclass:: Be.BPropertyInfo
   :members:
   :undoc-members:
   :show-inheritance:
