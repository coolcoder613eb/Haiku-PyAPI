BLooper Class Reference
========================

.. currentmodule:: Be


BLooper constructors
------------------------
.. rubric:: `Constructors`

.. function:: BLooper(name,priority,portCapacity)

   Construct a new BLooper with a priority and an capacity.

   The default priority should be good enough for most tasks. Also, some derived versions 
   of ``BLooper`` will use a specialized priority. So it is advised to leave this setting at 
   the default, unless you know why you would like another setting.
   The constants for priority are located in the OS module
   
   .. code-block:: python
   
      from Be.OS import B_NORMAL_PRIORITY
   
   Loopers use ports to send and receive messages (see the kernel kit). Ports have a maximum 
   capacity; if there are so many messages queued that the port is full, all other incoming 
   messages are dropped. There are situations where the size of the port should be different 
   from the default. This might be when your looper receives a lot of messages, or if the 
   message handling thread runs at a lower priority than normal, which would decrease the 
   processing speed. Finding a suitable value for these custom scenarios would be done by 
   testing.
   
   The new looper is, by default, not running yet. If you have set up everything properly, 
   you may call ``Run()``.
   
   :param name: The name of the looper.
   :type name: str
   :param priority: The priority of the message thread of this looper. The default is ``B_NORMAL_PRIORITY``
   :type priority: int
   :param portCapacity: The maximum port capacity, the default is ``B_LOOPER_PORT_DEFAULT_CAPACITY`` (200)
   :type portCapacity: int
   
.. function:: BLooper(data)

   Construct a looper from an archived message.

   The data message has to be constructed by a BLooper::Archive() call. Note that the 
   data that is restored, is merely the port capacity and the name of the looper/handler. 
   Other data, such as filters, is not archived by the default archiver.
   
   .. note::
      This constructor does no type check whatsoever. Since you can pass any BMessage, 
      you should - if you are not sure about the exact type - use the Instantiate() method, 
      which does check the type.
      
   :param data: The archived message containing the looper.
   :type data: BMessage

========================

BLooper functions
------------------------
.. rubric:: `Functions`

.. autoclass:: BLooper
   :members:
   :undoc-members:
   :show-inheritance:
