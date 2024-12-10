#pragma once

#include <clips.h>

void pred_literal_not_identical(Environment *env, UDFContext *udfc, UDFValue *out);

/**
 * Expects udfc->context to be const char*
 */
void rif_cast_as(Environment *env, UDFContext *udfc, UDFValue *out);

/**
 * check datatype of literal value.
 */
void check_datatype(Environment *env, UDFContext *udfc, UDFValue *out);

void check_not_datatype(Environment *env, UDFContext *udfc, UDFValue *out);
