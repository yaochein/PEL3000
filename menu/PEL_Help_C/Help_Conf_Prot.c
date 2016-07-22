#include "../INCLUDES.H" 

const BYTE Help_Conf_Prot_T[]="\
<M065>\
<L><C1><F0>Protection Settings
<L><C0><F0>
<L><C0><F0>The Protection settings are used to prevent 
<L><C0><F0>damage to the unit or the DUT by excessive
<L><C0><F0>current, voltage or power.
<L><C0><F0>
<L><C0><F0>An alarm is generated and a message is 
<L><C0><F0>displayed on the screen when a protection 
<L><C0><F0>setting is tripped. When an alarm is activated,
<L><C0><F0>the load is turned off (or limited), and the 
<L><C0><F0>ALARM STATUS pin of the J1 connector on the 
<L><C0><F0>rear panel (pin 16) turns on (open collector 
<L><C0><F0>output by a photocoupler).The protection 
<L><C0><F0>settings can be used regardless of whether 
<L><C0><F0>the remote sense connections are used or not.
<L><C0><F0>
<L><C2><F0>OCP
<L><C0><F0>For OCP, the Electronic Load can be configured 
<L><C0><F0>to either limit the current or turn off the 
<L><C0><F0>load. The OCP levels can be set to 10% higher 
<L><C0><F0>than the rating current.
<L><C0><F0>When OCP Setting is configured to Load Off, a 
<L><C0><F0>message will be displayed on the screen when 
<L><C0><F0>OCP is tripped. The Enter key must be pressed 
<L><C0><F0>to clear the alarm message. 
<L><C0><F0>When configured to LIMIT, OCP will be displayed
<L><C0><F0>on the screen when the OCP is tripped and the
<L><C0><F0>current will be limited to the OCP Level setting.
<L><C0><F0>
<L><C2><F0>OPP
<L><C0><F0>For OPP, the Electronic Load can be configured 
<L><C0><F0>to either limit the power or turn off the load.
<L><C0><F0>The OPP levels can be set to 10% higher than the
<L><C0><F0>rating power.
<L><C0><F0>When OPP Setting is configured to Load Off, a 
<L><C0><F0>message will be displayed on the screen when 
<L><C0><F0>OPP is tripped. The Enter key must be pressed 
<L><C0><F0>to clear the alarm message. 
<L><C0><F0>When configured to LIMIT, OPP will be displayed
<L><C0><F0>on the screen when the OPP is tripped and the
<L><C0><F0>power will be limited to the OPP Level setting.
<L><C0><F0>
<L><C2><F0>UVP
<L><C0><F0>If the UVP is tripped, the LSG series will turn 
<L><C0><F0>off the load. The UVP levels can be set from 
<L><C0><F0>0V to 10% higher than the rating voltage.
<L><C0><F0>The UVP indicator will only appear on the 
<L><C0><F0>screen when the input voltage is below the UVP 
<L><C0><F0>level.
<L><C0><F0>
<L><C2><F0>OVP
<L><C0><F0>If the OVP is tripped, the LSG series will turn 
<L><C0><F0>off the load.
<L><C0><F0>The OVP levels can be set from 0V to 10% higher 
<L><C0><F0>than the rating voltage.
<L><C0><F0>To turn OVP off, set the OVP voltage greater 
<L><C0><F0>than the current rating voltage + 10%.
<L><C0><F0>
<L><C1><F0>Previous Menu:
<L><C0><F0>Press the <C3>F5<C0> softkey, to return to the
<L><C0><F0>previous menu.
<L><C0><F0>
<L><C0><F0>-End-";


const BYTE Help_Conf_Prot[]="\
<M065>\
<L><C1><F0>Protection Settings
<L><C0><F0>
<L><C0><F0>The Protection settings are used to prevent 
<L><C0><F0>damage to the unit or the DUT by excessive
<L><C0><F0>current, voltage or power.
<L><C0><F0>
<L><C0><F0>An alarm is generated and a message is 
<L><C0><F0>displayed on the screen when a protection 
<L><C0><F0>setting is tripped. When an alarm is activated,
<L><C0><F0>the load is turned off (or limited), and the 
<L><C0><F0>ALARM STATUS pin of the J1 connector on the 
<L><C0><F0>rear panel (pin 16) turns on (open collector 
<L><C0><F0>output by a photocoupler).The protection 
<L><C0><F0>settings can be used regardless of whether 
<L><C0><F0>the remote sense connections are used or not.
<L><C0><F0>
<L><C2><F0>OCP
<L><C0><F0>For OCP, the Electronic Load can be configured 
<L><C0><F0>to either limit the current or turn off the 
<L><C0><F0>load. The OCP levels can be set to 10% higher 
<L><C0><F0>than the rating current.
<L><C0><F0>When OCP Setting is configured to Load Off, a 
<L><C0><F0>message will be displayed on the screen when 
<L><C0><F0>OCP is tripped. The Enter key must be pressed 
<L><C0><F0>to clear the alarm message. 
<L><C0><F0>When configured to LIMIT, OCP will be displayed
<L><C0><F0>on the screen when the OCP is tripped and the
<L><C0><F0>current will be limited to the OCP Level setting.
<L><C0><F0>
<L><C2><F0>OPP
<L><C0><F0>For OPP, the Electronic Load can be configured 
<L><C0><F0>to either limit the power or turn off the load.
<L><C0><F0>The OPP levels can be set to 10% higher than the
<L><C0><F0>rating power.
<L><C0><F0>When OPP Setting is configured to Load Off, a 
<L><C0><F0>message will be displayed on the screen when 
<L><C0><F0>OPP is tripped. The Enter key must be pressed 
<L><C0><F0>to clear the alarm message. 
<L><C0><F0>When configured to LIMIT, OPP will be displayed
<L><C0><F0>on the screen when the OPP is tripped and the
<L><C0><F0>power will be limited to the OPP Level setting.
<L><C0><F0>
<L><C2><F0>UVP
<L><C0><F0>If the UVP is tripped, the PEL-3000E will turn 
<L><C0><F0>off the load. The UVP levels can be set from 
<L><C0><F0>0V to 10% higher than the rating voltage.
<L><C0><F0>The UVP indicator will only appear on the 
<L><C0><F0>screen when the input voltage is below the UVP 
<L><C0><F0>level.
<L><C0><F0>
<L><C2><F0>OVP
<L><C0><F0>If the OVP is tripped, the PEL-3000E will turn 
<L><C0><F0>off the load.
<L><C0><F0>The OVP levels can be set from 0V to 10% higher 
<L><C0><F0>than the rating voltage.
<L><C0><F0>To turn OVP off, set the OVP voltage greater 
<L><C0><F0>than the current rating voltage + 10%.
<L><C0><F0>
<L><C1><F0>Previous Menu:
<L><C0><F0>Press the <C3>F5<C0> softkey, to return to the
<L><C0><F0>previous menu.
<L><C0><F0>
<L><C0><F0>-End-";

