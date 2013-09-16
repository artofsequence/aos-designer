cmake_minimum_required( VERSION 2.8 )

set( AOSL_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( AOSL_XSD_FILE ${AOSL_ROOT_DIR}/aosl.xsd
	CACHE PATH
	"Path of the XSD file defining the AOSL format."
	FORCE
)

# TODO : add custom project with all the test xml files and the xsd file and maybe a python script that checks validity?
