#pragma once

#include "triple_list.h"
#include "rdf_list.h"

typedef struct simpleToOwlInfo {
	TripleList *first;
	TripleList *last;
	PairList *first_member;
	PairList *last_member;
	PairList *first_subclass;
	PairList *last_subclass;
	RDFListInfo *list_info;
} SimpleToOwlInfo;
