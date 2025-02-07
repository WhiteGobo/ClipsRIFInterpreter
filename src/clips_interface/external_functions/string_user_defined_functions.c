#include <clips.h>
#include "string_user_defined_functions.h"
#include "info_query.h"
#include <crifi_numeric.h>
#include <ctype.h>
#include <uriencode.h>
#include <xpath_replace.h>

#define RETURNFAIL(failure) \
		Writeln(env, failure);\
		SetErrorValue(env, &(CreateString(env, failure)->header));\
		out->voidValue = VoidConstant(env);\
		return;

void rif_is_literal_string(Environment *env, UDFContext *udfc, UDFValue *out){
	char *datatype;
	bool invert = *(bool*) udfc->context;
	bool truth;
	UDFValue udfval;
	CLIPSValue valcpy;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is_literal_string.");
	}
	if (udfval.header->type == STRING_TYPE){
		datatype = extract_datatype(env, udfval.header);
		if (datatype == NULL){
			RETURNFAIL("is-literal-string: "
					"couldnt extract datatype");
		}

		//According to w3c testfiles this should be the way:
		truth = (0 == strcmp(datatype, _RDF_PlainLiteral_))
			|| (0 == strcmp(datatype, _RDF_string_))
			|| (0 == strcmp(datatype, _RDF_langString_));
		free(datatype);
	} else {
		truth = false;
	}
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}

void rif_is_literal_normalizedString(Environment *env, UDFContext *udfc, UDFValue *out){
	char *datatype;
	bool invert = *(bool*) udfc->context;
	bool truth;
	UDFValue udfval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is_literal_normalizedString.");
	}
	if (udfval.header->type == STRING_TYPE){
		datatype = extract_datatype(env, udfval.header);
		if (datatype == NULL){
			RETURNFAIL("is-literal-normalizedString: "
					"couldnt extract datatype");
		}

		//According to w3c testfiles this should be the way:
		truth = (0 == strcmp(datatype, _XS_normalizedString_));
		free(datatype);
	} else {
		truth = false;
	}
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}

void rif_is_literal_token(Environment *env, UDFContext *udfc, UDFValue *out){
	char *datatype;
	bool invert = *(bool*) udfc->context;
	bool truth;
	UDFValue udfval;
	CLIPSValue valcpy;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is_literal_token.");
	}
	if (udfval.header->type == STRING_TYPE){
		datatype = extract_datatype(env, udfval.header);
		if (datatype == NULL){
			RETURNFAIL("is-literal-token: "
					"couldnt extract datatype");
		}

		//According to w3c testfiles this should be the way:
		truth = (0 == strcmp(datatype, _XS_token_));
		free(datatype);
	} else {
		truth = false;
	}
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}

void rif_is_literal_language(Environment *env, UDFContext *udfc, UDFValue *out){
	char *datatype;
	bool invert = *(bool*) udfc->context;
	bool truth;
	UDFValue udfval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is_literal_language.");
	}
	if (udfval.header->type == STRING_TYPE){
		datatype = extract_datatype(env, udfval.header);
		if (datatype == NULL){
			RETURNFAIL("is-literal-language: "
					"couldnt extract datatype");
		}

		//According to w3c testfiles this should be the way:
		truth = (0 == strcmp(datatype, _XS_language_));
		free(datatype);
	} else {
		truth = false;
	}
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}

void rif_is_literal_Name(Environment *env, UDFContext *udfc, UDFValue *out){
	char *datatype;
	bool invert = *(bool*) udfc->context;
	bool truth;
	UDFValue udfval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is_literal_Name.");
	}
	if (udfval.header->type == STRING_TYPE){
		datatype = extract_datatype(env, udfval.header);
		if (datatype == NULL){
			RETURNFAIL("is-literal-Name: "
					"couldnt extract datatype");
		}

		//According to w3c testfiles this should be the way:
		truth = (0 == strcmp(datatype, _XS_Name_));
		free(datatype);
	} else {
		truth = false;
	}
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}

