#include "info_query.h"
#include <n3parser.h>
#include "crifi_lists.h"

Fact *get_next_triple(Environment *env, Fact *f){
	Deftemplate *tripletemplate = FindDeftemplate(env, TRIPLETEMPLATE);
	return GetNextFactInTemplate(tripletemplate, f);
}

Fact *get_next_list(Environment *env, Fact *f){
	Deftemplate *tripletemplate = FindDeftemplate(env, ATOMLISTTEMPLATE);
	return GetNextFactInTemplate(tripletemplate, f);
}

static bool clipsfact_to_identifier(Environment *env, Fact *f, CLIPSValue *result) {
	if (f == NULL || result == NULL){
		return false;
	}
	CLIPSValue tmpval = {.factValue = f};
	if (crifi_is_list(env, &tmpval)){
		return crifi_list_as_identifier(env, &tmpval, 0, result);
	}
	return false;
}

bool clipsvalue_is_uri(Environment *env, CLIPSValue val){
	const char *cntnt;
	//if (val == NULL) return false;
        switch (val.header->type) {
                case SYMBOL_TYPE:
			if (
					val.lexemeValue == FalseSymbol(env)
					|| val.lexemeValue == TrueSymbol(env)
			   ){
				return false;
			}
			cntnt = val.lexemeValue->contents;
			if (0==memcmp(cntnt, "_:", 2)){
				return false;
			} else {
				return true;
			}
			break;
		case FACT_ADDRESS_TYPE:
			return NULL != extract_uri(env, val.header);
			break;
	}
	return false;
}

bool clipsvalue_is_bnode(Environment *env, CLIPSValue val){
	bool ret;
	const char *cntnt;
	CLIPSValue tmpval = {.voidValue = VoidConstant(env)};
	Deftemplate* facttempl;
	//if (val == NULL) return false;
        switch (val.header->type) {
                case SYMBOL_TYPE:
			if (
					val.lexemeValue == FalseSymbol(env)
					|| val.lexemeValue == TrueSymbol(env)
			   ){
				return false;
			}
			cntnt = val.lexemeValue->contents;
			if (0==memcmp(cntnt, "_:", 2)){
				return true;
			}
			return false;
		case FACT_ADDRESS_TYPE:
			if (!clipsfact_to_identifier(env, val.factValue, &tmpval)){
				return false;
			}
			switch(tmpval.header->type){ //this prevents loops
				case SYMBOL_TYPE:
					return clipsvalue_is_bnode(env, tmpval);
			}
			return false;
	}
	return false;
}

bool clipsvalue_is_literal(Environment *env, CLIPSValue val){
	const char *cntnt;
	//if (val == NULL) return false;
        switch (val.header->type) {
		case STRING_TYPE:
                case INTEGER_TYPE:
                case FLOAT_TYPE:
			return true; break;
                case SYMBOL_TYPE:
			if (
					val.lexemeValue == FalseSymbol(env)
					|| val.lexemeValue == TrueSymbol(env)
			   ){
				return true;
			} else {
				return false;
			}
			break;
	}
	return false;
}

char *extract_uri(Environment *env, TypeHeader *head){
	CLIPSValue val = {.header=head};
	char *ret = NULL;
	CLIPSValue tmpval = {.voidValue = env->VoidConstant};
	size_t orig_l;
	if (head == NULL) return NULL;
        switch (val.header->type){
                case SYMBOL_TYPE:
			orig_l = strlen(val.lexemeValue->contents);
			ret = malloc(orig_l - 1);
			memcpy(ret, val.lexemeValue->contents +1, orig_l-2);
			ret[orig_l-2] = '\0';
			break;
		case FACT_ADDRESS_TYPE:
			if (!clipsfact_to_identifier(env, val.factValue, &tmpval)){
				return NULL;
			}
			switch(tmpval.header->type){
				case SYMBOL_TYPE:
				case STRING_TYPE:
					if (clipsvalue_is_uri(env, tmpval)){
						return extract_uri(env, tmpval.header);
					} else {
						return NULL;
					}
				default: //no loop
					return NULL;
			}
			return NULL;
			break;
	}
	return ret;
}

char *extract_bnodeid(Environment *env, TypeHeader *head){
	CLIPSValue val = {.header=head};
	CLIPSValue tmpval = {.voidValue = VoidConstant(env)};
	char *ret = NULL;
        switch (val.header->type) {
                case SYMBOL_TYPE:
			ret = malloc(strlen(val.lexemeValue->contents) - 1);
			strcpy(ret, val.lexemeValue->contents + 2);
			return ret;
		case FACT_ADDRESS_TYPE:
			if (!clipsfact_to_identifier(env, val.factValue, &tmpval)){
				return NULL;
			}
			switch(tmpval.header->type){ //prevents loops
				case SYMBOL_TYPE:
					if (clipsvalue_is_bnode(env, tmpval)){
						return extract_bnodeid(env, tmpval.header);
					} else {
						return NULL;
					}
			}
			return NULL;
			break;
	}
	return NULL;
}

char *extract_lexical(Environment *env, TypeHeader *head){
	char *ret;
	CLIPSValue val = {.header = head};
	switch (val.header->type){
		case STRING_TYPE:
			return lexeme_extract_lexical(env, val.lexemeValue);
		case INTEGER_TYPE:
			ret = malloc(12 * sizeof(char));
			sprintf(ret, "%ld", val.integerValue->contents);
			return ret;
		case FLOAT_TYPE:
			ret = malloc(10 * sizeof(char));
			sprintf(ret, "%f", val.floatValue->contents);
			return ret;
	}
	return NULL;
}

char *extract_datatype(Environment *env, TypeHeader *head){
	char *ret;
	CLIPSValue val = {.header = head};

	switch (val.header->type){
		case STRING_TYPE:
			return lexeme_extract_datatype(env, val.lexemeValue);
		case INTEGER_TYPE:
			ret = malloc(sizeof(_XS_integer_) + 1);
			sprintf(ret, _XS_integer_);
			return ret;
		case FLOAT_TYPE:
			ret = malloc(sizeof(_XS_float_) + 1);
			sprintf(ret, _XS_float_);
			return ret;
	}
	return NULL;
}

char *extract_lang(Environment *env, TypeHeader *head){
	CLIPSValue val = {.header = head};
	switch (val.header->type){
		case STRING_TYPE:
			return lexeme_extract_lang(env, val.lexemeValue);
	}
	return NULL;
}


bool crifi_infoquery_unpack_member(Environment *env, CLIPSValue member, CLIPSValue *instance, CLIPSValue *cls)
{
	switch (member.header-> type){
		case FACT_ADDRESS_TYPE:
			break;
		default:
			return false;
	}
	switch (GetFactSlot(member.factValue, MEMBERINSTANCE, instance)) {
		case GSE_NO_ERROR:
			break;
		default:
			return false;
	}
	switch (GetFactSlot(member.factValue, MEMBERCLASS, cls)) {
		case GSE_NO_ERROR:
			break;
		default:
			return false;
	}
	return true;
}
