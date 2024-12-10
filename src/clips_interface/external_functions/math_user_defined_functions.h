#pragma once

#include <clips.h>

typedef struct {
	bool invert;
} ContextTypecheck;

void rif_numeric_add(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_numeric_subtract(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_numeric_multiply(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_numeric_divide(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_numeric_integer_divide(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_numeric_integer_mod(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_numeric_equal(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_numeric_not_equal(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_numeric_less_than(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_numeric_less_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_numeric_greater_than(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_numeric_greater_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out);


void rif_is_literal_double(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_float(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_hexBinary(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_decimal(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_integer(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_long(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_int(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_short(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_byte(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_nonNegativeInteger(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_positiveInteger(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_unsignedLong(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_unsignedInt(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_unsignedShort(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_unsignedByte(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_nonPositiveInteger(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_negativeInteger(Environment *env, UDFContext *udfc, UDFValue *out);

void rif_is_literal_not_double(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_not_float(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_not_hexBinary(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_not_decimal(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_not_integer(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_not_long(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_not_int(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_not_short(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_not_byte(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_not_nonNegativeInteger(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_not_positiveInteger(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_not_unsignedLong(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_not_unsignedInt(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_not_unsignedShort(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_not_unsignedByte(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_not_nonPositiveInteger(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_is_literal_not_negativeInteger(Environment *env, UDFContext *udfc, UDFValue *out);
