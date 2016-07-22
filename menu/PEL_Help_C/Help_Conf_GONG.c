#include "../INCLUDES.H" 

const BYTE Help_Conf_GONG[]="\
<M024>\
<L><C1><F0>Go-NoGo configuration
<L><C0><F0>
<L><C0><F0>The Go-NoGo configuration is used to create 
<L><C0><F0>pass/fail limits on the voltage or current  
<L><C0><F0>input. If the voltage/current exceeds the  
<L><C0><F0>pass/fail limits, an alarm will be output. 
<L><C0><F0>The Go-NoGo configuration can be used with 
<L><C0><F0>the Program function to create complex 
<L><C0><F0>pass/fail tests.
<L><C0><F0>
<L><C2><F0>Setting the Go-NoGo Limits
<L><C0><F0>The Go-NoGo setting limits can be set as either 
<L><C0><F0>discrete high & low values or as a percentage 
<L><C0><F0>offset from a center value.
<L><C0><F0>
<L><C2><F0>SPEC Test<C0>   
<L><C0><F0>SPEC Test is used to turn <C2>ON<C0> or <C2>OFF<C0> the
<L><C0><F0>Go/NoGo testing.
<L><C0><F0>
<L><C2><F0>Delay Time<C0>   
<L><C0><F0>Delay Time is used to delay the Go/NoGo
<L><C0><F0>testing after the <C4>Load ON/OFF<C0> is turned
<L><C0><F0>to ON.
<L><C0><F0>
<L><C0><F0>Go/NoGo limits can be set as either
<L><C0><F0>absolute values (<C2>Entry Mode<C0> set to
<L><C0><F0><C2>Value<C0>) or as a percentage offset
<L><C0><F0>from a nominal (Center) value (<C2>Entry
<L><C0><F0>(<C2>Mode<C0> set to <C2>Percent<C0>).
<L><C0><F0>
<L><C2><F0>Running a Go-NoGo Test
<L><C0><F0>Go-NoGo test results are displayed in the 
<L><C0><F0>measurement panel.
<L><C0><F0>GO indicates pass (good).
<L><C0><F0>NG indicates fail (no good). 
<L><C0><F0>
<L><C0><F0>-End-";

