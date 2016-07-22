#include "../INCLUDES.H" 

const BYTE Help_File_chan[]="\
<M079>\
<L><C1><F0>File System
<L><C0><F0>
<L><C0><F0>The DC Electronic Load can save and recall system 
<L><C0><F0>settings, preset data, memory data, Go-NoGo 
<L><C0><F0>settings as well as normal and fast 
<L><C0><F0>sequences to internal memory or to USB.
<L><C0><F0>
<L><C0><F0>The DC Electronic Load file system can save 
<L><C0><F0>files to internal memory (Media|Memory) and 
<L><C0><F0>external memory (Media|USB). 
<L><C0><F0>
<L><C0><F0>To save or recall Memory, Setup or Preset data, 
<L><C0><F0>the DC Electronic Load uses a three tier system 
<L><C0><F0>where files are saved or recalled in the 
<L><C0><F0>following order:
<L><C0><F0>Active settings - Internal memory - USB.
<L><C0><F0>
<L><C0><F0>For normal and fast sequences however, files 
<L><C0><F0>can be saved or recalled directly to/from USB 
<L><C0><F0>memory. 
<L><C0><F0>
<L><C1><F0>File Types
<L><C0><F0>
<L><C2><F0>Memory Data
<L><C0><F0>Memory data contains general settings and is 
<L><C0><F0>used for creating programs. Memory Data 
<L><C0><F0>contains the operating mode, range, response 
<L><C0><F0>and Go/NoGo settings. Memory data can be 
<L><C0><F0>stored both internally and externally to USB. 
<L><C0><F0>Preset data and Memory data store the same 
<L><C0><F0>contents.
<L><C0><F0>Internal Format  M001 ~ M256
<L><C0><F0>External Format  model no_file no.M 
<L><C0><F0>
<L><C2><F0>Setup Data
<L><C0><F0>Setup data contains all general configuration 
<L><C0><F0>settings, protection settings, program and 
<L><C0><F0>program chain settings, as well as parallel 
<L><C0><F0>configuration settings. 
<L><C0><F0>Internal Format  1 ~ 100
<L><C0><F0>External Format  model no_file no.S
<L><C0><F0>
<L><C2><F0>Preset Data  
<L><C0><F0>Preset Data contains the same settings as the 
<L><C0><F0>Memory Data. Preset Data contains the 
<L><C0><F0>operating mode, range, response and Go-NoGo 
<L><C0><F0>settings. 
<L><C0><F0>Internal Format  P0 ~ P9
<L><C0><F0>External Format  model no_file no.P 
<L><C0><F0>
<L><C2><F0>NSeq Data  
<L><C0><F0>NSeq Data contains the Normal Sequence 
<L><C0><F0>settings.
<L><C0><F0>Internal Format  None
<L><C0><F0>External Format  model no_file no.N 
<L><C0><F0>
<L><C2><F0>FSeq Data  
<L><C0><F0>FSeq Data contains the Fast Sequence settings. 
<L><C0><F0>Internal Format  None
<L><C0><F0>External Format  model no_file no.F
<L><C0><F0>
<L><C1><F0>Saving / Recalling Files to Internal Memory
<L><C0><F0>When saving / recalling Memory, Setup or Preset  
<L><C0><F0>Data to internal memory, the currently active 
<L><C0><F0>setting is saved to one of the internal memory 
<L><C0><F0>slots. 
<L><C0><F0>Memory Data has 256 memory slots, Setup 
<L><C0><F0>Data has 100 memory slots and Preset Data has 
<L><C0><F0>10 memory slots. 
<L><C0><F0>
<L><C1><F0>Saving / Recalling Files to USB Memory
<L><C0><F0>When saving / recalling files to USB memory, 
<L><C0><F0>all the memory locations from the selected 
<L><C0><F0>data type are saved as a single file to the 
<L><C0><F0>USB file path directory. 
<L><C0><F0>
<L><C0><F0>-End-";
