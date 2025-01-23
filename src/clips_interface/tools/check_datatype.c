#include "check_datatype.h"
#include <stddef.h>
#include "ffi_constants.h"
#include <stdio.h>
#include <regex.h>
#include <string.h>

DatatypeInfo info_xs_string = {
	_XS_string_,
	"",
	NULL,
	{&info_xs_normalizedString, &info_rdf_PlainLiteral, NULL, NULL, NULL}
};

DatatypeInfo info_xs_normalizedString = {
	_XS_normalizedString_,
	"",
	&info_xs_string,
	{&info_xs_token, NULL, NULL, NULL, NULL}
};

DatatypeInfo info_xs_token = {
	_XS_token_,
	"",
	&info_xs_normalizedString,
	{&info_xs_language, &info_xs_Name, &info_xs_NMTOKEN, NULL, NULL}
};

DatatypeInfo info_xs_language = {
	_XS_language_,
	"",
	&info_xs_token,
	{NULL, NULL, NULL, NULL, NULL}
};

DatatypeInfo info_xs_Name = {
	_XS_Name_,
	"",
	&info_xs_token,
	{&info_xs_NCName, NULL, NULL, NULL, NULL}
};

DatatypeInfo info_xs_NCName = {
	_XS_NCName_,
	"",
	&info_xs_Name,
	{NULL, NULL, NULL, NULL, NULL}
};

DatatypeInfo info_xs_NMTOKEN = {
	_XS_NMTOKEN_,
	"",
	&info_xs_token,
	{NULL, NULL, NULL, NULL, NULL}
};

DatatypeInfo info_rdf_PlainLiteral = {
	_RDF_PlainLiteral_,
	"",
	NULL,
	{NULL, NULL, NULL, NULL, NULL}
};

static bool check_regex(const char* lexical, DatatypeInfo *target_datatype){
	//regmatch_t matches[5];
	int err;
	regex_t reg;
	err = regcomp(&reg, target_datatype->regex, 0);
	if (0 != err){
		//fprintf(stderr, "internal regex for datatypes seems broken:"
		//		"\n%s\n", target_datatype->regex);
		return false;
	};
	err = regexec(&reg, lexical, 0, NULL, 0);
	regfree(&reg);
	if (err == 0){
		return true;
	}
	/* dont need to check regex of subtypes
	for (int i=0; (i<5) && (target_datatype[i] != NULL); i++){
		if(check_regex(lexical, target_datatype[i])){
			return true;
		}
	}
	*/
	return false;
}

bool check_is_datatype(const char* lexical, const char *datatype, DatatypeInfo *target_datatype){
	bool success = false;
	for (DatatypeInfo *info = target_datatype; info != NULL; info = info->super){
		if(0 == strcmp(datatype, info->uri)){
			success = true;
			break;
		}
	}
	if (!success){
		return false;
	}
	if (!check_regex(lexical, target_datatype)){
		return false;
	}
	return true;
}
