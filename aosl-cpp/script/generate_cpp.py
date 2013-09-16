"""
    AOSL CPP : XSD to C++ Code Generation
    
    Python : 3.x
    
    This script assume that http://www.codesynthesis.com/products/xsd/ is available in the path.

"""

import os
import os.path
import sys
import shutil
import subprocess
import re
import logging

# Name of the log file.
LOG_PATH = 'generate_cpp.log'

# Path of the file where the list of generated files will be written.
GENERATED_SOURCE_LIST_LOG_PATH = "generate_files.log"

# Path of the XSD file to use to generate the code
AOSL_XSD_PATH = os.path.abspath( "../../../aosl/aosl.xsd" )

# Path of the directory where the generated C++ header files have to be installed.
AOSCPP_AOSL_INCLUDE_PATH = os.path.abspath( "../include/aosl" )

# Path of the directory where the genreated C++ source files have to be installed.
AOSCPP_AOSL_SOURCE_PATH = os.path.abspath( "../source/aosl" )

# Regex pattern to detect header files 
HEADER_FILE_REGEX_PATTERN = r"[\w_]+[.](hpp|inl)"

# Regex pattern to detect header, inline and source files 
CODE_FILE_REGEX_PATTERN = r"[\w_]+[.](hpp|inl|cpp)"

# Code Synthesis application name to use.
CODE_SYNTHESIS_GENERATOR = "xsd"

# Code Synthesis configuration file path.
CODE_SYNTHESIS_CONFIG_FILEPATH = os.path.abspath( "generate_cpp.cfg" )

# Code Synthesis generator command and parameters
GENERATOR_COMMAND = [ CODE_SYNTHESIS_GENERATOR
                    , "cxx-tree"
                    , "--options-file"
                    , CODE_SYNTHESIS_CONFIG_FILEPATH
                    , AOSL_XSD_PATH
                    ]


def log( text ):
    logging.debug( text )
    print( text )
                    
def process_files( dir_path , regex_pattern, process, action_text ):
    dir_path = os.path.abspath( dir_path )
    log( "Looking in directory : " + dir_path + " for action : " + action_text )
    file_names = os.listdir( dir_path )
    compiled_pattern = re.compile( regex_pattern )
    
    log("Files in path : " )
    for filename in file_names :
        file_path = os.path.abspath( os.path.join( dir_path , filename ) )
        log( " -> " + filename )
        
        if os.path.isfile( file_path ) :
            if compiled_pattern.match( filename ) :
                log( "        Matches! " + action_text + "..." )
                process( file_path )
            else:
                log( "        Don't match!" )
        else:
            log( "        Not a file!" )

def remove_files( dir_path, regex_pattern ):
    process_files( dir_path, regex_pattern, os.remove, "Removing" )
    
def move_files( dir_path, dest_path, regex_pattern ):
    
    class FileMover:
        def __init__( self, dest_path ):
            self.dest_path = dest_path
        def __call__( self, file_path ) :
            shutil.move( file_path, self.dest_path )
    
    process_files( dir_path, regex_pattern, FileMover( dest_path ), "Moving" )


logging.basicConfig(filename=LOG_PATH,level=logging.DEBUG)

log( "==== AOSL CPP : XSD to C++ Code Generation - " " ====" )
log( "XSD file path = " + os.path.abspath( AOSL_XSD_PATH ) )
log( "------------------------------------------------------------\n" )
# First remove the previously generated files ...
log( "== Remove previously generated files ==" )
remove_files( dir_path=AOSCPP_AOSL_SOURCE_PATH, regex_pattern=CODE_FILE_REGEX_PATTERN )
remove_files( dir_path=AOSCPP_AOSL_INCLUDE_PATH, regex_pattern=HEADER_FILE_REGEX_PATTERN )

# Now generate the files ...
log( "== Generate files from xsd! ==" )
subprocess.call( GENERATOR_COMMAND )

# Move the headers and inline files in the include directory ...
log( "== Move generated files to include directory ==" )
log( "Include path = " + AOSCPP_AOSL_INCLUDE_PATH )
move_files( dir_path=AOSCPP_AOSL_SOURCE_PATH, dest_path=AOSCPP_AOSL_INCLUDE_PATH, regex_pattern=HEADER_FILE_REGEX_PATTERN )


log( "==== AOSL CPP : End ====" )
log( "See " + GENERATED_SOURCE_LIST_LOG_PATH + " for the list of generated files." )
print("#### Logged in " + LOG_PATH + " ####" )


