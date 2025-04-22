#include "crifi_numeric.h"


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
	NumericValue *q;
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
