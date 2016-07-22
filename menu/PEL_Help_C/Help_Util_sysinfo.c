#include "../INCLUDES.H" 

const BYTE Help_Util_sysinfo_T[]="\
<M100>\
<L><C1><F0>Utility
<L><C0><F0>The 1st page of Utility menu will always
<L><C0><F0>show up the system information (<C3>System
<L><C0><F0><C3>Info(F1)<C0>) sub-menu.
<L><C0><F0>
<L><C1><F0>System Info
<L><C0><F0>The System information is listed on the display.
<L><C0><F0>MainFrame Ver: Mainframe firmware version.
<L><C0><F0>LSG series SN: Serial number of the unit.
<L><C0><F0>SCPI Ver: SCPI-compatible version
<L><C0><F0>
<L><C1><F0>Load
<L><C0><F0>This system is able to automatically start
<L><C0><F0>loading from the last program or load
<L><C0><F0>setting. If <C2>Auto Load On<C0> is set to <C2>Load<C0>,
<L><C0><F0>the last load setup used before the machine
<L><C0><F0>was reset will automatically start to load
<L><C0><F0>upon startup. If <C2>Prog<C0> is set as the Auto
<L><C0><F0>Load On configuration, the last program
<L><C0><F0>executed will start upon the next start up.
<L><C0><F0>
<L><C1><F0>Interface
<L><C0><F0><C2>Interface<C0> indicated which interface of rear
<L><C0><F0>panel is actived. And there have a list of
<L><C0><F0>the detail settings for the corresponding
<L><C0><F0>interface.
<L><C0><F0>
<L><C1><F0>Time Set
<L><C0><F0>This system is able to display the time and
<L><C0><F0>date on the top status panel, it is also
<L><C0><F0>used to tag files that are saved. Time
<L><C0><F0>information is displayed on the top-left
<L><C0><F0>hand side.
<L><C0><F0>
<L><C1><F0>Other
<L><C2><F0>Knob Type
<L><C0><F0>Update dependent operation is activated.
<L><C0><F0>Both the local (load module) selector knob
<L><C0><F0>and main frame selector knob can change
<L><C0><F0>the resistance (CR mode), current(CC
<L><C0><F0>mode) and voltage (CV mode). Changes from
<L><C0><F0>local mode are updated on the mainframe
<L><C0><F0>and vice versa. <C2>Old<C0> independent operation
<L><C0><F0>is activated. Local operation changes do
<L><C0><F0>not change the setting/values on the
<L><C0><F0>mainframe.
<L><C0><F0>
<L><C2><F0>Speaker
<L><C0><F0>The speaker function turns On/Off the
<L><C0><F0>sound for the UI (key presses and scrolling).
<L><C0><F0>The speaker setting will not alter the sound
<L><C0><F0>for protection alarms or Go/NoGo alarms.
<L><C0><F0>
<L><C2><F0>Alarm Tone / UnReg Tone / Go_NoGo Tone
<L><C0><F0>The alarm tone for the unit during normal 
<L><C0><F0>operation and for Go-NoGo testing can be 
<L><C0><F0>turned on or off in the utility menu. 
<L><C2><F0>Contrast
<L><C0><F0>Control the contrast of the mainframe
<L><C0><F0>display.
<L><C0><F0>
<L><C2><F0>Brightness
<L><C0><F0>Control the brightness of the mainframe
<L><C0><F0>display.
<L><C0><F0>
<L><C2><F0>Language
<L><C0><F0>The DC Electronic Load supports only English.
<L><C0><F0>
<L><C0><F0>-End-";


const BYTE Help_Util_sysinfo[]="\
<M100>\
<L><C1><F0>Utility
<L><C0><F0>The 1st page of Utility menu will always
<L><C0><F0>show up the system information (<C3>System
<L><C0><F0><C3>Info(F1)<C0>) sub-menu.
<L><C0><F0>
<L><C1><F0>System Info
<L><C0><F0>The System information is listed on the display.
<L><C0><F0>MainFrame Ver: Mainframe firmware version.
<L><C0><F0>PEL-3XXX SN: Serial number of the unit.
<L><C0><F0>SCPI Ver: SCPI-compatible version
<L><C0><F0>
<L><C1><F0>Load
<L><C0><F0>This system is able to automatically start
<L><C0><F0>loading from the last program or load
<L><C0><F0>setting. If <C2>Auto Load On<C0> is set to <C2>Load<C0>,
<L><C0><F0>the last load setup used before the machine
<L><C0><F0>was reset will automatically start to load
<L><C0><F0>upon startup. If <C2>Prog<C0> is set as the Auto
<L><C0><F0>Load On configuration, the last program
<L><C0><F0>executed will start upon the next start up.
<L><C0><F0>
<L><C1><F0>Interface
<L><C0><F0><C2>Interface<C0> indicated which interface of rear
<L><C0><F0>panel is actived. And there have a list of
<L><C0><F0>the detail settings for the corresponding
<L><C0><F0>interface.
<L><C0><F0>
<L><C1><F0>Time Set
<L><C0><F0>This system is able to display the time and
<L><C0><F0>date on the top status panel, it is also
<L><C0><F0>used to tag files that are saved. Time
<L><C0><F0>information is displayed on the top-left
<L><C0><F0>hand side.
<L><C0><F0>
<L><C1><F0>Other
<L><C2><F0>Knob Type
<L><C0><F0>Update dependent operation is activated.
<L><C0><F0>Both the local (load module) selector knob
<L><C0><F0>and main frame selector knob can change
<L><C0><F0>the resistance (CR mode), current(CC
<L><C0><F0>mode) and voltage (CV mode). Changes from
<L><C0><F0>local mode are updated on the mainframe
<L><C0><F0>and vice versa. <C2>Old<C0> independent operation
<L><C0><F0>is activated. Local operation changes do
<L><C0><F0>not change the setting/values on the
<L><C0><F0>mainframe.
<L><C0><F0>
<L><C2><F0>Speaker
<L><C0><F0>The speaker function turns On/Off the
<L><C0><F0>sound for the UI (key presses and scrolling).
<L><C0><F0>The speaker setting will not alter the sound
<L><C0><F0>for protection alarms or Go/NoGo alarms.
<L><C0><F0>
<L><C2><F0>Alarm Tone / UnReg Tone / Go_NoGo Tone
<L><C0><F0>The alarm tone for the unit during normal 
<L><C0><F0>operation and for Go-NoGo testing can be 
<L><C0><F0>turned on or off in the utility menu. 
<L><C2><F0>Contrast
<L><C0><F0>Control the contrast of the mainframe
<L><C0><F0>display.
<L><C0><F0>
<L><C2><F0>Brightness
<L><C0><F0>Control the brightness of the mainframe
<L><C0><F0>display.
<L><C0><F0>
<L><C2><F0>Language
<L><C0><F0>The DC Electronic Load supports only English.
<L><C0><F0>
<L><C0><F0>-End-";
