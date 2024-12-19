#include <clips.h>
#include "plainliteral_user_defined_functions.h"
#include <n3parser.h>


#define RETURNFAIL(failure) \
		Writeln(env, failure);\
		SetErrorValue(env, &(CreateString(env, failure)->header));\
		out->voidValue = VoidConstant(env);\
		return;

void rif_PlainLiteral_from_string_lang(Environment *env, UDFContext *udfc, UDFValue *out){
	char *value, *lang, *retval;
	size_t value_length, lang_length;
	UDFValue udfval, udflang;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for plainliteral from string lang.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udflang)){
		RETURNFAIL("Argument error for plainliteral from string lang.");
	}

	value = extract_lexical(env, udfval.lexemeValue);
	if (value == NULL){
		RETURNFAIL("Invalid String as Argument. "
				"error for plainliteral from string lang.");
	}
	lang = extract_lexical(env, udflang.lexemeValue);
	if (lang == NULL){
		RETURNFAIL("Invalid String as Argument. "
				"error for plainliteral from string lang.");
	}
	value_length = strlen(value);
	lang_length = strlen(lang);
	retval = malloc((3*value_length)+ lang_length + 3);
	value_and_lang_to_slotstring(retval, value, value_length,
			lang, lang_length);
	out->lexemeValue = CreateString(env, retval);
	free(retval);
}

void rif_string_from_PlainLiteral(Environment *env, UDFContext *udfc, UDFValue *out){
	char *datatype, *lexical, *pos, *retval, *value;
	size_t value_length;
	bool truth;
	UDFValue udfval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is_literal_PlainLiteral.");
	}
	if (udfval.header->type != STRING_TYPE){
		RETURNFAIL("is_literal_plainliteral expected lexeme.");
	}
	datatype = extract_datatype(env, udfval.lexemeValue);
	if (datatype == NULL){
		RETURNFAIL("is-literal-Plainliteral: couldnt extract datatype");
	}

	if(0 == strcmp(datatype, _RDF_PlainLiteral_)){
		lexical = extract_lexical(env, udfval.lexemeValue);
		pos = strstr(lexical, "@");
		*pos = '\0'; //cut of lang tail

		value_length = strlen(lexical);
		retval = malloc(3*value_length + 1);
		value_and_datatype_to_slotstring(retval, lexical, value_length,
				NULL, 0);
		out->value = CreateString(env, lexical);
		free(retval);
		free(lexical);
	} else if (0 == strcmp(datatype, _RDF_string_)) {
		lexical = extract_lexical(env, udfval.lexemeValue);
		value_length = strlen(lexical);
		retval = malloc(3*value_length + 1);
		value_and_datatype_to_slotstring(retval, lexical, value_length,
				NULL, 0);
		out->value = CreateString(env, retval);
		free(retval);
		free(lexical);
	} else if (0 == strcmp(datatype, _RDF_langString_)){
		value = extract_lexical(env, udfval.lexemeValue);
		value_length = strlen(value);
		retval = malloc(3*value_length + 1);
		value_and_datatype_to_slotstring(retval, value, value_length,
				NULL, 0);

		out->value = CreateString(env, retval);
		free(retval);
		free(value);
	} else {
		free(datatype);
		RETURNFAIL("Argument Error for plainliteral. Missing guard.");
	}
	free(datatype);
}

void rif_lang_from_PlainLiteral(Environment *env, UDFContext *udfc, UDFValue *out){
	char *datatype, *lexical, *pos, *retval, *value, *tmp;
	size_t value_length;
	char lang[10];
	bool truth;
	UDFValue udfval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is_literal_PlainLiteral.");
	}
	if (udfval.header->type != STRING_TYPE){
		RETURNFAIL("is_literal_plainliteral expected lexeme.");
	}
	datatype = extract_datatype(env, udfval.lexemeValue);
	if (datatype == NULL){
		RETURNFAIL("is-literal-Plainliteral: couldnt extract datatype");
	}

	if(0 == strcmp(datatype, _RDF_PlainLiteral_)){
		lexical = extract_lexical(env, udfval.lexemeValue);
		pos = strstr(lexical, "@");
		pos += 1;
		strcpy(lang, pos);
		free(lexical);
	} else if (0 == strcmp(datatype, _RDF_string_)) {
		lang[0] = '\0';
	} else if (0 == strcmp(datatype, _RDF_langString_)){
		tmp = extract_lang(env, udfval.lexemeValue);
		if (tmp == NULL){
			free(datatype);
			RETURNFAIL("is-literal-PlainLiteral: argument error.");
		}
		strcpy(lang, tmp);
		free(tmp);
	} else {
		free(datatype);
		RETURNFAIL("Argument Error for plainliteral. Missing guard.");
	}
	free(datatype);

	if (lang[0] != '\0'){
		retval = malloc(3*strlen(lang) + sizeof(_XS_lang_ "^^"));
		value_and_datatype_to_slotstring(retval, lang, strlen(lang),
						_XS_lang_, sizeof(_XS_lang_));
		out->lexemeValue = CreateString(env, retval);
		free(retval);
	} else {
		out->lexemeValue = CreateString(env, "");
	}
}

