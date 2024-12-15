#!/usr/bin/env python3

import	os
import	subprocess
import	argparse

source_folder_name	= "source_files"
suppported_boards	= [ "FRDM_MCXA153", "FRDM_MCXA156", "FRDM_MCXN236", "FRDM_MCXN947" ]

exec				= False

library_folders		= [ "_r01lib_frdm_mcxa153", "_r01lib_frdm_mcxa156", "_r01lib_frdm_mcxn236", "_r01lib_frdm_mcxn947" ]
app_template_prj	= "app_template_"
build_configs		= [ "Debug", "Release" ]

default_zip_name	= "apps_for_importing"

def main():
	if args.input_folder:
		source_folder_name	= args.input_folder

	if args.zipfile:
		output_zip_name		= args.zipfile
	else:
		output_zip_name		= default_zip_name + ".zip"

	if args.target:
		args.target		= args.target.strip( "'" )
		target_boards	= []
		for n in suppported_boards:
			print( args.target + "<>" + n )
			if args.target in n:
				target_boards	+= [ n ]
	else:
		target_boards	= suppported_boards
		
	base_dir	= os.getcwd() + "/"

	source_path	= [ i.path for i in os.scandir( base_dir + "/" + source_folder_name )  if "/." not in i.path ]
	source_path	= [ i for i in source_path if "/." not in i ]
	source_path.sort()

	print( base_dir )

	prj_name	= [ os.path.basename( i ) for i in source_path ]
	#prj_folders	= [ p + "_" + t for p in prj_name for t in target_boards ]

	print( "======= process started for .. =======" )
	print( "project sources:\n    " + "\n    ".join( prj_name ) )

	template_folders	= []
	app_folders			= []
	
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
				
				if not args.no_exec:
					subprocess.run( c, shell = True )

	commands	 = []
	commands	+= [ "rm -rf " + output_zip_name ]
	commands	+= [ "zip -r " + output_zip_name + " " + " ".join( library_folders ) + " " + " ".join( template_folders ) + " " + " ".join( app_folders ) + "> /dev/null" ]

	for c in commands:
		print( "    executing command: " + c )

		if not args.no_exec:
			subprocess.run( c, shell = True )


def command_line_handling():
	parser	= argparse.ArgumentParser( description = "r01lib MCUXpresso project generator" )
	qv_grp	= parser.add_mutually_exclusive_group()
	
	parser.add_argument( "input_folder",			help = "input source folder name" )
	parser.add_argument( "-t", "--target",			help = "target board", 			type=ascii )
	parser.add_argument( "-z", "--zipfile",			help = "output zip file name", 	type=ascii )
	qv_grp.add_argument( "-N", "--no_exec", 		help = "no execution",			action = "store_true" )
	
	return	parser.parse_args()

if __name__ == "__main__":
	args	= command_line_handling()
	
	print( args.input_folder )
	print( args.target )
	print( args.zipfile )
	print( args.no_exec )
	if args.no_exec:
		exec	= False
	main()

