#pragma once

#include <clips.h>

void rif_PlainLiteral_from_string_lang(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_string_from_PlainLiteral(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_lang_from_PlainLiteral(Environment *env, UDFContext *udfc, UDFValue *out);

void rif_cast_as_PlainLiteral(Environment *env, UDFContext *udfc, UDFValue *out);

void rif_is_literal_PlainLiteral(Environment *env, UDFContext *udfc, UDFValue *out);

void rif_PlainLiteral_compare(Environment *env, UDFContext *udfc, UDFValue *out);

void rif_matches_language_range(Environment *env, UDFContext *udfc, UDFValue *out);