void rif_is_literal_NCName(Environment *env, UDFContext *udfc, UDFValue *out){
	char *datatype;
	bool invert = *(bool*) udfc->context;
	bool truth;
	UDFValue udfval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is_literal_NCName.");
	}
	if (udfval.header->type == STRING_TYPE){
		datatype = extract_datatype(env, udfval.header);
		if (datatype == NULL){
			RETURNFAIL("is-literal-NCName: "
					"couldnt extract datatype");
		}

		//According to w3c testfiles this should be the way:
		truth = (0 == strcmp(datatype, _XS_NCName_));
		free(datatype);
	} else {
		truth = false;
	}
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}

void rif_is_literal_NMTOKEN(Environment *env, UDFContext *udfc, UDFValue *out){
	char *datatype;
	bool invert = *(bool*) udfc->context;
	bool truth;
	UDFValue udfval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is_literal_NCName.");
	}
	if (udfval.header->type == STRING_TYPE){
		datatype = extract_datatype(env, udfval.header);
		if (datatype == NULL){
			RETURNFAIL("is-literal-NCName: "
					"couldnt extract datatype");
		}

		//According to w3c testfiles this should be the way:
		truth = (0 == strcmp(datatype, _XS_NMTOKEN_));
		free(datatype);
	} else {
		truth = false;
	}
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}

void rif_iri_string(Environment *env, UDFContext *udfc, UDFValue *out){
	const char *iristring;
	char *lexical;
	bool truth;
	int uri_length;
	UDFValue udfiri, udfstring;
	if (!UDFFirstArgument(udfc, SYMBOL_BIT, &udfiri)){
		RETURNFAIL("Argument error for rif_iri_string.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfstring)){
		RETURNFAIL("Argument error for rif_iri_string.");
	}
	if (udfstring.header->type == STRING_TYPE
			&& udfiri.header->type == SYMBOL_TYPE){
		lexical = extract_lexical(env, udfstring.header);
		iristring = udfiri.lexemeValue->contents;
		uri_length = strlen(iristring) - 2;
		//According to w3c testfiles this should be the way:
		truth = (strlen(lexical) == uri_length)
			&& (0 == memcmp(lexical, iristring+1, uri_length));
		free(lexical);
	} else {
		truth = false;
	}
	out->lexemeValue = CreateBoolean(env, truth);
}

void rif_concat(Environment *env, UDFContext *udfc, UDFValue *out){
	int err;
	unsigned int l = UDFArgumentCount(udfc);
	size_t result_string_length = 1;
	UDFValue tmpval;
	CLIPSValue myval[l+1];
	CLIPSValue outclipsval;
	char *lexicals[l+1];
	char *result, *endptr;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpval)){
		RETURNFAIL("rif_concat");
	}
	myval[0].value = tmpval.value;
	for (int i=1; i<l; i++){
		if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpval)){
			RETURNFAIL("rif_concat");
		}
		myval[i].value = tmpval.value;
	}
	for (int i=0; i<l; i++){
		lexicals[i] = extract_lexical(env, myval[i].header);
		result_string_length += strlen(lexicals[i]) + sizeof(" ");
	}
	result = malloc(result_string_length);
	endptr = result;
	for (int i=0; i<l; i++){
		if (lexicals[i] != NULL){
			endptr += sprintf(endptr, "%s", lexicals[i]);
			free(lexicals[i]);
		}
	}
	err = value_and_datatype_to_clipsvalue(env,
			result, strlen(result), NULL, 0, &outclipsval);
	free(result);
	if (err==0){
		out->value = outclipsval.value;
	}
}

/**
 * TODO: Missing implementation for specified separator.
 */
