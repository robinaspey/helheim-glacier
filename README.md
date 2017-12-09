# helheim-glacier
This repository is for code, schematics and artwork for PCB's for the Networks of Sensors in Extreme Environments project which monitored 
monitored the spatial extension of Helheim glacier using 2 wireless sensor networks for transmitting high resolution RTK GPS data to
adjacent Linux base-stations on either side of the fjord.

The repositor is not complete at the time of writing, until I find time to add all of the code.

Contents are as follows:
1.  at Tiny code for external watchdog timer for Waspmote. This code runs on a serial interface board which interfaces the binary 220 byte 
payload from the GPS/GNSS front end to the ATMega on the Waspmote. The data is then transmitted via XBee Pro (Zigbee) radio. Each GNSS/GPS
has two waspmotes transmitting so as to avoid co-channel interference.

The Waspmote API from Libelium (v.028) had problems due to memory leaks which periodically caused the ATMega 1280 on the Waspmote to crash
or become unstable. This was due to stack overflow which meant the Waspmote could lock up.

Of the various solutions tested the most reliable one was to poll using the AT tiny uP for a DIO level change which indicated that the 
waspmote was running normally. If this was not seen the AT tiny pulled the reset line on the Waspmote to force a reboot, which also forced 
the XBee pro Zibgee module to rejoin its respective coordinator node on the side of the glacier. 
