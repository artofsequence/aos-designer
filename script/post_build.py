
import sys
import os.path
import shutil

BUILD_MODE = sys.argv[1]
BUILD_DIR = sys.argv[2]
DEPENDENCIES_BINARIES_PATHS = sys.argv[3:]


def setup_dependencies_binaries():
	for dependency_bin_path in DEPENDENCIES_BINARIES_PATHS:
		full_path = os.path.realpath( dependency_bin_path )
		target_path = os.path.realpath( os.path.join( BUILD_DIR, os.path.basename( dependency_bin_path ) ) )
		print( "Copying {0} to {1} ...".format( full_path, target_path ) )
		
		if not os.path.exists( target_path ) and not os.path.isdir( target_path ) and not os.path.isfile( target_path ):
			shutil.copy( full_path, target_path )
		else:
			print( "    Already there : skipped!" )
	

	
	
setup_dependencies_binaries()
