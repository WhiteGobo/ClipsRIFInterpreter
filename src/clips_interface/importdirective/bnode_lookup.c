#include "ffi_clips_interface.h"
#include "bnode_lookup.h"
#include <raptor.h>
#include "info_query.h"

typedef struct bnodelookup{
	raptor_avltree* avltree;
} BNodeLookup;

typedef struct {
	const char *id;
	CLIPSValue clipsnode;
} BNodeEntry;

static int compare_bnode_entry(const BNodeEntry* new, const BNodeEntry* old){
	if (new == NULL || old == NULL){
		return 0;
	}
	return strcmp(new->id, old->id);
}

static void free_bnode_entry(BNodeEntry* n){
	free(n->id);
	free(n);
}

BNodeLookup* new_bnodelookup(){
	BNodeLookup *ret = malloc(sizeof(BNodeLookup));
	ret->avltree = raptor_new_avltree(
			(raptor_data_compare_handler) compare_bnode_entry,
			(raptor_data_free_handler) free_bnode_entry,
			0);
	if (ret->avltree == NULL) return NULL;
	return ret;
}

void free_bnodelookup(BNodeLookup *bnode_lookup){
	raptor_free_avltree(bnode_lookup->avltree);
	free(bnode_lookup);
}


static int new_bnode_entry(BNodeLookup *bnode_lookup, const char *id,
						CLIPSValue* value){
	int err;
	if (bnode_lookup == NULL || id == NULL){
		return 1;
	}
	BNodeEntry *ret = malloc(sizeof(BNodeEntry));
	if (ret == NULL){
		return 2;
	}
	ret->id = malloc(strlen(id) + 1);
	if (ret->id == NULL){
		free(ret);
		return 2;
	}
	strcpy(ret->id, id);
	ret->clipsnode.value = value->value;

	err = raptor_avltree_add(bnode_lookup->avltree, ret);
	if (err != 0){
		free(ret->id);
		free(ret);
	}
	return err;
}

int retrieve_blanknode(crifi_graph *graph, const char *bnode_id,
			BNodeLookup *bnode_lookup, CLIPSValue* retval){
	int err;
	BNodeEntry searcher = {.id = bnode_id};
	BNodeEntry* existing;

	existing = (BNodeEntry*) raptor_avltree_search(bnode_lookup->avltree, &searcher);
	if (existing == NULL){
		err = new_blanknode(graph, retval);
		if (err != 0) return err;
		err = new_bnode_entry(bnode_lookup, bnode_id, retval);
		if (err != 0) return err;
	} else {
		retval->value = existing->clipsnode.value;
	}
	return 0;
}
