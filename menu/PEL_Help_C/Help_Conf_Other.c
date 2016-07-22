#include "../INCLUDES.H" 

const BYTE Help_Conf_Other[]="\
<M057>\
<L><C1><F0>Other Configure
<L><C0><F0>
<L><C2><F0>Soft Start
<L><C0><F0>The soft start setting is used to limit the amount 
<L><C0><F0>of input current at start-up or from when the 
<L><C0><F0>Von Voltage threshold is tripped.
<L><C0><F0>
<L><C2><F0>Von Voltage
<L><C0><F0>The Von Voltage is the threshold voltage at 
<L><C0><F0>which the load module will start to sink 
<L><C0><F0>current.
<L><C0><F0>
<L><C2><F0>Von Latch
<L><C0><F0>When Von Latch is set to ON, the load will 
<L><C0><F0>continue to sink current after being 'latched', 
<L><C0><F0>even if the voltage drops below the Von 
<L><C0><F0>Voltage threshold level.
<L><C0><F0>When Von Latch is set to OFF, the load will 
<L><C0><F0>turn off when the voltage drops below the Von 
<L><C0><F0>Voltage threshold level. 
<L><C0><F0>By default Von Latch is set to OFF.
<L><C0><F0>
<L><C2><F0>Von Delay
<L><C0><F0>Von Delay is the amount of time the unit will 
<L><C0><F0>wait before turning the load on after the Von 
<L><C0><F0>Voltage threshold has been latched. This will 
<L><C0><F0>prevent overshoot current from affecting the 
<L><C0><F0>Von Voltage threshold.
<L><C0><F0>
<L><C2><F0>Count Time
<L><C0><F0>When Count Time is set to on, it will count the 
<L><C0><F0>elapsed time from when the load was turned on 
<L><C0><F0>to when it was turned off.  
<L><C0><F0>This function is applicable to manual and 
<L><C0><F0>automatic shutdown (such as from protection 
<L><C0><F0>functions such as UVP etc.)
<L><C0><F0>The elapsed time will be shown in the display 
<L><C0><F0>Measurement area.
<L><C0><F0>
<L><C2><F0>Cut Off Time
<L><C0><F0>The Cut Off Time function will turn the load off 
<L><C0><F0>after a set-amount of time. After the load has 
<L><C0><F0>been turned off, a popup screen will display the 
<L><C0><F0>voltage level when the load was turned off. 
<L><C0><F0>
<L><C1><F0>Previous Menu:
<L><C0><F0>Press the <C3>F5<C0> softkey, to return to the
<L><C0><F0>previous menu.
<L><C0><F0>
<L><C0><F0>-End-";

