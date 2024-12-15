# r01lib_prj_generator

## What is this?

MCUXpresso project generator for `r01lib` applications.  
The `r01lib` is a library to abstract MCX microcontrollers. It enables to run same code on every supported MCX.  
A user application code is written in C++ and need to be in an application project which is copied from a template project.  

For each MCX, each template project is need to be applied to have necessary settings.  
When user is making new application for each MCXs, copying the template and source files into a source folder. This is painful process if there are several applications and supported targets.   
On addition to this, the maintenance (project setting change, etc) for those multiple projects may make mis-configurations. 

This generator helps to make application projects from single source of source-code and template.  
The copy operations for source-code and templates are done automatically for each application-target projects.  

## How to use?

A simple script command does project generation.  
```sh
./script/gen_prj.py source_files/general_tests/
```
This command generates projects from `source_files/general_tests/` for all targets.  
The output will be available as `general_tests_...zip` which can be imported into MCUXpresso IDE directly.  

If user need to generate the projects for specific target only, then `-t` option can be used. 
```sh
./script/gen_prj.py source_files/general_tests/ -t 236
```
The argument for the `-t` option is not need to be a complete string to specify the target. In sample above, it only have `236` but script can recognize it is for `FRDM_MCXN236`.  
Available target list can be found as `suppported_boards` in the script code. 
