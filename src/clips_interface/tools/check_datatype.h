#pragma once

/**
 * See for inheritance of datatypes: `https://www.w3.org/TR/2013/REC-rif-dtb-20130205/#Datatypes`_
 */

#include <stdbool.h>

typedef struct datatypeInfo {
	const char *uri;
	const char *regex;
	struct datatypeInfo *super;
	struct datatypeInfo *sub[5];
} DatatypeInfo ;

extern DatatypeInfo info_xs_string;
extern DatatypeInfo info_xs_normalizedString;
extern DatatypeInfo info_xs_token;
extern DatatypeInfo info_xs_language;
extern DatatypeInfo info_xs_Name;
extern DatatypeInfo info_xs_NCName;
extern DatatypeInfo info_xs_NMTOKEN;
extern DatatypeInfo info_rdf_PlainLiteral;

bool check_is_datatype(const char* lexical, const char *datatype, DatatypeInfo *target_datatype);
