#include "xmlliteral_user_defined_functions.h"
#include "info_query.h"
#include "ffi_constants.h"

static void my_set_error(Environment *env, const char* failure){
	SetErrorValue(env, &(CreateString(env, failure)->header));
}

void rif_is_literal_XMLLiteral(Environment *env, UDFContext *udfc, UDFValue *out){
	bool truth;
	bool invert = *(bool*) udfc->context;
	char *datatype;
	out->voidValue = VoidConstant(env);
	UDFValue udfval;
	CLIPSValue clipsval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		my_set_error(env, "Argument error for is-literal-XMLLiteral.");
		return;
	}

	datatype = extract_datatype(env, udfval.header);
	clipsval.value = udfval.value;
	truth = (0 == strcmp(datatype, _RDF_XMLLiteral_));
	free(datatype);
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}

void rif_is_literal_anyURI(Environment *env, UDFContext *udfc, UDFValue *out){
	bool truth;
	bool invert = *(bool*) udfc->context;
	char *datatype;
	out->voidValue = VoidConstant(env);
	UDFValue udfval;
	CLIPSValue clipsval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		my_set_error(env, "Argument error for is-literal-anyURI.");
		return;
	}

	datatype = extract_datatype(env, udfval.header);
	clipsval.value = udfval.value;
	truth = (0 == strcmp(datatype, _XS_anyURI_));
	free(datatype);
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}
