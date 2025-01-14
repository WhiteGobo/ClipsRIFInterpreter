#pragma once

#include <clips.h>

typedef enum {
	NT_RATIONAL,
	NT_FLOAT,
	NT_NAN
} NUMERIC_TYPE;

typedef struct {
	NUMERIC_TYPE t;
	union {
		double f;
		long int dividend;

		///describe if its +infinity or -infinity for example
		unsigned long nan_properties;
	};
	union {
		unsigned long int divisor;
		double precision;
	};
} NumericValue;


CLIPSValue crifi_create_integer(Environment *env, long long value);

CLIPSValue crifi_create_rational(Environment *env, long long dividend, long long divisor);

CLIPSValue crifi_numeric_to_clipsvalue(Environment *env, NumericValue val);

bool clipsvalue_as_numeric_value(Environment *env, CLIPSValue val, NumericValue *out);
double nv_as_float(NumericValue val);

bool clipsvalue_as_integer(Environment *env, CLIPSValue val, long long *value);
