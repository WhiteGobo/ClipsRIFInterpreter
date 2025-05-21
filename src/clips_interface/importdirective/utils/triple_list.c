#include "triple_list.h"

static TripleList* find_last(TripleList* first){
	if (first == NULL) return NULL;
	TripleList* last = first;
	while (last->next != NULL){
		last = last->next;
	}
	return last;
}

TripleList* crifi_import_append_triple(TripleList* first,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type){
	TripleList *last = find_last(first);
	TripleList *new = malloc(sizeof(TripleList));
	new->next = NULL;

	new->object = malloc(strlen(object) + 1);
	if(new->object == NULL) return NULL;
	strcpy(new->object, object);
	if(object_suffix != NULL){
		new->object_suffix = malloc(strlen(object_suffix) + 1);
		if(new->object_suffix == NULL) return NULL;
		strcpy(new->object_suffix, object_suffix);
	} else {
		new->object_suffix = NULL;
	}
	new->object_type = object_type;

	new->slotkey = malloc(strlen(slotkey) + 1);
	if(new->slotkey == NULL) return NULL;
	strcpy(new->slotkey, slotkey);
	if(slotkey_suffix != NULL){
		new->slotkey_suffix = malloc(strlen(slotkey_suffix) + 1);
		if(new->slotkey_suffix == NULL) return NULL;
		strcpy(new->slotkey_suffix, slotkey_suffix);
	} else {
		new->slotkey_suffix = NULL;
	}
	new->slotkey_type = slotkey_type;

	new->slotvalue = malloc(strlen(slotvalue) + 1);
	if(new->slotvalue == NULL) return NULL;
	strcpy(new->slotvalue, slotvalue);
	if(slotvalue_suffix != NULL){
		new->slotvalue_suffix = malloc(strlen(slotvalue_suffix) + 1);
		if(new->slotvalue_suffix == NULL) return NULL;
		strcpy(new->slotvalue_suffix, slotvalue_suffix);
	} else {
		new->slotvalue_suffix = NULL;
	}
	new->slotvalue_type = slotvalue_type;
	if (last != NULL){
		last->next = new;
	}
	return new;
}

void crifi_import_free_TripleList(TripleList* first){
	TripleList *last = NULL;
	for(TripleList *x = first; x != NULL; x = x->next){
		if(last != NULL){
			free(last);
		}
		free(x->object);
		free(x->object_suffix);
		free(x->slotkey);
		free(x->slotkey_suffix);
		free(x->slotvalue);
		free(x->slotvalue_suffix);
		last = x;
	}
	if(last != NULL){
		free(last);
	}
}
