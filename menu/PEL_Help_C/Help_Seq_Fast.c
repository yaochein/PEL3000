#include "../INCLUDES.H"

const BYTE Help_Seq_Fast[]="\
<M078>\
<L><C1><F0>Fast Sequence
<L><C0><F0>
<L><C0><F0>A fast sequence is comprised of a 
<L><C0><F0>user-defined number of steps that can be 
<L><C0><F0>executed at a high frequency. Unlike normal 
<L><C0><F0>sequences, each step in a fast sequence 
<L><C0><F0>has the same execution time(time base). 
<L><C0><F0>
<L><C0><F0>This mode is only available for CC and CR 
<L><C0><F0>mode.
<L><C0><F0>
<L><C0><F0>Up to 1024 discrete steps can be configured 
<L><C0><F0>using fast sequences.
<L><C0><F0>
<L><C0><F0>Each fast sequence can have a memo note 
<L><C0><F0>attached to it.
<L><C0><F0>
<L><C0><F0>Fast Sequences can be looped up to 9999 discrete 
<L><C0><F0>times or for an infinite amount of times.
<L><C0><F0>
<L><C0><F0>Fast sequences can be configured to hold a set 
<L><C0><F0>current or resistance at the end of the load. 
<L><C0><F0>
<L><C0><F0>No ramping function can be used with the Fast 
<L><C0><F0>Sequence function.
<L><C0><F0>
<L><C1><F0>Timing Edit for Fast Sequence
<L><C0><F0>Fast Sequence configuration is split into Timing 
<L><C0><F0>Edit configuration and Data Edit configuration. 
<L><C0><F0>
<L><C0><F0>Timing Edit configuration is used to configure
<L><C0><F0>all the settings that are common to all the steps 
<L><C0><F0>of the fast sequence. This includes settings such 
<L><C0><F0>as the mode, range, loops and time base.
<L><C0><F0>
<L><C2><F0>Memo
<L><C0><F0>A user-created note for the currently 
<L><C0><F0>selected sequence.
<L><C0><F0>
<L><C2><F0>Mode
<L><C0><F0>Operating mode for the sequence.
<L><C0><F0>
<L><C2><F0>Range
<L><C0><F0>ILVL  Low current range, low voltage range
<L><C0><F0>IMVL  Middle current range, low voltage range
<L><C0><F0>IHVL  High current range, low voltage range
<L><C0><F0>ILVH  Low current range, high voltage range
<L><C0><F0>IMVH  Middle current range, high voltage range
<L><C0><F0>IHVH  High current range, high voltage range
<L><C0><F0>
<L><C2><F0>Loop
<L><C0><F0>Sets the amount of times to loop the 
<L><C0><F0>selected sequence.
<L><C0><F0>
<L><C2><F0>Last Load 
<L><C0><F0>Set the load condition after the end of 
<L><C0><F0>the sequence.
<L><C0><F0>
<L><C2><F0>Last
<L><C0><F0>The load setting for when Last Load is 
<L><C0><F0>set to ON.
<L><C0><F0>
<L><C2><F0>RPTSTEP
<L><C0><F0>Last step number(0003~1024) per loop 
<L><C0><F0>
<L><C1><F0>Edit Sequence:
<L><C0><F0>Press the <C3>F2<C0> softkey to enter the
<L><C0><F0>Sequence edit menu.
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

