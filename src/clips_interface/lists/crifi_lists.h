#pragma once

#include "ffi_clips_interface.h"

typedef enum {
	CRIFI_LIST_REMOVE_NOERROR = 0,
	CRIFI_LIST_REMOVE_NOLIST,
	CRIFI_LIST_REMOVE_INDEX,
	CRIFI_LIST_REMOVE_USAGE,
	CRIFI_LIST_REMOVE_CREATE_LIST,
	CRIFI_LIST_REMOVE_EMPTY_LIST,
	CRIFI_LIST_REMOVE_MALLOC
} CRIFI_LIST_REMOVE_RET;

typedef enum {
	CRIFI_LIST_GET_NOERROR = 0,
	CRIFI_LIST_GET_NOLIST,
	CRIFI_LIST_GET_INDEX
} CRIFI_LIST_GET_RET;

#ifdef __cplusplus
extern "C" {
#endif

bool crifi_is_list(Environment *env, CLIPSValue *arglist);
int crifi_list_count(Environment *env, CLIPSValue *list);

Multifield* retrieve_items(Environment *env, CLIPSValue arglist);


CRIFI_LIST_REMOVE_RET crifi_list_remove(Environment *env, CLIPSValue list, long long index, CLIPSValue *ret);

CRIFI_LIST_GET_RET crifi_list_get(Environment *env, CLIPSValue list, long long index, CLIPSValue *ret);

Fact *crifi_list_concatenate(Environment *env, CLIPSValue *listlist, size_t listlist_length);

int crifi_list_new(Environment *env, CLIPSValue *values, size_t values_length, CLIPSValue *ret);

Fact *crifi_list_distinct_values(Environment *env, CLIPSValue list);

Fact *crifi_list_intersect(Environment *env, CLIPSValue leftlist, CLIPSValue rightlist);

int crifi_list_except(Environment *env, CLIPSValue list, CLIPSValue exceptions, CLIPSValue *ret);

//Fact *clipsvalue_to_list(CLIPSValue val);

bool crifi_list_as_identifier(Environment *env, CLIPSValue *val, int index, CLIPSValue *target);


#ifdef __cplusplus
}
#endif
