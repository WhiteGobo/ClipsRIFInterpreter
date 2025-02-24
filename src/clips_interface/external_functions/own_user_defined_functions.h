#pragma once

#include <clips.h>

void clipsudf_equal(Environment *env, UDFContext *udfc, UDFValue *out);

void clipsudf_import(Environment *env, UDFContext *udfc, UDFValue *out);

void clipsudf_new_blanknode(Environment *env, UDFContext *udfc, UDFValue *out);
