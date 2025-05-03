#include "rdf_list.h"
#include <raptor.h>
#include "clipsvalue_interface.h"
#include "crifi_lists.h"
#include "ffi_constants.h"

typedef struct rdflistinfo {
	raptor_avltree* avltree;
} RDFListInfo;

typedef struct {
	char *this_id;
	char* first;
	char* first_suffix;
	IMPORT_TERM_TYPE first_type;
	const char *next_id;
} ListEntry;

static int compare_list_entry(const ListEntry* new, const ListEntry* old);
static void free_list_entry(ListEntry*);

static ListEntry* retrieve_list_entry(RDFListInfo *info, const char *list_id);
static ListEntry* find_list_entry(RDFListInfo* info, const char* list_id);

static int compare_list_entry(const ListEntry* new, const ListEntry* old){
	int diff;
	if (new == NULL || old == NULL){
		return 0;
	}
	//diff = new->id_type - old->id_type;
	//if (diff != 0) return diff;

	diff = strcmp(new->this_id, old->this_id);
	if (diff != 0) return diff;
	return 0;
}
static void free_list_entry(ListEntry* entry) {
	free(entry->this_id);
	free(entry->first);
	free(entry->first_suffix);
	free(entry->next_id);
	free(entry);
}

RDFListInfo *new_RDFListInfo(){
	RDFListInfo *info = malloc(sizeof(RDFListInfo));
	if (info == NULL) return NULL;
	info->avltree = raptor_new_avltree(
			(raptor_data_compare_handler) compare_list_entry,
			(raptor_data_free_handler) free_list_entry, 0);
	if (info->avltree == NULL){
		free(info);
		return NULL;
	}
	return info;
}

int add_first(RDFListInfo* info,
		const char* source, const char* source_suffix,
		IMPORT_TERM_TYPE source_type,
		const char* target, const char* target_suffix,
		IMPORT_TERM_TYPE target_type)
{
	int err;
	ListEntry* entry;
	if (source_type != CRIFI_IMPORT_TERM_BNODE){
		return 1;
	}
	entry = retrieve_list_entry(info, source);

	entry->first = malloc(strlen(target) + 1);
	if (entry->first == NULL){
		return 1;
	}
	strcpy(entry->first, target);
	if (target_suffix != NULL){
		entry->first_suffix = malloc(strlen(target_suffix) + 1);
		if (entry->first_suffix == NULL){
			return 1;
		}
		strcpy(entry->first_suffix, target_suffix);
	} else {
		target_suffix = NULL;
	}
	entry->first_type = target_type;
	return 0;
}

int add_rest(RDFListInfo* info,
		const char* source, const char* source_suffix,
		IMPORT_TERM_TYPE source_type,
		const char* target, const char* target_suffix,
		IMPORT_TERM_TYPE target_type)
{
	ListEntry* entry;
	if (source_type != CRIFI_IMPORT_TERM_BNODE){
		fprintf(stderr, "rdflist only support blank nodes as source\n");
		return 1;
	}
	switch (target_type){
		case CRIFI_IMPORT_TERM_BNODE:

			entry = retrieve_list_entry(info, source);
			entry->next_id = malloc(strlen(target) +1);
			if (entry->next_id == NULL){
				return 1;
			}
			strcpy(entry->next_id, target);
			return 0;
		case CRIFI_IMPORT_TERM_URI:
			if (0==strcmp(target, _RDF_nil_)){
				//rest == NULL means end of list
				//rest is already NULL if graph is intact
				break;
			}
		default:
			fprintf(stderr, "rdflist only support blank nodes "
					"as source\n");
			return 1;
	}
	return 0;
}

void free_RDFListInfo(RDFListInfo* info){
	if(info == NULL) return;
	raptor_free_avltree(info->avltree);
	free(info);
}


