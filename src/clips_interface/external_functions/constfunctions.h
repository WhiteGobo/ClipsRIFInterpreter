#pragma once
#include <n3parser.h>
#include "ffi_constants.h"
#include "math_user_defined_functions.h"
#include "pred_user_defined_functions.h"
#include "list_user_defined_functions.h"
#include "binary_user_defined_functions.h"
#include "own_user_defined_functions.h"

#include "external_functions.h"

typedef enum {
	CT_static,
	CT_generate,
} ContextType;

typedef struct UDFDescription_ {
	const char *clipsName;
	const char *returnTypes;
	unsigned short minArgs;
	unsigned short maxArgs;
	const char *argTypes;
	UserDefinedFunction *cfp;
	const char *cName;
	ContextType contextType;
	union {
		void *context;
	};
} UDFDescription;

static ContextTypecheck CRegular = {false};
static ContextTypecheck CInvert = {true};

static UDFDescription builtinFunctionList[] = {
	{"<"_CRIFI_equal_">", "*", 2, 2, "*",
		clipsudf_equal, "clipsudf_equal", CT_static, NULL},
	{"<"_CRIFI_percent_encode_">", "s", 1, 1, "s",
		_clipsudf_percent_encoding, "_clipsudf_percent_encoding",  CT_static, NULL},
	{"PercentDecoding", "s", 1, 1, "s",
		_clipsudf_percent_encoding,
		"_clipsudf_percent_encoding",
		CT_static, NULL},
	{"<"_RIFBUILTIN_"numeric-add>", "s", 2, 2, "s",
		rif_numeric_add, "rif_numeric_add", CT_static, NULL},
	{"<"_RIFBUILTIN_"numeric-subtract>", "s", 2, 2, "s",
		rif_numeric_subtract, "rif_numeric_subtract", CT_static, NULL},
	{"<"_RIFBUILTIN_"numeric-multiply>", "s", 2, 2, "s",
		rif_numeric_multiply, "rif_numeric_multiply", CT_static, NULL},
	{"<"_RIFBUILTIN_"numeric-divide>", "s", 2, 2, "s",
		rif_numeric_divide, "rif_numeric_divide", CT_static, NULL},
	{"<"_RIFBUILTIN_"numeric-integer-divide>", "s", 2, 2, "s",
		rif_numeric_integer_divide, "rif_numeric_integer_divide", CT_static, NULL},
	{"<"_RIFBUILTIN_"numeric-integer-mod>", "s", 2, 2, "s",
		rif_numeric_integer_mod, "rif_numeric_integer_mod", CT_static, NULL},
	{"<"_PRED_numeric_equal_">", "s", 2, 2, "s",
		rif_numeric_equal, "rif_numeric_equal", CT_static, NULL},
	{"<"_PRED_numeric_not_equal_">", "s", 2, 2, "s",
		rif_numeric_not_equal, "rif_numeric_not_equal", CT_static, NULL},
	{"<"_PRED_numeric_less_than_">", "s", 2, 2, "s",
		rif_numeric_less_than, "rif_numeric_less_than", CT_static, NULL},
	{"<"_PRED_numeric_less_than_or_equal_">", "s", 2, 2, "s",
		rif_numeric_less_than_or_equal, "rif_numeric_less_than_or_equal", CT_static, NULL},
	{"<"_PRED_numeric_greater_than_">", "s", 2, 2, "s",
		rif_numeric_greater_than, "rif_numeric_greater_than", CT_static, NULL},
	{"<"_PRED_numeric_greater_than_or_equal_">", "s", 2, 2, "s",
		rif_numeric_greater_than_or_equal, "rif_numeric_greater_than_or_equal", CT_static, NULL},


	{"<"_PRED_literal_not_identical_">", "*", 0, 2, NULL,
		pred_literal_not_identical, "pred_literal_not_identical", CT_static, NULL},


	{"<"_PRED_is_literal_double_">", "b", 1, 1, "s",
		rif_is_literal_double, "rif_is_literal_double", CT_static, &CRegular},
	{"<"_PRED_is_literal_float_">", "b", 1, 1, "s",
		rif_is_literal_float, "rif_is_literal_float", CT_static, &CRegular},
	{"<"_PRED_is_literal_decimal_">", "b", 1, 1, "s",
		rif_is_literal_decimal, "rif_is_literal_decimal", CT_static, &CRegular},
	{"<"_PRED_is_literal_hexBinary_">", "b", 1, 1, "s",
		rif_is_literal_hexBinary, "rif_is_literal_hexBinary", CT_static, &CRegular},
	{"<"_PRED_is_literal_integer_">", "b", 1, 1, "s",
		rif_is_literal_integer, "rif_is_literal_integer", CT_static, &CRegular},
	{"<"_PRED_is_literal_long_">", "b", 1, 1, "s",
		rif_is_literal_long, "rif_is_literal_long", CT_static, &CRegular},
	{"<"_PRED_is_literal_int_">", "b", 1, 1, "s",
		rif_is_literal_int, "rif_is_literal_int", CT_static, &CRegular},
	{"<"_PRED_is_literal_short_">", "b", 1, 1, "s",
		rif_is_literal_short, "rif_is_literal_short", CT_static, &CRegular},
	{"<"_PRED_is_literal_byte_">", "b", 1, 1, "s",
		rif_is_literal_byte, "rif_is_literal_byte", CT_static, &CRegular},
	{"<"_PRED_is_literal_nonNegativeInteger_">", "b", 1, 1, "s",
		rif_is_literal_nonNegativeInteger, "rif_is_literal_nonNegativeInteger", CT_static, &CRegular},
	{"<"_PRED_is_literal_positiveInteger_">", "b", 1, 1, "s",
		rif_is_literal_positiveInteger, "rif_is_literal_positiveInteger", CT_static, &CRegular},
	{"<"_PRED_is_literal_unsignedLong_">", "b", 1, 1, "s",
		rif_is_literal_unsignedLong, "rif_is_literal_unsignedLong", CT_static, &CRegular},
	{"<"_PRED_is_literal_unsignedInt_">", "b", 1, 1, "s",
		rif_is_literal_unsignedInt, "rif_is_literal_unsignedInt", CT_static, &CRegular},
	{"<"_PRED_is_literal_unsignedShort_">", "b", 1, 1, "s",
		rif_is_literal_unsignedShort, "rif_is_literal_unsignedShort", CT_static, &CRegular},
	{"<"_PRED_is_literal_unsignedByte_">", "b", 1, 1, "s",
		rif_is_literal_unsignedByte, "rif_is_literal_unsignedByte", CT_static, &CRegular},
	{"<"_PRED_is_literal_nonPositiveInteger_">", "b", 1, 1, "s",
		rif_is_literal_nonPositiveInteger, "rif_is_literal_nonPositiveInteger", CT_static, &CRegular},
	{"<"_PRED_is_literal_negativeInteger_">", "b", 1, 1, "s",
		rif_is_literal_negativeInteger, "rif_is_literal_negativeInteger", CT_static, &CRegular},

	{"<"_PRED_is_literal_not_double_">", "b", 1, 1, "s",
		rif_is_literal_double, "rif_is_literal_double", CT_static, &CInvert},
	{"<"_PRED_is_literal_not_float_">", "b", 1, 1, "s",
		rif_is_literal_float, "rif_is_literal_float", CT_static, &CInvert},
	{"<"_PRED_is_literal_not_decimal_">", "b", 1, 1, "s",
		rif_is_literal_decimal, "rif_is_literal_decimal", CT_static, &CInvert},
	{"<"_PRED_is_literal_not_hexBinary_">", "b", 1, 1, "s",
		rif_is_literal_hexBinary, "rif_is_literal_hexBinary", CT_static, &CInvert},
	{"<"_PRED_is_literal_not_integer_">", "b", 1, 1, "s",
		rif_is_literal_integer, "rif_is_literal_integer", CT_static, &CInvert},
	{"<"_PRED_is_literal_not_long_">", "b", 1, 1, "s",
		rif_is_literal_long, "rif_is_literal_long", CT_static, &CInvert},
	{"<"_PRED_is_literal_not_int_">", "b", 1, 1, "s",
		rif_is_literal_int, "rif_is_literal_int", CT_static, &CInvert},
	{"<"_PRED_is_literal_not_short_">", "b", 1, 1, "s",
		rif_is_literal_short, "rif_is_literal_short", CT_static, &CInvert},
	{"<"_PRED_is_literal_not_byte_">", "b", 1, 1, "s",
		rif_is_literal_byte, "rif_is_literal_byte", CT_static, &CInvert},
	{"<"_PRED_is_literal_not_nonNegativeInteger_">", "b", 1, 1, "s",
		rif_is_literal_nonNegativeInteger, "rif_is_literal_nonNegativeInteger", CT_static, &CInvert},
	{"<"_PRED_is_literal_not_positiveInteger_">", "b", 1, 1, "s",
		rif_is_literal_positiveInteger, "rif_is_literal_positiveInteger", CT_static, &CInvert},
	{"<"_PRED_is_literal_not_unsignedLong_">", "b", 1, 1, "s",
		rif_is_literal_unsignedLong, "rif_is_literal_unsignedLong", CT_static, &CInvert},
	{"<"_PRED_is_literal_not_unsignedInt_">", "b", 1, 1, "s",
		rif_is_literal_unsignedInt, "rif_is_literal_unsignedInt", CT_static, &CInvert},
	{"<"_PRED_is_literal_not_unsignedShort_">", "b", 1, 1, "s",
		rif_is_literal_unsignedShort, "rif_is_literal_unsignedShort", CT_static, &CInvert},
	{"<"_PRED_is_literal_not_unsignedByte_">", "b", 1, 1, "s",
		rif_is_literal_unsignedByte, "rif_is_literal_unsignedByte", CT_static, &CInvert},
	{"<"_PRED_is_literal_not_nonPositiveInteger_">", "b", 1, 1, "s",
		rif_is_literal_nonPositiveInteger, "rif_is_literal_nonPositiveInteger", CT_static, &CInvert},
	{"<"_PRED_is_literal_not_negativeInteger_">", "b", 1, 1, "s",
		rif_is_literal_negativeInteger, "rif_is_literal_negativeInteger", CT_static, &CInvert},

	{"<"_XS_double_">", "s", 1, 1, "s",
		rif_cast_as, "rif_cast_as", CT_static, _XS_double_},
	{"<"_XS_float_">", "s", 1, 1, "s",
		rif_cast_as, "rif_cast_as", CT_static, _XS_float_},
	{"<"_XS_decimal_">", "s", 1, 1, "s", rif_cast_as, "rif_cast_as", CT_static, _XS_decimal_},
	{"<"_XS_hexBinary_">", "s", 1, 1, "s",
		rif_cast_as, "rif_cast_as", CT_static, _XS_hexBinary_},
	{"<"_XS_base64Binary_">", "s", 1, 1, "s",
		rif_cast_as, "rif_cast_as", CT_static, _XS_base64Binary_},
	{"<"_XS_integer_">", "s", 1, 1, "s", rif_cast_as, "rif_cast_as", CT_static, _XS_integer_},
	{"<"_XS_long_">", "s", 1, 1, "s", rif_cast_as, "rif_cast_as", CT_static, _XS_long_},
	{"<"_XS_int_">", "s", 1, 1, "s", rif_cast_as, "rif_cast_as", CT_static, _XS_int_},
	{"<"_XS_short_">", "s", 1, 1, "s", rif_cast_as, "rif_cast_as", CT_static, _XS_short_},
	{"<"_XS_byte_">", "s", 1, 1, "s", rif_cast_as, "rif_cast_as", CT_static, _XS_byte_},
	{"<"_XS_nonNegativeInteger_">", "s", 1, 1, "s", rif_cast_as, "rif_cast_as", CT_static, _XS_nonNegativeInteger_},
	{"<"_XS_positiveInteger_">", "s", 1, 1, "s", rif_cast_as, "rif_cast_as", CT_static, _XS_positiveInteger_},
	{"<"_XS_unsignedLong_">", "s", 1, 1, "s", rif_cast_as, "rif_cast_as", CT_static, _XS_unsignedLong_},
	{"<"_XS_unsignedInt_">", "s", 1, 1, "s", rif_cast_as, "rif_cast_as", CT_static, _XS_unsignedInt_},
	{"<"_XS_unsignedShort_">", "s", 1, 1, "s", rif_cast_as, "rif_cast_as", CT_static, _XS_unsignedShort_},
	{"<"_XS_unsignedByte_">", "s", 1, 1, "s", rif_cast_as, "rif_cast_as", CT_static, _XS_unsignedByte_},
	{"<"_XS_nonPositiveInteger_">", "s", 1, 1, "s", rif_cast_as, "rif_cast_as", CT_static, _XS_nonPositiveInteger_},
	{"<"_XS_negativeInteger_">", "s", 1, 1, "s", rif_cast_as, "rif_cast_as", CT_static, _XS_negativeInteger_},

	{"<"_PRED_is_list_">", "b", 1, 1, "*",
		pred_is_list, "pred_is_list", CT_static, NULL},
	{"<"_PRED_list_contains_">", "b", 2, 2, "*",
		pred_list_contains, "pred_list_contains", CT_static, NULL},
	{"<"_FUNC_make_list_">", "*", 0, UNBOUNDED, "*",
		func_make_list, "func_make_list", CT_static, NULL},
	{"<"_FUNC_count_">", "*", 1, 1, "*",
		func_count, "func_count", CT_static, NULL},
	{"<"_FUNC_get_">", "*", 0, -1, "*",
		func_get, "func_get", CT_static, NULL},
	{"<"_FUNC_sublist_">", "*", 2, 3, "*",
		func_sublist, "func_sublist", CT_static, NULL},
	{"<"_FUNC_append_">", "*", 2, -1, "*",
		func_append, "func_append", CT_static, NULL},
	{"<"_FUNC_concatenate_">", "*", 2, -1, "*",
		func_concatenate, "func_concatenate", CT_static, NULL},
	{"<"_FUNC_insert_before_">", "*", 3, 3, "*",
		func_insert_before, "func_insert_before", CT_static, NULL},
	{"<"_FUNC_remove_">", "*", 2, 2, "*",
		func_remove, "func_remove", CT_static, NULL},
	{"<"_FUNC_reverse_">", "*", 1, 1, "*",
		func_reverse, "func_reverse", CT_static, NULL},
	{"<"_FUNC_index_of_">", "*", 2, 2, "*",
		func_index_of, "func_index_of", CT_static, NULL},
	{"<"_FUNC_union_">", "*", 2, -1, "*",
		func_union, "func_union", CT_static, NULL},
	{"<"_FUNC_distinct_values_">", "*", 1, 1, "*",
		func_distinct_values, "func_distinct_values", CT_static, NULL},
	{"<"_FUNC_intersect_">", "*", 2, -1, "*",
		func_intersect, "func_intersect", CT_static, NULL},
	{"<"_FUNC_except_">", "*", 2, 2, "*",
		func_except, "func_except", CT_static, NULL},

	{"<"_PRED_is_literal_base64Binary_">", "b", 1, 1, "s",
		rif_is_literal_base64Binary, "rif_is_literal_base64Binary",
		CT_static, &CRegular},
	{"<"_PRED_is_literal_not_base64Binary_">", "b", 1, 1, "s",
		rif_is_literal_base64Binary, "rif_is_literal_base64Binary",
		CT_static, &CInvert},


	{NULL, NULL, 0,0, NULL, NULL, NULL, CT_static, NULL}
};
