#include "clipsvalue_check_datatype.h"
#include <check_datatype.h>
#include <n3parser.h>


#define RETURNFAIL(failure) \
		Writeln(env, failure);\
		SetErrorValue(env, &(CreateString(env, failure)->header));\
		out->voidValue = VoidConstant(env);\
		return;

void rif_check_datatype(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = ((struct context_check_datatype *) udfc->context)->invert;
	DatatypeInfo *datatype_info\
		= ((struct context_check_datatype *) udfc->context)->datatype;
	char *datatype, *lexical;
	bool truth;
	UDFValue udfval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is_literal_string.");
	}
	if (udfval.header->type == STRING_TYPE){
		datatype = extract_datatype(env, udfval.lexemeValue);
		if (datatype == NULL){
			RETURNFAIL("is-literal-string: "
					"couldnt extract datatype");
		}
		lexical = extract_lexical(env, udfval.lexemeValue);
		if (lexical ==NULL){
			free(datatype);
			RETURNFAIL("");
		}
		truth = check_is_datatype(lexical, datatype, datatype_info);
		free(datatype);
		free(lexical);
	} else {
		RETURNFAIL("rif_check_datatype cant work with not lexical literals");
	}
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}

#undef RETURNFAIL


ContextCheckDatatype ContextCheck_XS_string = {false, &info_xs_string};
ContextCheckDatatype ContextCheck_XS_normalizedString = {false, &info_xs_normalizedString};
ContextCheckDatatype ContextCheck_XS_token = {false, &info_xs_token};
ContextCheckDatatype ContextCheck_XS_language = {false, &info_xs_language};
ContextCheckDatatype ContextCheck_XS_Name = {false, &info_xs_Name};
ContextCheckDatatype ContextCheck_XS_NCName = {false, &info_xs_NCName};
ContextCheckDatatype ContextCheck_XS_NMTOKEN = {false, &info_xs_NMTOKEN};

ContextCheckDatatype ContextCheck_not_XS_string = {true, &info_xs_string};
ContextCheckDatatype ContextCheck_not_XS_normalizedString = {true, &info_xs_normalizedString};
ContextCheckDatatype ContextCheck_not_XS_token = {true, &info_xs_token};
ContextCheckDatatype ContextCheck_not_XS_language = {true, &info_xs_language};
ContextCheckDatatype ContextCheck_not_XS_Name = {true, &info_xs_Name};
ContextCheckDatatype ContextCheck_not_XS_NCName = {true, &info_xs_NCName};
ContextCheckDatatype ContextCheck_not_XS_NMTOKEN = {true, &info_xs_NMTOKEN};