void rif_string_join(Environment *env, UDFContext *udfc, UDFValue *out){
	int err, delimiter_size;
	unsigned int l = UDFArgumentCount(udfc);
	size_t result_string_length = 1;
	UDFValue tmpval;
	CLIPSValue myval[l+1], delimiterval;
	CLIPSValue outclipsval;
	char *lexicals[l+1];
	char *delimiter;
	char *result, *endptr;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpval)){
		RETURNFAIL("rif_concat");
	}
	myval[0].value = tmpval.value;
	for (int i=1; i<l-1; i++){
		if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpval)){
			RETURNFAIL("rif_concat");
		}
		myval[i].value = tmpval.value;
	}
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpval)){
		RETURNFAIL("rif_concat");
	}
	delimiter = extract_lexical(env, tmpval.header);
	delimiter_size = strlen(delimiter);
	for (int i=0; i<l-1; i++){
		lexicals[i] = extract_lexical(env, myval[i].header);
		result_string_length += strlen(lexicals[i]) + delimiter_size;
	}
	result = malloc(result_string_length);
	endptr = result;
	endptr += sprintf(endptr, "%s", lexicals[0]);
	free(lexicals[0]);
	for (int i=1; i<l-1; i++){
		if (lexicals[i] != NULL){
			endptr += sprintf(endptr, "%s%s", delimiter, lexicals[i]);
			free(lexicals[i]);
		}
	}
	err = value_and_datatype_to_clipsvalue(env,
			result, strlen(result), NULL, 0, &outclipsval);
	free(result);
	if (err==0){
		out->value = outclipsval.value;
	}
	free(delimiter);
}

void rif_substring(Environment *env, UDFContext *udfc, UDFValue *out){
	unsigned int l = UDFArgumentCount(udfc);
	size_t result_string_length, source_length;
	UDFValue udfSourceString, udfStartingLoc, udfLength;
	CLIPSValue myval, tmpval;
	long long start, length;
	char *lexical;
	char *result;
	int err;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfSourceString)){
		RETURNFAIL("rif_substring");
	}
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &udfStartingLoc)){
		RETURNFAIL("rif_substring");
	}
	tmpval.value = udfSourceString.value;
	lexical = extract_lexical(env, udfSourceString.header);
	if (lexical == NULL){
		RETURNFAIL("rif:substring - Cant extract string from input 1");
	}
	source_length = strlen(lexical);

	tmpval.value = udfStartingLoc.value;
	if(!clipsvalue_as_integer(env, tmpval, &start)){
		free(lexical);
		RETURNFAIL("rif_substring position 2 isnt an integer");
	}

	if (l == 3){
		if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &udfLength)){
			free(lexical);
			RETURNFAIL("rif_substring");
		}
		tmpval.value = udfLength.value;
		if(!clipsvalue_as_integer(env, tmpval, &length)){
			free(lexical);
			RETURNFAIL("rif_substring position 3 isnt an integer");
		}
	} else {
		length = strlen(lexical+start-1);
	}
	if (start < 1){
		length -= 1 - start;
		start = 0;
	} else {
		start -= 1; //xpath string starts with 1
	}
	if (length > source_length - start){
		length = source_length - start;
	} else if (length < 0){
		length = 0;
	}
	err = value_and_datatype_to_clipsvalue(env,
			lexical+start, length, NULL, 0, &tmpval);
	free(lexical);
	if (err==0){
		out->value = tmpval.value;
	} else {
		RETURNFAIL("rif_substring couldnt create new string");
	}
}

void rif_string_length(Environment *env, UDFContext *udfc, UDFValue *out){
	size_t result_string_length, source_length;
	UDFValue udfSourceString, udfStartingLoc, udfLength;
	CLIPSValue myval, tmpval;
	long long start, length;
	char *lexical;
	char *result;
	int err;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfSourceString)){
		RETURNFAIL("rif_substring");
	}
	lexical = extract_lexical(env, udfSourceString.header);
	if (lexical == NULL){
		RETURNFAIL("rif:substring - Cant extract string from input 1");
	}
	source_length = strlen(lexical);
	free(lexical);
	tmpval = crifi_create_integer(env, source_length);
	out->value = tmpval.value;
}

void rif_upper_case(Environment *env, UDFContext *udfc, UDFValue *out){
	size_t result_string_length, source_length;
	UDFValue udfSourceString, udfStartingLoc, udfLength;
	CLIPSValue myval, tmpval;
	long long start, length;
	char *lexical;
	char *result;
	int err;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfSourceString)){
		RETURNFAIL("rif_substring");
	}
	lexical = extract_lexical(env, udfSourceString.header);
	if (lexical == NULL){
		RETURNFAIL("rif:substring - Cant extract string from input 1");
	}
	source_length = strlen(lexical);
	result = malloc(source_length + 1);
	for (int i=0; i<source_length; i++){
		result[i] = toupper(lexical[i]);
	}
	result[source_length] = '\0';
	err = value_and_datatype_to_clipsvalue(env,
			result, source_length, NULL, 0, &tmpval);
	free(lexical);
	free(result);
	if (err==0){
		out->value = tmpval.value;
	}
}


