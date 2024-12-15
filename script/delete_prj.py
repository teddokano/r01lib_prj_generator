#!/usr/bin/env python3

import	os
import	subprocess

source_folder_name	= "source_files"
target_boards		= [ "FRDM_MCXA153", "FRDM_MCXA156", "FRDM_MCXN236", "FRDM_MCXN947" ]

app_template_prj	= "app_template_"
build_configs		= [ "Debug", "Release" ]

base_dir	= os.getcwd() + "/"

source_path	= [ i.path for i in os.scandir( base_dir + "/" + source_folder_name )  if "/." not in i.path ]
source_path	= [ i for i in source_path if "/." not in i ]
source_path.sort()

print( base_dir )

prj_name	= [ os.path.basename( i ) for i in source_path ]
prj_folders	= [ p + "_" + t for p in prj_name for t in target_boards ]

print( "======= process started for .. =======" )
print( "project folders:\n    " + "\n    ".join( prj_folders ) )

commands	= []
commands	+= [ "rm -rf " + " ".join( prj_folders ) ]		#	delete project folders

for c in commands:
	print( "    executing command: " + c )
	subprocess.run( c, shell = True )
