#pragma once

#include <clips.h>
#include <check_datatype.h>

typedef struct context_check_datatype {
	bool invert;
	DatatypeInfo *datatype;
} ContextCheckDatatype;

void rif_check_datatype(Environment *env, UDFContext *udfc, UDFValue *out);

extern ContextCheckDatatype ContextCheck_XS_string;
extern ContextCheckDatatype ContextCheck_XS_normalizedString;
extern ContextCheckDatatype ContextCheck_XS_token;
extern ContextCheckDatatype ContextCheck_XS_language;
extern ContextCheckDatatype ContextCheck_XS_Name;
extern ContextCheckDatatype ContextCheck_XS_NCName;
extern ContextCheckDatatype ContextCheck_XS_NMTOKEN;

extern ContextCheckDatatype ContextCheck_not_XS_string;
extern ContextCheckDatatype ContextCheck_not_XS_normalizedString;
extern ContextCheckDatatype ContextCheck_not_XS_token;
extern ContextCheckDatatype ContextCheck_not_XS_language;
extern ContextCheckDatatype ContextCheck_not_XS_Name;
extern ContextCheckDatatype ContextCheck_not_XS_NCName;
extern ContextCheckDatatype ContextCheck_not_XS_NMTOKEN;
