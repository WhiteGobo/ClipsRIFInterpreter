#include <gtest/gtest.h>
#include <unistd.h>
#include <linux/limits.h>

#include "helper.h"

TEST(ExternalFunctionsXMLLiteral, isliteralstring){
	check_command_true( 
	"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-XMLLiteral> \"%3Cbr%2F%3E^^http://www.w3.org/1999/02/22-rdf-syntax-ns#XMLLiteral\" )");
}

TEST(ExternalFunctionsXMLLiteral, isliteralnotstring){
	check_command_true( 
	"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-not-XMLLiteral> \"1^^http://www.w3.org/2001/XMLSchema#integer\" )");
}

TEST(ExternalFunctionsXMLLiteral, castasxmlliteral){
	check_command_true( 
	"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-XMLLiteral> (<http://www.w3.org/1999/02/22-rdf-syntax-ns#XMLLiteral> \"%3Cbr%3E%3C%2Fbr%3E\" ) )");
}