CRIFI_IMPORT_GENERATE_RDFLIST get_list_as_clipsvalue(
			ImportProcess *process, RDFListInfo *info,
			const char *listid, const char *listid_suffix,
			IMPORT_TERM_TYPE listid_type, CLIPSValue *target)
{
	int err;
	int length = 0, i;
	CLIPSValue *values;
	if (info == NULL) return CRIFI_IMPORT_GENERATE_RDFLIST_UNKNOWN_ERROR;
	if (listid_type == CRIFI_IMPORT_TERM_URI){
		if (0 == strcmp(listid, _RDF_nil_)){
			err = crifi_list_new(process->graph, NULL, 0, target);
			if (err == 0){
				return CRIFI_IMPORT_GENERATE_RDFLIST_NOERROR;
			} else {
				return CRIFI_IMPORT_GENERATE_RDFLIST_UNKNOWN_ERROR;
			}
		}
		return CRIFI_IMPORT_GENERATE_RDFLIST_NOTFOUND;
	} else if (listid_type != CRIFI_IMPORT_TERM_BNODE){
		return CRIFI_IMPORT_GENERATE_RDFLIST_NOTFOUND;
	}

	for (ListEntry *tmp = find_list_entry(info, listid);
			tmp != NULL;
			tmp = find_list_entry(info, tmp->next_id))
	{
		length += 1;
	}
	if (length == 0){
		return CRIFI_IMPORT_GENERATE_RDFLIST_NOTFOUND;
	}
	values = calloc(length, sizeof(CLIPSValue));
	i = 0;
	for (ListEntry *tmp = find_list_entry(info, listid);
			tmp != NULL;
			tmp = find_list_entry(info, tmp->next_id))
	{
		err = value_suffix_to_clipsvalue(process,
				tmp->first, tmp->first_suffix, tmp->first_type,
				values + i);
		i++;
		if (err != 0){
			free(values);
			return CRIFI_IMPORT_GENERATE_RDFLIST_UNKNOWN_ERROR;
		}
	}
	err = crifi_list_new(process->graph, values, length, target);
		//err = value_suffix_to_clipsvalue(process,
		//		"asdf", NULL, CRIFI_IMPORT_TERM_URI,
		//		target);
	//err = crifi_list_new(process->graph, NULL, 0, target);
	free(values);
	switch (err){
		case 0:
			return CRIFI_IMPORT_GENERATE_RDFLIST_NOERROR;
		default:
			return CRIFI_IMPORT_GENERATE_RDFLIST_UNKNOWN_ERROR;
	}
}


static ListEntry* find_list_entry(RDFListInfo* info, const char* list_id){
	ListEntry *new;
	ListEntry searcher = {.this_id = (char*) list_id};
	ListEntry* existing;
	if (list_id == NULL){
		return NULL;
	}

	existing = (ListEntry*) raptor_avltree_search(info->avltree, &searcher);
	return existing;
}

static ListEntry* retrieve_list_entry(RDFListInfo *info, const char *list_id)
{
	int err;
	ListEntry *new;
	ListEntry searcher = {.this_id = (char*) list_id};
	ListEntry* existing;
	if (list_id == NULL){
		return NULL;
	}

	existing = (ListEntry*) raptor_avltree_search(info->avltree, &searcher);
	if (existing != NULL){
		return existing;
	}
	new = malloc(sizeof(ListEntry));
	if (new == NULL){
		return NULL;
	}
	new->this_id = malloc(strlen(list_id)+1);
	if(new->this_id == NULL){
		free(new); return NULL;
	}
	strcpy(new->this_id, list_id);
	new->next_id = NULL;
	new->first = NULL;
	new->first_suffix = NULL;
	new->first_type = CRIFI_IMPORT_TERM_UNKNOWN;

	err = raptor_avltree_add (info->avltree, new);
	if (err == 0){
		return new;
	} else {
		return NULL;
	}
}

CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_RET retrieve_rdf_list(
		ImportProcess *process,
		const char *id, const char *suffix, IMPORT_TERM_TYPE type,
		RDFListInfo* context,
		CLIPSValue* retval)
{
	CRIFI_IMPORT_GENERATE_RDFLIST err;
	err = get_list_as_clipsvalue(process, context,
					id, suffix, type, retval);
	switch(err){
		case CRIFI_IMPORT_GENERATE_RDFLIST_NOERROR:
			return CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_SUCCESS;
		case CRIFI_IMPORT_GENERATE_RDFLIST_NOTFOUND:
			return CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_NOTFOUND;
		case CRIFI_IMPORT_GENERATE_RDFLIST_UNKNOWN_ERROR:
		default:
			return CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_UNHANDLED_ERROR;
	}
}

