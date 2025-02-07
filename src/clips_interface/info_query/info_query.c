#include "info_query.h"
#include <n3parser.h>

Fact *get_next_triple(Environment *env, Fact *f){
	Deftemplate *tripletemplate = FindDeftemplate(env, TRIPLETEMPLATE);
	return GetNextFactInTemplate(tripletemplate, f);
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
	}
	return false;
}

bool clipsvalue_is_bnode(Environment *env, CLIPSValue val){
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
				return true;
			} else {
				return false;
			}
			break;
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
	char *ret;
	size_t orig_l = strlen(val.lexemeValue->contents);
	ret = malloc(orig_l - 1);
	memcpy(ret, val.lexemeValue->contents +1, orig_l-2);
	ret[orig_l-2] = '\0';
	return ret;
}

char *extract_bnodeid(Environment *env, TypeHeader *head){
	CLIPSValue val = {.header=head};
	char *ret;
	ret = malloc(strlen(val.lexemeValue->contents) - 1);
	strcpy(ret, val.lexemeValue->contents + 2);
	return ret;
}

char *extract_lexical(Environment *env, TypeHeader *head){
	CLIPSValue val = {.header = head};
	return lexeme_extract_lexical(env, val.lexemeValue);
}
char *extract_datatype(Environment *env, TypeHeader *head){
	CLIPSValue val = {.header = head};
	return lexeme_extract_datatype(env, val.lexemeValue);
}
char *extract_lang(Environment *env, TypeHeader *head){
	CLIPSValue val = {.header = head};
	return lexeme_extract_lang(env, val.lexemeValue);
}
