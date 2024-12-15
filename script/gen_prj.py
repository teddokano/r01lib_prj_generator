#!/usr/bin/env python3

import	os
import	subprocess

source_folder_name	= "source_files"
target_boards		= [ "FRDM_MCXA153", "FRDM_MCXA156", "FRDM_MCXN236", "FRDM_MCXN947" ]

library_folders		= [ "_r01lib_frdm_mcxa153", "_r01lib_frdm_mcxa156", "_r01lib_frdm_mcxn236", "_r01lib_frdm_mcxn947" ]
template_folders	= []
app_folders			= []


app_template_prj	= "app_template_"
build_configs		= [ "Debug", "Release" ]

base_dir	= os.getcwd() + "/"

source_path	= [ i.path for i in os.scandir( base_dir + "/" + source_folder_name )  if "/." not in i.path ]
source_path	= [ i for i in source_path if "/." not in i ]
source_path.sort()

print( base_dir )

prj_name	= [ os.path.basename( i ) for i in source_path ]
#prj_folders	= [ p + "_" + t for p in prj_name for t in target_boards ]

print( "======= process started for .. =======" )
print( "project sources:\n    " + "\n    ".join( prj_name ) )

for t in target_boards:
	template	= app_template_prj + t
	print( "using template : " + template )
	template_folders	+= [ template ]
	
	for p in prj_name:
		commands	= []
		new_prj	= p + "_" + t
		
		print( "    generating project: " + new_prj )
		app_folders	+= [ new_prj ]
		
		commands	+= [ "cp -r " + template + "/ " + new_prj + "/" ]	#	copy template
		commands	+= [ "cp -r " + source_folder_name + "/" + p + "/ " + new_prj + "/source/" ]	#	copy source files
		commands	+= [ "rm -rf " + " ".join( [ new_prj + "/" + i + "/" for i in build_configs ] ) ]		#	delete built folders
		commands	+= [ "sed -i -e s/'<name>" + template + "'/'<name>" + new_prj + "'/ " + new_prj + "/.project" ]
		
		for c in commands:
			print( "    executing command: " + c )
			subprocess.run( c, shell = True )

commands	= []
commands	= [ "zip -r apps_for_importing.zip " + " ".join( library_folders ) + " " + " ".join( template_folders ) + " " + " ".join( app_folders ) ]

for c in commands:
	print( "    executing command: " + c )
	subprocess.run( c, shell = True )
