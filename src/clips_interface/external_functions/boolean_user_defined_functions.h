#pragma once

#include <clips.h>

void rif_is_literal_boolean(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_cast_boolean(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_boolean_less_than(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_boolean_greater_than(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_boolean_equal(Environment *env, UDFContext *udfc, UDFValue *out);
