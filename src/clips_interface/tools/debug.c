#include "debug.h"

void debugprint(FILE* stream, CLIPSValue *val){
	Multifield *mf;
	switch(val->header->type){
		case INTEGER_TYPE:
			fprintf(stream, "int%d", val->integerValue->contents);
			break;
		case FLOAT_TYPE:
			fprintf(stream, "float%f", val->floatValue->contents);
			break;
		case STRING_TYPE:
			fprintf(stream, "\"%s\"", val->lexemeValue->contents);
			break;
		case SYMBOL_TYPE:
			fprintf(stream, "%s", val->lexemeValue->contents);
			break;
		case INSTANCE_NAME_TYPE:
			fprintf(stream, "(instance)", val->lexemeValue->contents);
			break;
		case FACT_ADDRESS_TYPE:
			fprintf(stream, "Fact-%ld", FactIndex(val->factValue));
			break;
		case MULTIFIELD_TYPE:
			mf = val->multifieldValue;
			fprintf(stream, "(");
			debugprint(stream, mf->contents);
			for (int i=1; i < mf->length; i++){
				fprintf(stream, ", ");
				debugprint(stream, mf->contents + i);
			}
			fprintf(stream, ")");
			break;
		default:
			fprintf(stream, "(not implemented type for debug))");
			break;
	}
}
