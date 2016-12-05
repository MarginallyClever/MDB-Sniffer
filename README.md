MDB Parser
==========

What 
----

Modern vending machines voluntarily adhere to the NAMA standard for Multidrop Bus (MDB).  If these steps are correctly duplicated then this will output to  the Arduino serial window a human-readable interpretation of the conversation taking place inside the vending machine between the various peripherals and the VMC.

Why
---

Many people want to create devices that "speak" MDB and can interact with a vending machine.  Some examples include adding an RFID reader, Accepting payment with BitCoin, touch screens, and discount for secret knock.

How
---

This code is meant to be Arduino firmware.  It assumes that the vending machine components adhere to the [MDB 4.2 standard](http://www.coin-acceptor.com.cn/Upload/EditorFiles/technicalfile/Mdb_version_4-2.pdf).  There are three required components:

* A physical circuit you will have to build/source.  Section 4.4 of the standard describe the circuit.  [An example schematic from the Nottingham Hackspace Wiki](http://wiki.nottinghack.org.uk/images/a/a2/VMC-Nanode_Schematic.png) has been included in this distro.
* Arduino #1 runs "near_MDB" firmware.  A1 connects to the physical circuit through the hardware serial.  This means the hardware serial is not avilable to output data to a PC.
* Arduino #2 runs "near_PC" firmware.  A2 connects to your PC through a USB cable.  A2 pin 10 connects to A1 pin 11.  A2 pin 11 connects to A1 pin 10.

Don't forget the common ground between A1 and A2.

Who Where When
--------------

Created by Dan Royer (dan@marginallyclever.com) for the vending machine at the [Vancouver Hackspace](http://vanhack.ca) April 16, 2014.

"If I have seen further it is by standing on the shoulders of giants."  -- Isaac Newton

Based on [previous work](https://github.com/NottingHack/Vend) from [Nottingham Hackspace](http://nottinghack.org.uk/) members [James Hayward](jhayward1980@gmail.com) and [Matt Lloyd](dps.lwk@gmail.com).

More
----
* [Nottingham Hackspace Wiki page on their vending machine](http://wiki.nottinghack.org.uk/wiki/Vending_Machine)
* [Vancouver Hackspace Wiki page on their vending machine](https://vanhack.ca/doku.php?id=tool:vending_machine)
