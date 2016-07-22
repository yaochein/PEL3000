#include "../INCLUDES.H"

const BYTE Help_NSeq_Edit[]="\
<M061>\
<L><C1><F0>Data Edit for Normal Sequence
<L><C0><F0>
<L><C0><F0>Normal Sequence configuration is split into 
<L><C0><F0>Timing Edit configuration and Data Edit 
<L><C0><F0>configuration.
<L><C0><F0>
<L><C0><F0>Data Edit configuration is used to create 
<L><C0><F0>the actual steps used in each sequence.
<L><C0><F0>
<L><C2><F0>Step
<L><C0><F0>Selects/displays the current step in the 
<L><C0><F0>sequence. 
<L><C0><F0>The number of available steps is dependent 
<L><C0><F0>on the number of steps added using the 
<L><C0><F0><C3>Insert Point[F1]<C0> functions.
<L><C0><F0>
<L><C2><F0>Value
<L><C0><F0>The current, voltage, power or resistance 
<L><C0><F0>setting for the selected operating mode.
<L><C0><F0>
<L><C2><F0>Load
<L><C0><F0>Turns the load on or off for the selected step. 
<L><C0><F0>
<L><C2><F0>RAMP
<L><C0><F0>When turned on the current transition is 
<L><C0><F0>evenly ramped from the start of the step to 
<L><C0><F0>the end of the step. When turned off the 
<L><C0><F0>current transition is stepped.
<L><C0><F0>
<L><C2><F0>TRIG OUT
<L><C0><F0>When TRIG OUT is set to ON, a trigger 
<L><C0><F0>signal is output from the TRIG OUT BNC 
<L><C0><F0>terminal at the start of the step.
<L><C0><F0>
<L><C2><F0>PAUSE
<L><C0><F0>Pause: Inserts a pause at the end of the 
<L><C0><F0>sequence. When paused, the unit will pause 
<L><C0><F0>at the end of step current/voltage/resistance/
<L><C0><F0>power level. The sequence can be resumed by 
<L><C0><F0>pressing <C3>Next[F2]<C0> or by using an 
<L><C0><F0>external trigger signal
<L><C0><F0>
<L><C3><F0>Insert Point:
<L><C0><F0>Press <C3>Insert Point[F1]<C0> to add a 
<L><C0><F0>step to the sequence after the current step.
<L><C0><F0>
<L><C3><F0>Delete Point:
<L><C0><F0>Press <C3>Delete Point[F2]<C0> to delete a 
<L><C0><F0>step to the sequence after the current step.
<L><C0><F0>
<L><C1><F0>Save:
<L><C0><F0>Press the <C3>F3<C0> softkey, to save all of the
<L><C0><F0>settings for the sequence function.
<L><C0><F0>
<L><C1><F0>Previous Menu:
<L><C0><F0>Press the <C3>F5<C0> softkey, to return to the
<L><C0><F0>previous menu.
<L><C0><F0>
<L><C0><F0>-End-";

