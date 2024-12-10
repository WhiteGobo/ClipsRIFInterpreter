#pragma once

#include <clips.h>


/**
 * TODO: remove this method
 */
bool retrieve_items_udf(Environment *env, UDFValue arglist, CLIPSValue *items);

bool retrieve_items(Environment *env, CLIPSValue arglist, CLIPSValue *items);

CLIPSValue crifi_list_get(Environment *env, CLIPSValue list, long long index);

Instance *crifi_list_concatenate(Environment *env, CLIPSValue *listlist, size_t listlist_length);

Instance* crifi_list_new(Environment *env, CLIPSValue *values, size_t values_length);

Instance *crifi_list_distinct_values(Environment *env, CLIPSValue list);

Instance *crifi_list_intersect(Environment *env, CLIPSValue leftlist, CLIPSValue rightlist);

Instance *crifi_list_except(Environment *env, CLIPSValue list, CLIPSValue exceptions);
