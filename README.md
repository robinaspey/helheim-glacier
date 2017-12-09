# helheim-glacier
This repository is for code, schematics and artwork for PCB's for the NERC Networks of Sensors in Extreme Environments project 
which monitored spatial extension of Helheim glacier using 2 wireless sensor networks for transmitting high resolution RTK GPS data to
adjacent Linux base-stations on either side of the fjord. The project aimed to monitor flexure of the glacier during the Summer
melt when the ice sheet moved at 10 - 200 cm or so per hour (I forget the actual figure).

The repository is not complete at the time of writing, until I find time to add all of the code.

Contents are as follows:
1.  at Tiny C/C++ code for external watchdog timer for Waspmote. This code runs on a serial interface board which interfaces the binary 220 byte payload from the GPS/GNSS front end to the ATMega on the Waspmote. The data is then transmitted via XBee Pro (Zigbee) radio. Each GNSS/GPS has two waspmotes transmitting so as to avoid co-channel interference.

The Waspmote API from Libelium (v.028) had problems due to memory leaks which periodically caused the ATMega 1280 on the Waspmote to crash
or become unstable. This was due to stack overflow which meant the Waspmote could lock up.

Of the various solutions tested the most reliable one was to poll using the AT tiny uP for a DIO level change which indicated that the 
waspmote was running normally. If this was not seen the AT tiny pulled the reset line on the Waspmote to force a reboot, which also forced 
the XBee pro Zibgee module to rejoin its respective coordinator node on the side of the glacier. 

2.  Waspmote processing (similar to C++/C) code running on ATMega 1280.

3.  Libelium v.28 api, which is C++ libraries for ATmega using 802.15.4 style frames.  This is the stock code which requires slight modification to allow an escaped binary payload to be sent of up to 250 bytes. Details of the modifications also included reducting memory use to cut down on the chances of stack overflow due to code bugs causeing pointers to overrun.

4.  Daughter board PCB and gerber files for Eagler v5.X.

5.  End of readme file
