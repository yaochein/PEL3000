#include "../INCLUDES.H"

const BYTE Help_Seq_Normal[]="\
<M078>\
<L><C1><F0>Timing Edit for Normal Sequence
<L><C0><F0>
<L><C0><F0>A normal sequence is comprised of a 
<L><C0><F0>user-defined number of steps that when 
<L><C0><F0>executed in sequence can be used to simulate
<L><C0><F0>a DC load.
<L><C0><F0>Up to 1024 discrete steps can be configured 
<L><C0><F0>using normal sequences.„h  
<L><C0><F0>Each normal sequence can have a memo note 
<L><C0><F0>attached to it.
<L><C0><F0>Normal Sequences can be looped up to 9999 
<L><C0><F0>discrete times or for an infinite amount of times.
<L><C0><F0>Normal sequences can be configured to hold a 
<L><C0><F0>set voltage, current, power or resistance at the 
<L><C0><F0>end of the load.
<L><C0><F0>Normal Sequences can be linked together in a 
<L><C0><F0>chain. 
<L><C0><F0>Normal Sequence configuration is split into 
<L><C0><F0>Timing Edit configuration and Data Edit 
<L><C0><F0>configuration. 
<L><C0><F0>Timing Edit configuration is used to configure 
<L><C0><F0>the actual sequences, such as mode, range, 
<L><C0><F0>loops and chains.
<L><C0><F0>
<L><C2><F0>Start
<L><C0><F0>Sets which sequence is used to start a 
<L><C0><F0>chain of Normal Sequences.
<L><C0><F0>
<L><C2><F0>Seq.No
<L><C0><F0>Sets the current sequence to edit. 
<L><C0><F0>
<L><C2><F0>Memo
<L><C0><F0>A user-created note for the currently 
<L><C0><F0>selected sequence.
<L><C0><F0>
<L><C2><F0>Mode
<L><C0><F0>Operating mode for the sequence. 
<L><C0><F0>+CV mode is supported.
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
<L><C0><F0>The setting value of the load for when 
<L><C0><F0>Last Load = ON.
<L><C0><F0>
<L><C0><F0>Chain
<L><C0><F0>Sets the next sequence in the chain, when 
<L><C0><F0>not set to off.
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

