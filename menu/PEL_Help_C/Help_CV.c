#include "../INCLUDES.H" 

const BYTE Help_CV_T[]="\
<M115>\
<L><C0><F0>The basic configuration settings are the common
<L><C0><F0>configuration settings that are used for each
<L><C0><F0>operating mode. After selecting a basic operating
<L><C0><F0>mode (CC, CR, CV or CP mode), the slew rate,
<L><C0><F0>switching mode, response rate and other common
<L><C0><F0>parameters should be configured.
<L><C0><F0>
<L><C1><F0>CV Mode:
<L><C0><F0>In Constant Voltage Mode, the unit will 
<L><C0><F0>maintain a constant voltage. In CV mode you 
<L><C0><F0>set the constant voltage level.
<L><C0><F0>
<L><C1><F0>Response:
<L><C0><F0>The response speed setting is the response 
<L><C0><F0>speed for the negative feedback control of the 
<L><C0><F0>load current when used in CV mode. Response 
<L><C0><F0>speed settings are only applicable to CV mode.
<L><C0><F0>A response speed that is too fast could cause the 
<L><C0><F0>unit to be unstable. 
<L><C0><F0>Reducing the response speed can improve 
<L><C0><F0>stability. 
<L><C0><F0>
<L><C1><F0>I Range:
<L><C0><F0>Press the <C3>F2<C0> soft-key to select current range
<L><C0><F0>Range:High, Mid, Low. 
<L><C0><F0>I Range(Resolution) vs. Model
<L><C0><F0>Model Name    High               Mid                     Low
<L><C0><F0>LSG-175     35A(1mA)       3.5A(0.1mA)     0.35A(0.01mA)
<L><C0><F0>LSG-350     70A(2mA)       7A(0.2mA)        0.7A(0.02mA)
<L><C0><F0>
<L><C1><F0>V Range:
<L><C0><F0>Select the voltage range with the V Range <C3>F3<C0>
<L><C0><F0>soft-key. Range:High, Low.
<L><C0><F0>
<L><C1><F0>Configure:
<L><C0><F0>Config the details setting.
<L><C0><F0>Press the <C3>F5<C0> softkey to enter this menu
<L><C0><F0>then press the <C4>HELP<C0> key for help
<L><C0><F0>
<L><C4><F0>Main(LOCAL):
<L><C0><F0>Sets the operating mode:CC, CV, CR, CP mode.
<L><C0><F0>Combined with the <C4>SHIFT<C0> key,Puts the
<L><C0><F0>instrument back into local mode from remote mode.
<L><C0><F0>
<L><C4><F0>FUNC:
<L><C0><F0>Sets the program function,sequence function
<L><C0><F0>or other special functions.
<L><C0><F0>Press the <C4>FUNC<C0> key to enter this
<L><C0><F0>menu then press the <C4>HELP<C0> key for help.
<L><C0><F0>
<L><C4><F0>File(Shift + FUNC):
<L><C0><F0>Accesses the file system.Press the
<L><C0><F0><C4>FILE<C0> key to enter this menu then press
<L><C0><F0>the <C4>HELP<C0> key for help.
<L><C0><F0>
<L><C4><F0>HELP:
<L><C0><F0>Access the help menu.
<L><C0><F0>Press the <C4>HELP<C0> key will brings
<L><C0><F0>up the Help information for current
<L><C0><F0>operation menu.
<L><C0><F0>
<L><C0><F0>UTILITY(Shift + HELP):
<L><C0><F0>Access the utility menu.
<L><C0><F0>For the help information of utility menu,
<L><C0><F0>have to press the <C4>HELP<C0> key again.
<L><C0><F0>
<L><C4><F0>PRESET:
<L><C0><F0>Used in conjunction with the number pad to save or
<L><C0><F0>load preset settings P0 to P9.
<L><C0><F0><C4>PRESET<C0>  key pressed in combination with the
<L><C0><F0>number pad.Presets P0-P9 <C4>Number pad<C0> can
<L><C0><F0>be recalled or saved.Press P0-P9 <C4>Number pad<C0>
<L><C0><F0>to recall preset. Hold P0-P9 <C4>digital keys<C0>
<L><C0><F0>to save preset. Combined with <L><C0><F0>the
<L><C0><F0><C4>SHIFT<C0> key on.
<L><C0><F0>
<L><C4><F0>SHIFT:
<L><C0><F0>The <C4>SHIFT<C0> key is used to access alternate
<L><C0><F0>functions assigned to select key.
<L><C0><F0>
<L><C4><F0>ENTER:
<L><C0><F0>The <C4>ENTER<C0> key is used to confirms
<L><C0><F0>selection.
<L><C0><F0>
<L><C4><F0>Number pad:
<L><C0><F0>Enter numerical values, or to save/recall
<L><C0><F0>presets (P0-P9).
<L><C0><F0>
<L><C4><F0>Decimal point (Calibration) key:
<L><C0><F0>Decimal point. Alternative function for
<L><C0><F0>enter the Calibration menu.
<L><C0><F0>
<L><C4><F0>CLEAR (LOCK) key:
<L><C0><F0>The <C4>CLEAR<C0> key is used to clears current
<L><C0><F0>values. Alternative function locks the keys 
<L><C0><F0>and the Selector knob.
<L><C0><F0>
<L><C4><F0>LOAD ON/OFF:
<L><C0><F0>The <C4>LOAD ON/OFF<C0> key is used to turn the
<L><C0><F0>load on or off.
<L><C0><F0>Yellow light: Load is currently on
<L><C0><F0>Unlit: Load is currently off
<L><C0><F0>
<L><C0><F0>For the sequence enabled, the <C4>LOAD
<L><C0><F0><C4>ON/OFF<C0> key is used to start the
<L><C0><F0>sequence(quick sequence) or stop it.
<L><C0><F0>
<L><C0><F0>For the program enabled, the <C4>LOAD
<L><C0><F0><C4>ON/OFF<C0> key is used to start the program
<L><C0><F0>or stop it.
<L><C0><F0>
<L><C0><F0>-End-";


