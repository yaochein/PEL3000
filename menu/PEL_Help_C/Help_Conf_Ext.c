#include "../INCLUDES.H" 

const BYTE Help_Conf_Ext[]="\
<M051>\
<L><C2><F0>External Voltage Control
<L><C0><F0>External voltage control of the CC, CR, CV 
<L><C0><F0>and CP mode is accomplished using the J1 
<L><C0><F0>of connector on the rear panel. An input 
<L><C0><F0>voltage 0~10V corresponds to 0% ~ 100% of 
<L><C0><F0>the rated current (CC mode), rated voltage 
<L><C0><F0>(CV mode), or rated power (CP mode). For CR 
<L><C0><F0>mode, 0V ~ 10V corresponds to the maximum 
<L><C0><F0>resistance ~ minimum resistance.
<L><C0><F0>
<L><C0><F0>External voltage control can be used to control 
<L><C0><F0>the current, voltage, resistance and power for 
<L><C0><F0>CC, CR, CV and CP modes. Configuration for 
<L><C0><F0>each operating mode is the same. 
<L><C0><F0>
<L><C2><F0>External Resistance Control
<L><C0><F0>External resistance control of the CC, CR, CV 
<L><C0><F0>and CP modes is accomplished using the J1 
<L><C0><F0>connector on the rear panel. 
<L><C0><F0>A resistance of 0k ~ 10k  is used to control the 
<L><C0><F0>input current, voltage, resistance or power on
<L><C0><F0>the DC Electronic Load.
<L><C0><F0>
<L><C0><F0>External resistance control can be used to 
<L><C0><F0>control the current, voltage, resistance and 
<L><C0><F0>power for CC, CR, CV and CP modes. 
<L><C0><F0>Configuration for each operating mode is the 
<L><C0><F0>same. 
<L><C0><F0>
<L><C2><F0>External Inverse Resistance Control
<L><C0><F0>The inverse configuration is recommended for 
<L><C0><F0>safety reasons. In the event that any of the cables 
<L><C0><F0>become accidentaly disconnected, the 
<L><C0><F0>current/voltage/power input will drop to the 
<L><C0><F0>minimum. Under similar circumstances using 
<L><C0><F0>proportional control, an unexpectedly high input 
<L><C0><F0>would result.
<L><C0><F0>
<L><C2><F0>Turning the Load On
<L><C0><F0>The load can be turned on and off with an 
<L><C0><F0>external switch connected to pins 7 and 12 of 
<L><C0><F0>the J1 connector.
<L><C0><F0>
<L><C0><F0>When external control is used to turn the load off, 
<L><C0><F0>the load key cannot be used to turn the load on. 
<L><C0><F0>However the reverse is not true. If the load has 
<L><C0><F0>been turned on by external control, the load key 
<L><C0><F0>can be used to turn the load off. 
<L><C0><F0>
<L><C0><F0>-End-";
