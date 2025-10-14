#creates a headerfile at LOGDATA_HEADER for each member of here defined logfiles.
#For example the content of the header file look for logfiles = [a, b]:
# const char* logmanagment_a = "/current-build-path/log/a.log";
# const char* logmanagment_b = "/current-build-path/log/b.log";
#
# Removes existing logging files.

list(APPEND logfiles
	"modelA"
)

if(NOT LOGDATA_HEADER)
	MESSAGE(FATAL_ERROR "LOGDATA_HEADER wasnt defined.")
endif(NOT LOGDATA_HEADER)

set(logfolder "${CMAKE_CURRENT_BINARY_DIR}/log")
file(MAKE_DIRECTORY "${logfolder}")

FILE(WRITE ${LOGDATA_HEADER} "/**
 * Automaticly created by logmanagment.cmake
 */
")
FOREACH(X IN ITEMS ${logfiles})
	set(log_path "${logfolder}/${X}.log")
	set(log_path_name "logmanagment_${X}")
	FILE(REMOVE ${log_path})
	FILE(APPEND ${LOGDATA_HEADER} "
const char *${log_path_name} = \"${log_path}\";")
ENDFOREACH()
