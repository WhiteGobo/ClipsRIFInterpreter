#include "pair_list.h"

static PairList* find_last(PairList* first){
	if (first == NULL) return NULL;
	PairList* last = first;
	while (last->next != NULL){
		last = last->next;
	}
	return last;
}

PairList* crifi_import_append_pair(PairList* first,
		const char *left, const char *left_suffix,
		IMPORT_TERM_TYPE left_type,
		const char *second, const char *second_suffix,
		IMPORT_TERM_TYPE second_type){
	PairList *last = find_last(first);
	PairList *new = malloc(sizeof(PairList));
	new->next = NULL;

	new->left = malloc(strlen(left) + 1);
	if(new->left == NULL) return NULL;
	strcpy(new->left, left);
	if(left_suffix != NULL){
		new->left_suffix = malloc(strlen(left_suffix) + 1);
		if(new->left_suffix == NULL) return NULL;
		strcpy(new->left_suffix, left_suffix);
	} else {
		new->left_suffix = NULL;
	}
	new->left_type = left_type;

	new->second = malloc(strlen(second) + 1);
	if(new->second == NULL) return NULL;
	strcpy(new->second, second);
	if(second_suffix != NULL){
		new->second_suffix = malloc(strlen(second_suffix) + 1);
		if(new->second_suffix == NULL) return NULL;
		strcpy(new->second_suffix, second_suffix);
	} else {
		new->second_suffix = NULL;
	}
	new->second_type = second_type;
	if (last != NULL){
		last->next = new;
	}
	return new;
}

void crifi_import_free_PairList(PairList* first){
	PairList *last = NULL;
	for(PairList *x = first; x != NULL; x = x->next){
		if(last != NULL){
			free(last);
		}
		free(x->left);
		free(x->left_suffix);
		free(x->second);
		free(x->second_suffix);
		last = x;
	}
	if(last != NULL){
		free(last);
	}
}