void rif_lower_case(Environment *env, UDFContext *udfc, UDFValue *out){
	size_t result_string_length, source_length;
	UDFValue udfSourceString, udfStartingLoc, udfLength;
	CLIPSValue myval, tmpval;
	long long start, length;
	char *lexical;
	char *result;
	int err;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfSourceString)){
		RETURNFAIL("rif_substring");
	}
	lexical = extract_lexical(env, udfSourceString.header);
	if (lexical == NULL){
		RETURNFAIL("rif:substring - Cant extract string from input 1");
	}
	source_length = strlen(lexical);
	result = malloc(source_length + 1);
	for (int i=0; i<source_length; i++){
		result[i] = tolower(lexical[i]);
	}
	result[source_length] = '\0';
	err = value_and_datatype_to_clipsvalue(env,
			result, source_length, NULL, 0, &tmpval);
	free(lexical);
	free(result);
	if (err==0){
		out->value = tmpval.value;
	}
}


void rif_encode_for_uri(Environment *env, UDFContext *udfc, UDFValue *out){
	size_t result_string_length, source_length;
	UDFValue udfSourceString, udfStartingLoc, udfLength;
	CLIPSValue myval, tmpval;
	long long start, length;
	char *lexical;
	char *result;
	int err;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfSourceString)){
		RETURNFAIL("rif:encode-for-uri");
	}
	lexical = extract_lexical(env, udfSourceString.header);
	if (lexical == NULL){
		RETURNFAIL("rif:encode-for-uri - "
				"Cant extract string from input 1");
	}
	source_length = strlen(lexical);
	result = malloc(3*source_length + 1);
	uri_encode(lexical, source_length, result);
	err = value_and_datatype_to_clipsvalue(env,
			result, strlen(result), NULL, 0, &tmpval);
	if (err==0){
		out->value = tmpval.value;
	}
	free(lexical);
	free(result);
}


void rif_iri_to_uri(Environment *env, UDFContext *udfc, UDFValue *out){
	size_t result_string_length, source_length;
	UDFValue udfSourceString, udfStartingLoc, udfLength;
	CLIPSValue myval, tmpval;
	long long start, length;
	char *lexical;
	char *result;
	int err;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfSourceString)){
		RETURNFAIL("rif:encode-for-uri");
	}
	lexical = extract_lexical(env, udfSourceString.header);
	if (lexical == NULL){
		RETURNFAIL("rif:encode-for-uri - "
				"Cant extract string from input 1");
	}
	source_length = strlen(lexical);
	result = malloc(3*source_length + 1);
	iri_to_uri(lexical, source_length, result);

	err = value_and_datatype_to_clipsvalue(env,
			result, strlen(result), NULL, 0, &tmpval);
	if (err==0){
		out->value = tmpval.value;
	}
	free(lexical);
	free(result);
}


void rif_escape_html_uri(Environment *env, UDFContext *udfc, UDFValue *out){
	size_t result_string_length, source_length;
	UDFValue udfSourceString, udfStartingLoc, udfLength;
	CLIPSValue myval, tmpval;
	long long start, length;
	char *lexical;
	char *result;
	int err;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfSourceString)){
		RETURNFAIL("rif:escape-html-uri");
	}
	lexical = extract_lexical(env, udfSourceString.header);
	if (lexical == NULL){
		RETURNFAIL("rif:escape-html-uri - "
				"Cant extract string from input 1");
	}
	source_length = strlen(lexical);
	result = malloc(3*source_length + 1);
	escape_html_uri(lexical, source_length, result);
	err = value_and_datatype_to_clipsvalue(env,
			result, strlen(result), NULL, 0, &tmpval);
	if (err==0){
		out->value = tmpval.value;
	}
	free(lexical);
	free(result);
}


