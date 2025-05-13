#include <gtest/gtest.h>
#include <unistd.h>
#include <linux/limits.h>

#include <ffi_clips_interface.h>
#include <ntriplesParser.h>
#include "crifi_import.h"
#include "ffi_constants.h"

#include "info_query.h"
#include "helper.h"


TEST(ExternalFunctionsBoolean, isLiteralBoolean){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-boolean> TRUE)"
			);
}

TEST(ExternalFunctionsBoolean, isLiteralNotBoolean){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-not-boolean> \"foo\"  )"
			);
}

TEST(ExternalFunctionsBoolean, castBoolean){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-boolean> (<http://www.w3.org/2001/XMLSchema#boolean> \"1\"  ) )"
			);
}

TEST(ExternalFunctionsBoolean, BooleanLessThan){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#boolean-less-than> FALSE TRUE)"
			);
}

TEST(ExternalFunctionsBoolean, BooleanGreaterThan){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#boolean-greater-than> TRUE FALSE)"
			);
}

TEST(ExternalFunctionsBoolean, BooleanEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#boolean-equal> FALSE FALSE)"
			);
}
