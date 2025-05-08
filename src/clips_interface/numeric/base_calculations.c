#include "crifi_numeric.h"


NumericValue* crifi_numeric_create_float(double value, double precision){
	NumericValue *ret = malloc(sizeof(NumericValue));
	ret->t = NT_FLOAT;
	ret->f = value;
	ret->precision = precision;
	return ret;
}

NumericValue* crifi_numeric_create_rational(long int dividend, long int divisor){
	NumericValue *ret = malloc(sizeof(NumericValue));
	ret->t = NT_RATIONAL;
	if (divisor < 0){
		ret->dividend = -dividend;
		ret->divisor = -divisor;
	} else {
		ret->dividend = dividend;
		ret->divisor = divisor;
	}
	return ret;
}

NumericValue* crifi_numeric_add(Environment *env, NumericValue *val1, NumericValue *val2){
	long int x, y;
	float tmp;
	NumericValue *q = NULL;
	if(val1 == NULL || val2 == NULL) return NULL;

	switch (val1->t){
		case NT_RATIONAL:
			switch (val2->t){
				case NT_RATIONAL:
					x = (val1->dividend * val2->divisor)\
						     + (val2->dividend * val1->divisor);
					y = val1->divisor * val2->divisor;
					return crifi_numeric_create_rational(x, y);
					break;
				case NT_FLOAT:
					q = malloc(sizeof(NumericValue));
					q->t = NT_FLOAT;
					tmp = val1->dividend / val1->divisor;
					q->f = tmp + val2->f;
					q->precision = val2->precision;
					return q;
					break;
			}
			break;
		case NT_FLOAT:
			switch (val2->t){
				case NT_RATIONAL:
					q = malloc(sizeof(NumericValue));
					q->t = NT_FLOAT;
					tmp = val2->dividend / val2->divisor;
					q->f = tmp + val1->f;
					q->precision = val1->precision;
					return q;
					break;
				case NT_FLOAT:
					q = malloc(sizeof(NumericValue));
					q->t = NT_FLOAT;
					q->f = val1->f + val2->f;
					q->precision = val1->precision\
						      + val2->precision;
					return q;
					break;
			}
			break;
		default:
			return NULL;
	}
	return q;
}


NumericValue* crifi_numeric_multiply(Environment *env, NumericValue *val1, NumericValue *val2){
	long int x, y;
	double value, precision;
	float tmp;
	NumericValue *q = NULL;
	if(val1 == NULL || val2 == NULL) return NULL;
	switch (val1->t){
		case NT_RATIONAL:
			switch (val2->t){
				case NT_RATIONAL:
					x = val1->dividend * val2->dividend;
					y = val1->divisor * val2->divisor;
					return crifi_numeric_create_rational(x, y);
					break;
				case NT_FLOAT:
					tmp = val1->dividend / val1->divisor;
					value = tmp * val2->f;
					precision = tmp * val2->precision;
					return crifi_numeric_create_float(value, precision);
					break;
			}
			break;
		case NT_FLOAT:
			switch (val2->t){
				case NT_RATIONAL:
					tmp = val2->dividend / val2->divisor;
					value = tmp * val1->f;
					precision = tmp * val1->precision;
					return crifi_numeric_create_float(value, precision);
					break;
				case NT_FLOAT:
					value = val1->f * val2->f;
					precision = (val1->precision * val2->f)\
						      +(val2->precision*val1->f);
					return crifi_numeric_create_float(value, precision);
					break;
			}
			break;
	}
	return q;
}