void rif_substring_before(Environment *env, UDFContext *udfc, UDFValue *out){
	int err;
	UDFValue udfSource, udfSearch;
	CLIPSValue tmpval;
	int max_search, search_length;
	char *search;
	char *result;
	char *source;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfSource)){
		RETURNFAIL("rif:encode-for-uri");
	}
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &udfSearch)){
		RETURNFAIL("rif:encode-for-uri");
	}
	source = extract_lexical(env, udfSource.header);
	if (source == NULL){
		RETURNFAIL("rif:substring-before");
	}
	search = extract_lexical(env, udfSearch.header);
	if (search == NULL){
		RETURNFAIL("rif:substring-before");
	}
	search_length = strlen(search);
	max_search = strlen(source) - search_length + 1;
	for (int i=0; i < max_search; i++){
		if (0 == memcmp(source + i, search, search_length)){
			result = malloc(i + 1);
			memcpy(result, source, i);
			result[i] = '\0';
			err = value_and_datatype_to_clipsvalue(env,
					result, strlen(result), NULL, 0,
					&tmpval);
			if (err==0){out->value = tmpval.value;}
			free(result);
			break;
		}
	}
	free(source);
	free(search);
}


void rif_substring_after(Environment *env, UDFContext *udfc, UDFValue *out){
	int err;
	UDFValue udfSource, udfSearch;
	CLIPSValue tmpval;
	int max_search, search_length, source_length, length, delta;
	char *search;
	char *result;
	char *source;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfSource)){
		RETURNFAIL("rif:encode-for-uri");
	}
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &udfSearch)){
		RETURNFAIL("rif:encode-for-uri");
	}
	source = extract_lexical(env, udfSource.header);
	if (source == NULL){
		RETURNFAIL("rif:substring-after");
	}
	search = extract_lexical(env, udfSearch.header);
	if (search == NULL){
		RETURNFAIL("rif:substring-after");
	}
	source_length = strlen(source);
	search_length = strlen(search);
	max_search = source_length - search_length + 1;
	for (int i=0; i < max_search; i++){
		if (0 == memcmp(source + i, search, search_length)){
			result = malloc(1 + source_length - i);
			strcpy(result, source + i + search_length);
			err = value_and_datatype_to_clipsvalue(env,
					result, strlen(result), NULL, 0,
					&tmpval);
			if (err==0){out->value = tmpval.value;}
			free(result);
			break;
		}
	}
	free(source);
	free(search);
}


void rif_replace(Environment *env, UDFContext *udfc, UDFValue *out){
	unsigned int l = UDFArgumentCount(udfc);
	char *src, *pattern, *replacement, *flags, *outString;
	CLIPSValue tmpval;
	int err;
	UDFValue udfInput, udfPattern, udfReplacement, udfFlags;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfInput)){
		RETURNFAIL("rif_replace");
	}
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &udfPattern)){
		RETURNFAIL("rif_replace");
	}
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &udfReplacement)){
		RETURNFAIL("rif_replace");
	}
	if (l >= 4){
		if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &udfFlags)){
			RETURNFAIL("rif_replace");
		}
		flags = extract_lexical(env, udfFlags.header);
	} else {
		flags = NULL;
	}
	src = extract_lexical(env, udfInput.header);
	pattern = extract_lexical(env, udfPattern.header);
	replacement = extract_lexical(env, udfReplacement.header);

	outString = xpath_replace(src, pattern, replacement, flags);
	if (flags != NULL) free(flags);
	free(src);
	free(pattern);
	free(replacement);
	if(outString != NULL){
		err = value_and_datatype_to_clipsvalue(env,
				outString, strlen(outString), NULL, 0, &tmpval);
		if (err==0){
			out->value = tmpval.value;
		}
		free(outString);
	}
	if (outString == NULL || err != 0){
		RETURNFAIL("rif_replace didnt work");
	}
}


void rif_contains(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfSource, udfSearch;
	CLIPSValue tmpval;
	int max_search, search_length, source_length;
	char *search;
	char *result;
	char *source;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfSource)){
		RETURNFAIL("rif:encode-for-uri");
	}
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &udfSearch)){
		RETURNFAIL("rif:encode-for-uri");
	}
	source = extract_lexical(env, udfSource.header);
	if (source == NULL){
		RETURNFAIL("rif:substring-after");
	}
	search = extract_lexical(env, udfSearch.header);
	if (search == NULL){
		RETURNFAIL("rif:substring-after");
	}
	search_length = strlen(search);
	source_length = strlen(source);
	out->lexemeValue = CreateBoolean(env, false);
	for (int i=0; i <= source_length - search_length; i++){
		if (0 == memcmp(source + i, search, search_length)){
			out->lexemeValue = CreateBoolean(env, true);
			break;
		}
	}
	free(source);
	free(search);
}


