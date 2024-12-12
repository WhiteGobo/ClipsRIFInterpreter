#include <ffi_clips_interface.h>

#define _CRIFI_RM_import_ "http://white.gobo/ResourceManager/import"

#define INDEX_DATA USER_ENVIRONMENT_DATA + 0
struct indexData
{
	long index;
};
#define IndexData(theEnv) \
	((struct indexData *) GetEnvironmentData(theEnv,INDEX_DATA))

bool add_needed_user_functions(struct clips_graph_container graph);
