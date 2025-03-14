#pragma once

#include <clips.h>

bool crifi_is_list(Environment *env, CLIPSValue *arglist);
int crifi_list_count(Environment *env, CLIPSValue *list);

/**
 * TODO: remove this method
 */
bool retrieve_items_udf(Environment *env, UDFValue arglist, CLIPSValue *items);

bool retrieve_items(Environment *env, CLIPSValue arglist, CLIPSValue *items);

CLIPSValue crifi_list_get(Environment *env, CLIPSValue list, long long index);

Fact *crifi_list_concatenate(Environment *env, CLIPSValue *listlist, size_t listlist_length);

int crifi_list_new(Environment *env, CLIPSValue *values, size_t values_length, CLIPSValue *ret);

Fact *crifi_list_distinct_values(Environment *env, CLIPSValue list);

Fact *crifi_list_intersect(Environment *env, CLIPSValue leftlist, CLIPSValue rightlist);

int crifi_list_except(Environment *env, CLIPSValue list, CLIPSValue exceptions, CLIPSValue *ret);

Fact *clipsvalue_to_list(CLIPSValue val);

bool crifi_list_as_identifier(Environment *env, CLIPSValue *val, int index, CLIPSValue *target);
