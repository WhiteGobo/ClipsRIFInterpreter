#pragma once

#include <clips.h>

void pred_is_list(Environment *env, UDFContext *udfc, UDFValue *out);
void pred_list_contains(Environment *env, UDFContext *udfc, UDFValue *out);
void func_make_list(Environment *env, UDFContext *udfc, UDFValue *out);
void func_count(Environment *env, UDFContext *udfc, UDFValue *out);
void func_get(Environment *env, UDFContext *udfc, UDFValue *out);
void func_sublist(Environment *env, UDFContext *udfc, UDFValue *out);
void func_append(Environment *env, UDFContext *udfc, UDFValue *out);
void func_concatenate(Environment *env, UDFContext *udfc, UDFValue *out);
void func_insert_before(Environment *env, UDFContext *udfc, UDFValue *out);
void func_remove(Environment *env, UDFContext *udfc, UDFValue *out);
void func_reverse(Environment *env, UDFContext *udfc, UDFValue *out);
void func_index_of(Environment *env, UDFContext *udfc, UDFValue *out);
void func_union(Environment *env, UDFContext *udfc, UDFValue *out);
void func_distinct_values(Environment *env, UDFContext *udfc, UDFValue *out);
void func_intersect(Environment *env, UDFContext *udfc, UDFValue *out);
void func_except(Environment *env, UDFContext *udfc, UDFValue *out);
