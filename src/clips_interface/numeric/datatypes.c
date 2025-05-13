#include <stddef.h>
#include "ffi_constants.h"
#include <regex.h>


bool is_string_datatype(char *x, size_t xl){
	if (ISURI(x, xl, _XS_string_)) return true;
	//if (ISURI(x, xl, _RDF_string_)) return true;
	if (ISURI(x, xl, _XS_untypedAtomic_)) return true;
	return false;
}

static bool reg_int(char *lexical){
	int err;
	regex_t reg;
	err = regcomp(&reg, "^[-+]?[0-9]+$", REG_EXTENDED | REG_NOSUB);
	if (err == 0){
		err = regexec(&reg, lexical, 0, NULL, 0);
	}
	regfree(&reg);
	return err == 0;
}

static bool reg_hexadecimal(char *lexical){
	int err;
	regex_t reg;
	err = regcomp(&reg, "^[-+]?[0-9aAbBcCdDeEfF]+$",
			REG_EXTENDED | REG_NOSUB);
	if (err == 0){
		err = regexec(&reg, lexical, 0, NULL, 0);
	}
	regfree(&reg);
	return err == 0;
}

static bool reg_double(char *lexical){
	int err;
	regex_t reg;
	err = regcomp(&reg, "^[-+]?(\.[0-9]+)|([0-9]+(\.[0-9]*)|([eE][-+]?[0-9]+))$",
			REG_EXTENDED | REG_NOSUB);
	if (err == 0){
		err = regexec(&reg, lexical, 0, NULL, 0);
	}
	regfree(&reg);
	return err == 0;
}

bool castable_as_double(char* lexical, char *x, size_t xl){
	if (is_string_datatype){
		return reg_double(lexical);
	}
	if (ISURI(x, xl, _XS_decimal_)) return true;
	if (ISURI(x, xl, _XS_double_)) return true;
	if (ISURI(x, xl, _XS_float_)) return true;
	return false;
}


bool castable_as_hexadecimal(char *lexical, char *x, size_t xl){
	if (is_string_datatype){
		return reg_hexadecimal(lexical);
	}
	if (ISURI(x, xl, _XS_hexBinary_)) return true;
	return false;
}

bool castable_as_long(char *lexical, char *x, size_t xl){
	if (is_string_datatype){
		return reg_int(lexical);
	}
	if (ISURI(x, xl, _XS_integer_)) return true;
	if (ISURI(x, xl, _XS_long_)) return true;
	if (ISURI(x, xl, _XS_int_)) return true;
	if (ISURI(x, xl, _XS_short_)) return true;
	if (ISURI(x, xl, _XS_byte_)) return true;
	if (ISURI(x, xl, _XS_nonNegativeInteger_)) return true;
	if (ISURI(x, xl, _XS_positiveInteger_)) return true;
	if (ISURI(x, xl, _XS_unsignedLong_)) return true;
	if (ISURI(x, xl, _XS_unsignedInt_)) return true;
	if (ISURI(x, xl, _XS_unsignedShort_)) return true;
	if (ISURI(x, xl, _XS_unsignedByte_)) return true;
	if (ISURI(x, xl, _XS_nonPositiveInteger_)) return true;
	if (ISURI(x, xl, _XS_negativeInteger_)) return true;
	return false;
}
