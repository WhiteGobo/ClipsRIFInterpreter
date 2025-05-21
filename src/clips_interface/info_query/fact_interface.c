#include "info_query.h"
#include <n3parser.h>
#include "crifi_lists.h"

Fact *get_next_member(Environment *env, Fact *f){
	Deftemplate *tripletemplate = FindDeftemplate(env, MEMBERTEMPLATE);
	return GetNextFactInTemplate(tripletemplate, f);
}

Fact *get_next_subclass(Environment *env, Fact *f){
	Deftemplate *tripletemplate = FindDeftemplate(env, SUBCLASSTEMPLATE);
	return GetNextFactInTemplate(tripletemplate, f);
}