void rif_starts_with(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfSource, udfSearch;
	CLIPSValue tmpval;
	int max_search, search_length, diff, source_length;
	char *search;
	char *result;
	char *source;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfSource)){
		RETURNFAIL("rif:encode-for-uri");
	}
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &udfSearch)){
		RETURNFAIL("rif:encode-for-uri");
	}
	source = extract_lexical(env, udfSource.header);
	if (source == NULL){
		RETURNFAIL("rif:substring-after");
	}
	search = extract_lexical(env, udfSource.header);
	if (search == NULL){
		RETURNFAIL("rif:substring-after");
	}
	search_length = strlen(search);
	source_length = strlen(source);
	if (search_length <= source_length){
		diff = memcmp(source, search, search_length);
		out->lexemeValue = CreateBoolean(env, diff == 0);
	} else {
		out->lexemeValue = CreateBoolean(env, false);
	}
	free(source);
	free(search);
}


void rif_ends_with(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfSource, udfSearch;
	CLIPSValue tmpval;
	int max_search, search_length, diff, source_length;
	char *search;
	char *result;
	char *source;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfSource)){
		RETURNFAIL("rif:encode-for-uri");
	}
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &udfSearch)){
		RETURNFAIL("rif:encode-for-uri");
	}
	source = extract_lexical(env, udfSource.header);
	if (source == NULL){
		RETURNFAIL("rif:substring-after");
	}
	search = extract_lexical(env, udfSource.header);
	if (search == NULL){
		RETURNFAIL("rif:substring-after");
	}
	search_length = strlen(search);
	source_length = strlen(source);
	if (search_length <= source_length){
		diff = memcmp(source + source_length - search_length,
					search, search_length);
		out->lexemeValue = CreateBoolean(env, diff == 0);
	} else {
		out->lexemeValue = CreateBoolean(env, false);
	}
	free(source);
	free(search);
}



void rif_matches(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfSource, udfSearch;
	CLIPSValue tmpval;
	int max_search, search_length, diff;
	char *search;
	char *result;
	char *source;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfSource)){
		RETURNFAIL("rif:encode-for-uri");
	}
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &udfSearch)){
		RETURNFAIL("rif:encode-for-uri");
	}
	source = extract_lexical(env, udfSource.header);
	if (source == NULL){
		RETURNFAIL("rif:substring-after");
	}
	search = extract_lexical(env, udfSource.header);
	if (search == NULL){
		RETURNFAIL("rif:substring-after");
	}
	diff = strcmp(source, search);
	out->lexemeValue = CreateBoolean(env, diff == 0);
	free(source);
	free(search);
}


/**
 * TODO: implementation of codepoint collation is missing.
 * 	see `https://www.w3.org/TR/2013/REC-rif-dtb-20130205/#func:compare_.28adapted_from_fn:compare.29`_
 */
void rif_compare(Environment *env, UDFContext *udfc, UDFValue *out){
	unsigned int l = UDFArgumentCount(udfc);
	if (l == 3){
		RETURNFAIL("rif:compare cant handle codepoint collation");
	}
	UDFValue udfSource, udfSearch;
	CLIPSValue tmpval;
	int max_search, search_length, diff;
	char *search;
	char *result;
	char *source;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfSource)){
		RETURNFAIL("rif:encode-for-uri");
	}
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &udfSearch)){
		RETURNFAIL("rif:encode-for-uri");
	}
	source = extract_lexical(env, udfSource.header);
	if (source == NULL){
		RETURNFAIL("rif:substring-after");
	}
	search = extract_lexical(env, udfSearch.header);
	if (search == NULL){
		RETURNFAIL("rif:substring-after");
	}
	diff = strcmp(source, search);
	if (diff < 0){
		diff = -1;
	} else if (diff > 0){
		diff = 1;
	}
	tmpval = crifi_create_integer(env, diff);
	out->value = tmpval.value;
	free(source);
	free(search);
}

#undef RETURNFAIL(failure)
