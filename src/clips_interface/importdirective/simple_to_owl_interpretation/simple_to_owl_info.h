#pragma once

#include "triple_list.h"
#include "rdf_list.h"

typedef struct simpleToOwlInfo {
	TripleList *first;
	TripleList *last;
	RDFListInfo *list_info;
} SimpleToOwlInfo;