void rif_cast_as_PlainLiteral(Environment *env, UDFContext *udfc, UDFValue *out){
	char *lexical, *tmplang, *retval, *datatype;
	size_t value_length, lang_length;
	UDFValue udfval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for cast as plainliteral.");
	}
	if (udfval.header->type != STRING_TYPE){
		RETURNFAIL("cast as plainliteral expected lexeme.");
	}
	datatype = extract_datatype(env, udfval.lexemeValue);
	if (datatype == NULL){
		RETURNFAIL("cast as plainliteral: couldnt extract datatype");
	}
	if ((0 == strcmp(datatype, _RDF_string_))
			|| (0 == strcmp(datatype, _RDF_langString_)))
	{
		out->value = udfval.value;
		return;
	}

	lexical = extract_lexical(env, udfval.lexemeValue);
	tmplang = strstr(lexical, "@");
	if (tmplang != NULL){
		value_length = tmplang - lexical;
		tmplang += 1;
		lang_length = strlen(tmplang);
		retval = malloc(3*strlen(lexical)+3);
		value_and_lang_to_slotstring(retval, lexical, value_length,
				tmplang, lang_length);
		out->lexemeValue = CreateString(env, retval);
		free(retval);
	} else {
		value_length = strlen(lexical);
		retval = malloc(3*strlen(lexical)+1);
		percent_encode(retval, lexical, value_length);
		out->lexemeValue = CreateString(env, retval);
		free(retval);
	}
}

void rif_is_literal_PlainLiteral(Environment *env, UDFContext *udfc, UDFValue *out){
	char *datatype;
	bool invert = *(bool*) udfc->context;
	bool truth;
	UDFValue udfval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is_literal_PlainLiteral.");
	}
	if (udfval.header->type != STRING_TYPE){
		RETURNFAIL("is_literal_plainliteral expected lexeme.");
	}
	datatype = extract_datatype(env, udfval.lexemeValue);
	if (datatype == NULL){
		RETURNFAIL("is-literal-Plainliteral: couldnt extract datatype");
	}

	//According to w3c testfiles this should be the way:
	truth = (0 == strcmp(datatype, _RDF_PlainLiteral_))
		|| (0 == strcmp(datatype, _RDF_string_))
		|| (0 == strcmp(datatype, _RDF_langString_));
	free(datatype);
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}


void rif_PlainLiteral_compare(Environment *env, UDFContext *udfc, UDFValue *out){
	char *datatype, *lexical, *pos, *retval, *value;
	char lang[10];
	size_t value_length;
	int diff_cmp;
	bool truth;
	UDFValue udfval1, udfval2;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval1)){
		RETURNFAIL("plainliteral_compare: Argument error.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfval2)){
		RETURNFAIL("plainliteral_compare: Argument error.");
	}
	diff_cmp = strcmp(udfval1.lexemeValue->contents,
			udfval2.lexemeValue->contents);
	if (diff_cmp < 0){
		diff_cmp = -1;
	} else if (diff_cmp > 0) {
		diff_cmp = 1;
	}
	char tmp[13 + sizeof(_XS_integer_)];
	sprintf(tmp, "%d^^" _XS_integer_, diff_cmp);
	out->lexemeValue = CreateString(env, tmp);
}


void rif_matches_language_range(Environment *env, UDFContext *udfc, UDFValue *out){
	char *datatype, *lexical, *pos, *retval, *value;
	char lang[10];
	size_t value_length;
	int diff_pos;
	bool truth;
	UDFValue udfval, udflangrange;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("matches-language-range: Argument error.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udflangrange)){
		RETURNFAIL("matches-language-range: Argument error.");
	}
	datatype = extract_datatype(env, udfval.lexemeValue);
	if (datatype == NULL){
		RETURNFAIL("is-literal-Plainliteral: couldnt extract datatype");
	}

	if(0 == strcmp(datatype, _RDF_PlainLiteral_)){
		lexical = extract_lexical(env, udfval.lexemeValue);
		pos = strstr(lexical, "@");
		if (pos != NULL){
			pos += 1;
			strcpy(lang,pos);
		} else {
			lang[0] = '\0';
		}
		free(lexical);
	} else if (0 == strcmp(datatype, _RDF_string_)) {
		lang[0] = '\0';
	} else if (0 == strcmp(datatype, _RDF_langString_)){
		retval = extract_lang(env, udfval.lexemeValue);
		if (retval == NULL){
			free(datatype);
			RETURNFAIL("matches-language-range: "
					"couldnt extract lang.");
		}
		strcpy(lang,retval);
		free(retval);
	} else {
		free(datatype);
		RETURNFAIL("matches-language-range: Missing Guard.");
	}
	free(datatype);

	lexical = extract_lexical(env, udflangrange.lexemeValue);
	size_t i = 0;
	while (
			lang[i] != '\0'
			&& (lexical[i] != '\0')
			&& (lexical[i] != '*')
			&& (lang[i] == lexical[i]))
	{
		i++;
	}
	truth = (lexical[i] == '*') || (lang[i] == lexical[i]);
	out->value = CreateBoolean(env, truth);
}

#undef RETURNFAIL
