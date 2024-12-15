#!/usr/bin/env python3

import	os
import	subprocess
import	argparse

suppported_boards	= [ "FRDM_MCXA153", "FRDM_MCXA156", "FRDM_MCXN236", "FRDM_MCXN947" ]

library_folders		= [ "_r01lib_frdm_mcxa153", "_r01lib_frdm_mcxa156", "_r01lib_frdm_mcxn236", "_r01lib_frdm_mcxn947" ]
app_template_prj	= "app_template_"
build_configs		= [ "Debug", "Release" ]

lib_and_template	= "library_and_template_projects"

def main():
	base_dir	= os.getcwd() + "/"

	source_folder_path	= os.path.dirname( args.input_folder )
	source_folder_name	= os.path.basename( source_folder_path )

	if args.target:
		args.target		= args.target.strip( "'" )
		target_boards	= []
		for n in suppported_boards:
			if args.target in n:
				target_boards	+= [ n ]
	else:
		target_boards	= suppported_boards

	if args.zipfile:
		output_zip_name		= args.zipfile
	else:
		output_zip_name		= source_folder_name + "_" + "_".join( target_boards ) + ".zip"

	source_path	= [ i.path for i in os.scandir( base_dir + "/" + source_folder_path )  if "/." not in i.path ]
	source_path	= [ i for i in source_path if "/." not in i ]
	source_path.sort()

	prj_name	= [ os.path.basename( i ) for i in source_path ]

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
			
			commands	+= [ "cp -r " + lib_and_template + "/" + template + "/ " + new_prj + "/" ]	#	copy template
			commands	+= [ "cp -r " + source_folder_name + "/" + p + "/ " + new_prj + "/source/" ]	#	copy source files
			commands	+= [ "rm -rf " + " ".join( [ new_prj + "/" + i + "/" for i in build_configs ] ) ]		#	delete built folders
			commands	+= [ "sed -i -e s/'<name>" + template + "'/'<name>" + new_prj + "'/ " + new_prj + "/.project" ]
			
			for c in commands:
				print( "    executing command: " + c )
				
				if not args.no_exec and not args.delete:
					subprocess.run( c, shell = True )

	### zipping

	try:
		os.chdir( base_dir + lib_and_template )
	except:
		print( "  !!!!!!!!!!  error: couldn't 'cd' to 'library_and_template_projects/'" )
	else:
		commands	 = []
		commands	+= [ "rm -rf ../" + output_zip_name ]
#		commands	+= [ "zip -r ../" + output_zip_name + " " + " ".join( library_folders ) + " " + " ".join( template_folders ) + "> /dev/null" ]
		commands	+= [ "zip -r ../" + output_zip_name + " " + " ".join( library_folders ) + " " + " ".join( template_folders ) ]

		for c in commands:
			print( "    executing command: " + c )

			if not args.no_exec:
				subprocess.run( c, shell = True )

	try:
		os.chdir( base_dir )
	except:
		pass

	commands	 = []
	commands	+= [ "zip -r " + output_zip_name + " " + " ".join( app_folders ) + "> /dev/null" ]
#	commands	+= [ "zip -r " + output_zip_name + " " + " ".join( app_folders ) ]

	for c in commands:
		print( "    executing command: " + c )

		if not args.no_exec:
			subprocess.run( c, shell = True )
	"""
	"""

	### deleting projects after zipping

	if not args.keep:
		commands	 = []
		commands	+= [ "rm -rf " + " ".join( app_folders ) ]

		for c in commands:
			print( "    executing command: " + c )

			if not args.no_exec:
				subprocess.run( c, shell = True )


def command_line_handling():
	parser	= argparse.ArgumentParser( description = "r01lib MCUXpresso project generator" )
	qv_grp	= parser.add_mutually_exclusive_group()
	
	parser.add_argument( "input_folder",			help = "input source folder name" )
	parser.add_argument( "-t", "--target",			help = "target board", 				type=ascii )
	parser.add_argument( "-z", "--zipfile",			help = "output zip file name", 		type=ascii )
	qv_grp.add_argument( "-d", "--delete", 			help = "delete project folders",	action = "store_true" )
	qv_grp.add_argument( "-k", "--keep", 			help = "keep project folders",		action = "store_true" )
	qv_grp.add_argument( "-N", "--no_exec", 		help = "no execution",				action = "store_true" )
	
	return	parser.parse_args()

if __name__ == "__main__":
	args	= command_line_handling()
	
	if args.no_exec:
		exec	= False
	main()

