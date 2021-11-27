# Parsing Lib for AoC
## This folder contains a little library for general input parsing hence to facilitate data storage in data structures
### How to use
- every input is stored either in one Input_obj object or in a list of them (user choice)
- the Lib Input_obj object is set up to contain major std:: data structures so the user can mix them up
- write your custom parse class (in N_custom_parsing namespace) overriding the default one (in N_input_parsing namespace)
