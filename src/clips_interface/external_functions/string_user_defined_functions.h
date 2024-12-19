#pragma once

#include <clips.h>

void rif_is_literal_string(Environment *env, UDFContext *udfc, UDFValue *out);

void rif_is_literal_normalizedString(Environment *env, UDFContext *udfc, UDFValue *out);

void rif_is_literal_token(Environment *env, UDFContext *udfc, UDFValue *out);

void rif_is_literal_language(Environment *env, UDFContext *udfc, UDFValue *out);

void rif_is_literal_Name(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_NCName(Environment *env, UDFContext *udfc, UDFValue *out);

void rif_is_literal_NMTOKEN(Environment *env, UDFContext *udfc, UDFValue *out);

void rif_iri_string(Environment *env, UDFContext *udfc, UDFValue *out);

void rif_compare(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_concat(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_string_join(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_substring(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_string_length(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_upper_case(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_lower_case(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_encode_for_uri(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_iri_to_uri(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_escape_html_uri(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_substring_before(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_substring_after(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_replace(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_contains(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_starts_with(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_ends_with(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_matches(Environment *env, UDFContext *udfc, UDFValue *out);
