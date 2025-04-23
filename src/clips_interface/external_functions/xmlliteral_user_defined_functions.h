#pragma once

#include <clips.h>

//void rif_is_literal_string(Environment *env, UDFContext *udfc, UDFValue *out)

void rif_is_literal_XMLLiteral(Environment *env, UDFContext *udfc, UDFValue *out);

void rif_is_literal_anyURI(Environment *env, UDFContext *udfc, UDFValue *out);
