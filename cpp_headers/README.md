# Parsing Lib for AoC
## This folder contains a little library for general input parsing hence to facilitate data storage in data structures
### How to use
- every input is stored either in one Input_obj object or in a list of them (user choice)
- the Lib Input_obj object is set up to contain major std:: data structures so the user can mix them up
- write your custom parse class (in N_custom_parsing namespace) overriding the default one (in N_input_parsing namespace)
- in main driver code include
```
#include "custom_parser.h"
```

### Compilation
- the user must modify only "custom_parser.h/cpp" and "test_main.cpp" files (main driver and parse object methods overriding)
- the Lib is tested on g++ compiler version 10.2.0 with the command 
```
g++ test_main.cpp custom_parser.cpp mc.cpp
```
