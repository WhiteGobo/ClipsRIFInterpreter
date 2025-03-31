#include "crifi_import_implementations.h"

FileImportList *append_importlocation_to_list(FileImportList *first,
					const char *id, const char *filepath,
					const char *syntax)
{
	FilepathImportidPair *new = malloc(sizeof(FilepathImportidPair));
	FileImportList *newlist = malloc(sizeof(FileImportList));
	if (newlist == NULL || new == NULL){
		free(new);
		free(newlist);
		return NULL;
	}
	new->id = id;
	new->filepath = filepath;
	new->syntax = syntax;
	newlist->first = new;
	newlist->rest = NULL;
	if (first == NULL){
		return newlist;
	}
	FileImportList *x = first;
	while (x->rest != NULL){
		x = x->rest;
	}
	x->rest = newlist;
	return first;
}

FilepathImportidPair *combine_importlocationlist(FileImportList *list){
	int length = 0, i = 0;
	FilepathImportidPair *ret;
	if (list == NULL) return NULL;
	for(FileImportList *x = list; x->rest != NULL; x = x->rest){
		length++;
	}
	ret = calloc(length + 1, sizeof(FilepathImportidPair));
	i = 0;
	for(FileImportList *x = list; x->rest != NULL; x = x->rest){
		ret[i].id = x->first->id;
		ret[i].filepath = x->first->filepath;
		ret[i].syntax = x->first->syntax;
		i++;
	}
	ret[length].id = NULL;
	ret[length].filepath = NULL;
	ret[length].syntax = NULL;
	return ret;
}