const BYTE Help_CV[]="\
<M115>\
<L><C0><F0>The basic configuration settings are the common
<L><C0><F0>configuration settings that are used for each
<L><C0><F0>operating mode. After selecting a basic operating
<L><C0><F0>mode (CC, CR, CV or CP mode), the slew rate,
<L><C0><F0>switching mode, response rate and other common
<L><C0><F0>parameters should be configured.
<L><C0><F0>
<L><C1><F0>CV Mode:
<L><C0><F0>In Constant Voltage Mode, the unit will 
<L><C0><F0>maintain a constant voltage. In CV mode you 
<L><C0><F0>set the constant voltage level.
<L><C0><F0>
<L><C1><F0>Response:
<L><C0><F0>The response speed setting is the response 
<L><C0><F0>speed for the negative feedback control of the 
<L><C0><F0>load current when used in CV mode. Response 
<L><C0><F0>speed settings are only applicable to CV mode.
<L><C0><F0>A response speed that is too fast could cause the 
<L><C0><F0>unit to be unstable. 
<L><C0><F0>Reducing the response speed can improve 
<L><C0><F0>stability. 
<L><C0><F0>
<L><C1><F0>I Range:
<L><C0><F0>Press the <C3>F2<C0> soft-key to select current range
<L><C0><F0>Range:High,  Low. 
<L><C0><F0>I Range(Resolution) vs. Model
<L><C0><F0>Model Name    High             Low
<L><C0><F0>PEL3031E     60A(2mA)       6A(0.2mA)
<L><C0><F0>PEL3032E     15A(0.5mA)     1.5A(0.05mA)  
<L><C0><F0>
<L><C1><F0>V Range:
<L><C0><F0>Select the voltage range with the V Range <C3>F3<C0>
<L><C0><F0>soft-key. Range:High, Low.
<L><C0><F0>
<L><C1><F0>Configure:
<L><C0><F0>Config the details setting.
<L><C0><F0>Press the <C3>F5<C0> softkey to enter this menu
<L><C0><F0>then press the <C4>HELP<C0> key for help
<L><C0><F0>
<L><C4><F0>Main(LOCAL):
<L><C0><F0>Sets the operating mode:CC, CV, CR, CP mode.
<L><C0><F0>Combined with the <C4>SHIFT<C0> key,Puts the
<L><C0><F0>instrument back into local mode from remote mode.
<L><C0><F0>
<L><C4><F0>FUNC:
<L><C0><F0>Sets the program function,sequence function
<L><C0><F0>or other special functions.
<L><C0><F0>Press the <C4>FUNC<C0> key to enter this
<L><C0><F0>menu then press the <C4>HELP<C0> key for help.
<L><C0><F0>
<L><C4><F0>File(Shift + FUNC):
<L><C0><F0>Accesses the file system.Press the
<L><C0><F0><C4>FILE<C0> key to enter this menu then press
<L><C0><F0>the <C4>HELP<C0> key for help.
<L><C0><F0>
<L><C4><F0>HELP:
<L><C0><F0>Access the help menu.
<L><C0><F0>Press the <C4>HELP<C0> key will brings
<L><C0><F0>up the Help information for current
<L><C0><F0>operation menu.
<L><C0><F0>
<L><C0><F0>UTILITY(Shift + HELP):
<L><C0><F0>Access the utility menu.
<L><C0><F0>For the help information of utility menu,
<L><C0><F0>have to press the <C4>HELP<C0> key again.
<L><C0><F0>
<L><C4><F0>PRESET:
<L><C0><F0>Used in conjunction with the number pad to save or
<L><C0><F0>load preset settings P0 to P9.
<L><C0><F0><C4>PRESET<C0>  key pressed in combination with the
<L><C0><F0>number pad.Presets P0-P9 <C4>Number pad<C0> can
<L><C0><F0>be recalled or saved.Press P0-P9 <C4>Number pad<C0>
<L><C0><F0>to recall preset. Hold P0-P9 <C4>digital keys<C0>
<L><C0><F0>to save preset. Combined with <L><C0><F0>the
<L><C0><F0><C4>SHIFT<C0> key on.
<L><C0><F0>
<L><C4><F0>SHIFT:
<L><C0><F0>The <C4>SHIFT<C0> key is used to access alternate
<L><C0><F0>functions assigned to select key.
<L><C0><F0>
<L><C4><F0>ENTER:
<L><C0><F0>The <C4>ENTER<C0> key is used to confirms
<L><C0><F0>selection.
<L><C0><F0>
<L><C4><F0>Number pad:
<L><C0><F0>Enter numerical values, or to save/recall
<L><C0><F0>presets (P0-P9).
<L><C0><F0>
<L><C4><F0>Decimal point (Calibration) key:
<L><C0><F0>Decimal point. Alternative function for
<L><C0><F0>enter the Calibration menu.
<L><C0><F0>
<L><C4><F0>CLEAR (LOCK) key:
<L><C0><F0>The <C4>CLEAR<C0> key is used to clears current
<L><C0><F0>values. Alternative function locks the keys 
<L><C0><F0>and the Selector knob.
<L><C0><F0>
<L><C4><F0>LOAD ON/OFF:
<L><C0><F0>The <C4>LOAD ON/OFF<C0> key is used to turn the
<L><C0><F0>load on or off.
<L><C0><F0>Yellow light: Load is currently on
<L><C0><F0>Unlit: Load is currently off
<L><C0><F0>
<L><C0><F0>For the sequence enabled, the <C4>LOAD
<L><C0><F0><C4>ON/OFF<C0> key is used to start the
<L><C0><F0>sequence(quick sequence) or stop it.
<L><C0><F0>
<L><C0><F0>For the program enabled, the <C4>LOAD
<L><C0><F0><C4>ON/OFF<C0> key is used to start the program
<L><C0><F0>or stop it.
<L><C0><F0>
<L><C0><F0>-End-";

