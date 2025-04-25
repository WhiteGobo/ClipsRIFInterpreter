#include "info_query.h"
#include <n3parser.h>
#include "crifi_lists.h"

/*
int local_blanknode(Environment *env, const char* location, const char* id, CLIPSValue* result){
	char bnodeid[strlen(location) + strlen(id) + 20];
	sprintf(bnodeid, "_:n%s_l%s", location, id);
	result->lexemeValue = CreateSymbol(env, bnodeid);
	return 0;
}
*/
