#include "../INCLUDES.H"

const BYTE Help_Prog_main_T[]="\
<M081>\
<L><C1><F0>Timing Edit for Program
<L><C0><F0>
<L><C0><F0>The LSG series has a total of 16 different
<L><C0><F0>programs (<C2>PROG: ##<C0>) and 16 sequences
<L><C0><F0>(<C2>STEP: ##<C0>)to each program. Up to 16
<L><C0><F0>Programs can be chained together. That
<L><C0><F0>totals to 256 different Sequence 
<L><C0><F0>combinations.
<L><C0><F0>
<L><C0><F0>Each Step in each program uses
<L><C0><F0>Memory data (<C2>Memory: M###<C0>)
<L><C0><F0>Different Step can use the
<L><C0><F0>same Memory data if desired.
<L><C0><F0>
<L><C0><F0>Each Step has a number of
<L><C0><F0>configuration options.
<L><C0><F0>
<L><C2><F0>Memory:
<L><C0><F0>While executing the <C2>STEP: ##<C0> of <C2>PROG: ##<C0>,
<L><C0><F0>the load will recall the <C2>Memory: M###<C0> as
<L><C0><F0>the setting.
<L><C0><F0>
<L><C2><F0>Run:
<L><C0><F0>There have three options for the <C2>Run<C0>
<L><C0><F0>type. <C2>Skip:<C0> Temporary skip the current
<L><C0><F0>step. <C2>Auto:<C0> On the end of step,
<L><C0><F0>automatic jump to the next step.
<L><C0><F0><C2>Manual:<C0> Temporary pause the current
<L><C0><F0>step until push the <C3>Next(F1)<C0> softkey
<L><C0><F0>manually.
<L><C0><F0>
<L><C2><F0>On-Time:
<L><C0><F0>The total Load-On time for the setting of
<L><C0><F0><C2>Memory: M###<C0>. The setting range is
<L><C0><F0>0.1 ~ 60.0 seconds
<L><C0><F0>
<L><C2><F0>Off-Time:
<L><C0><F0>The total Load-Off time for the setting of
<L><C0><F0><C2>Memory: M###<C0>. The setting range is Off,
<L><C0><F0>0.1 ~ 60.0 seconds
<L><C0><F0>
<L><C2><F0>P/F-Time:
<L><C0><F0>The Pass(P)/Fail(F) Time can be set to 0.1
<L><C0><F0>seconds less than the total test time. The
<L><C0><F0>total test time is defined as: On-Time + 
<L><C0><F0>Off-Time (seconds). If Go/NoGo is turned on
<L><C0><F0>but the pass fail time is off, then Go/NoGo 
<L><C0><F0>test will continue, but there will not be a
<L><C0><F0>specified pass/fail time window.
<L><C0><F0>The setting range is Off ¡V 0.1 ~ ((On-Time+
<L><C0><F0>Off-Time) - 0.1) secouds.
<L><C0><F0>
<L><C2><F0>Short-Time:
<L><C0><F0>Determines how long a short circuit will last
<L><C0><F0>(seconds). However the shorting time
<L><C0><F0>cannot be longer than the Load-On time.
<L><C0><F0>And, Short-Time will start at the same
<L><C0><F0>time as Load-On. The setting range is Off
<L><C0><F0>¡V0.1 ~ On-Time seconds.
<L><C0><F0>
<L><C1><F0>Chain:
<L><C0><F0>Press the <C3>F1<C0> softkey, to enter the menu
<L><C0><F0>of Chain edit.
<L><C0><F0>
<L><C1><F0>Save:
<L><C0><F0>Press the <C3>F3<C0> softkey, to save all of the
<L><C0><F0>settings for the program function.
<L><C0><F0>
<L><C1><F0>Recall Default:
<L><C0><F0>Press the <C3>F4<C0> softkey, to recall the default
<L><C0><F0>sequence setting for current <C2>PROG: ##<C0>.
<L><C0><F0>This function will not effect the other
<L><C0><F0>programs.
<L><C0><F0>
<L><C1><F0>Previous Menu:
<L><C0><F0>Press the <C3>F5<C0> softkey, to return to the
<L><C0><F0>previous menu.
<L><C0><F0>
<L><C0><F0>-End-";


const BYTE Help_Prog_main[]="\
<M081>\
<L><C1><F0>Timing Edit for Program
<L><C0><F0>
<L><C0><F0>The PEL series has a total of 16 different
<L><C0><F0>programs (<C2>PROG: ##<C0>) and 16 sequences
<L><C0><F0>(<C2>STEP: ##<C0>)to each program. Up to 16
<L><C0><F0>Programs can be chained together. That
<L><C0><F0>totals to 256 different Sequence 
<L><C0><F0>combinations.
<L><C0><F0>
<L><C0><F0>Each Step in each program uses
<L><C0><F0>Memory data (<C2>Memory: M###<C0>)
<L><C0><F0>Different Step can use the
<L><C0><F0>same Memory data if desired.
<L><C0><F0>
<L><C0><F0>Each Step has a number of
<L><C0><F0>configuration options.
<L><C0><F0>
<L><C2><F0>Memory:
<L><C0><F0>While executing the <C2>STEP: ##<C0> of <C2>PROG: ##<C0>,
<L><C0><F0>the load will recall the <C2>Memory: M###<C0> as
<L><C0><F0>the setting.
<L><C0><F0>
<L><C2><F0>Run:
<L><C0><F0>There have three options for the <C2>Run<C0>
<L><C0><F0>type. <C2>Skip:<C0> Temporary skip the current
<L><C0><F0>step. <C2>Auto:<C0> On the end of step,
<L><C0><F0>automatic jump to the next step.
<L><C0><F0><C2>Manual:<C0> Temporary pause the current
<L><C0><F0>step until push the <C3>Next(F1)<C0> softkey
<L><C0><F0>manually.
<L><C0><F0>
<L><C2><F0>On-Time:
<L><C0><F0>The total Load-On time for the setting of
<L><C0><F0><C2>Memory: M###<C0>. The setting range is
<L><C0><F0>0.1 ~ 60.0 seconds
<L><C0><F0>
<L><C2><F0>Off-Time:
<L><C0><F0>The total Load-Off time for the setting of
<L><C0><F0><C2>Memory: M###<C0>. The setting range is Off,
<L><C0><F0>0.1 ~ 60.0 seconds
<L><C0><F0>
<L><C2><F0>P/F-Time:
<L><C0><F0>The Pass(P)/Fail(F) Time can be set to 0.1
<L><C0><F0>seconds less than the total test time. The
<L><C0><F0>total test time is defined as: On-Time + 
<L><C0><F0>Off-Time (seconds). If Go/NoGo is turned on
<L><C0><F0>but the pass fail time is off, then Go/NoGo 
<L><C0><F0>test will continue, but there will not be a
<L><C0><F0>specified pass/fail time window.
<L><C0><F0>The setting range is Off ¡V 0.1 ~ ((On-Time+
<L><C0><F0>Off-Time) - 0.1) secouds.
<L><C0><F0>
<L><C2><F0>Short-Time:
<L><C0><F0>Determines how long a short circuit will last
<L><C0><F0>(seconds). However the shorting time
<L><C0><F0>cannot be longer than the Load-On time.
<L><C0><F0>And, Short-Time will start at the same
<L><C0><F0>time as Load-On. The setting range is Off
<L><C0><F0>¡V0.1 ~ On-Time seconds.
<L><C0><F0>
<L><C1><F0>Chain:
<L><C0><F0>Press the <C3>F1<C0> softkey, to enter the menu
<L><C0><F0>of Chain edit.
<L><C0><F0>
<L><C1><F0>Save:
<L><C0><F0>Press the <C3>F3<C0> softkey, to save all of the
<L><C0><F0>settings for the program function.
<L><C0><F0>
<L><C1><F0>Recall Default:
<L><C0><F0>Press the <C3>F4<C0> softkey, to recall the default
<L><C0><F0>sequence setting for current <C2>PROG: ##<C0>.
<L><C0><F0>This function will not effect the other
<L><C0><F0>programs.
<L><C0><F0>
<L><C1><F0>Previous Menu:
<L><C0><F0>Press the <C3>F5<C0> softkey, to return to the
<L><C0><F0>previous menu.
<L><C0><F0>
<L><C0><F0>-End-";

