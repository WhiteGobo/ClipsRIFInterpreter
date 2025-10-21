#include <gtest/gtest.h>
#include <unistd.h>
#include <linux/limits.h>

#include <ffi_clips_interface.h>
#include "crifi_import.h"
#include "ffi_constants.h"

#include "info_query.h"
#include "helper.h"


TEST(ExternalFunctionsStrings, isliteralstring){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-string> \"Hello%20world\" )"
			);
}

TEST(ExternalFunctionsStrings, isliteralnormalizedString){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-normalizedString> \"Hello%20world\" )"
			);
}

TEST(ExternalFunctionsStrings, isliteraltoken){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-token> \"Hello%20world\" )"
			);
}

TEST(ExternalFunctionsStrings, isliterallanguage){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-language> \"en^^http://www.w3.org/2001/XMLSchema#language\" )"
			);
}

TEST(ExternalFunctionsStrings, isliteralName){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-Name> \"Hello^^http://www.w3.org/2001/XMLSchema#Name\" )"
			);
}

TEST(ExternalFunctionsStrings, isliteralNCName){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-NCName> \"Hello^^http://www.w3.org/2001/XMLSchema#NCName\" )"
			);
}

TEST(ExternalFunctionsStrings, isliteralNTOKEN){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-NMTOKEN> \"Hello^^http://www.w3.org/2001/XMLSchema#NMTOKEN\" )"
			);
}

TEST(ExternalFunctionsStrings, isliteralnotstring){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-not-string> \"1^^http://www.w3.org/2001/XMLSchema#integer\" )"
			);
}

TEST(ExternalFunctionsStrings, isliteralnotnormalizedString){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-not-normalizedString> \"1^^http://www.w3.org/2001/XMLSchema#integer\" )"
			);
}

TEST(ExternalFunctionsStrings, isliteralnottoken){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-not-token> \"1^^http://www.w3.org/2001/XMLSchema#integer\" )"
			);
}

TEST(ExternalFunctionsStrings, isliteralnotlanguage){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-not-language> \"1^^http://www.w3.org/2001/XMLSchema#integer\" )"
			);
}

TEST(ExternalFunctionsStrings, isliteralnotName){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-not-Name> \"1^^http://www.w3.org/2001/XMLSchema#integer\" )"
			);
}

TEST(ExternalFunctionsStrings, isliteralnotNCName){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-not-NCName> \"1^^http://www.w3.org/2001/XMLSchema#integer\" )"
			);
}

TEST(ExternalFunctionsStrings, isliteralnotNMTOKEN){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-not-NMTOKEN> \"1^^http://www.w3.org/2001/XMLSchema#integer\" )"
			);
}

TEST(ExternalFunctionsStrings, castasstring){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-string> (<http://www.w3.org/2001/XMLSchema#string> \"1^^http://www.w3.org/2001/XMLSchema#integer\" ) )"
			);
}

TEST(ExternalFunctionsStrings, castasnormalizedString){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-normalizedString> (<http://www.w3.org/2001/XMLSchema#normalizedString> \"1^^http://www.w3.org/2001/XMLSchema#integer\" ) )"
			);
}

TEST(ExternalFunctionsStrings, castasliteraltoken){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-token> (<http://www.w3.org/2001/XMLSchema#token> \"de^^http://www.w3.org/2001/XMLSchema#hexBinary\" ) )"
			);
}

TEST(ExternalFunctionsStrings, castasliterallanguage){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-language> (<http://www.w3.org/2001/XMLSchema#language> \"de^^http://www.w3.org/2001/XMLSchema#hexBinary\" ) )"
			);
}

TEST(ExternalFunctionsStrings, castasliteralName){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-Name> (<http://www.w3.org/2001/XMLSchema#Name> \"de^^http://www.w3.org/2001/XMLSchema#hexBinary\" ) )"
			);
}

TEST(ExternalFunctionsStrings, castasliteralNCName){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-NCName> (<http://www.w3.org/2001/XMLSchema#NCName> \"de^^http://www.w3.org/2001/XMLSchema#hexBinary\" ) )"
			);
}

TEST(ExternalFunctionsStrings, castasliteralNMTOKEN){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-NMTOKEN> (<http://www.w3.org/2001/XMLSchema#NMTOKEN> \"de^^http://www.w3.org/2001/XMLSchema#hexBinary\" ) )"
			);
}

TEST(ExternalFunctionsStrings, iristring){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#iri-string> <http://www.example.org> \"http%3A%2F%2Fwww.example.org\" )"
			);
}

TEST(ExternalFunctionsStrings, compare1){
	check_command_true( 
			"(eq \"-1^^http://www.w3.org/2001/XMLSchema#integer\"(<http://www.w3.org/2007/rif-builtin-function#compare> \"bar\" \"foo\" ))"
			);
}

TEST(ExternalFunctionsStrings, compare2){
	check_command_true( 
			"(eq \"1^^http://www.w3.org/2001/XMLSchema#integer\"(<http://www.w3.org/2007/rif-builtin-function#compare> \"foo\" \"bar\" ))"
			);
}

TEST(ExternalFunctionsStrings, compare3){
	check_command_true( 
			"(eq \"0^^http://www.w3.org/2001/XMLSchema#integer\"(<http://www.w3.org/2007/rif-builtin-function#compare> \"bar\" \"bar\" ))"
			);
}

TEST(ExternalFunctionsStrings, concat){
	check_command_true( 
			"(eq \"foobar\"(<http://www.w3.org/2007/rif-builtin-function#concat> \"foo\" \"bar\" ))"
			);
}

TEST(ExternalFunctionsStrings, stringjoin){
	check_command_true( 
			"(eq \"foo%2Cbar\"(<http://www.w3.org/2007/rif-builtin-function#string-join> \"foo\" \"bar\" \"%2C\" ))"
			);
}

TEST(ExternalFunctionsStrings, substring1){
	check_command_true( 
			"(eq \"bar\"(<http://www.w3.org/2007/rif-builtin-function#substring> \"foobar\" \"3^^http://www.w3.org/2001/XMLSchema#integer\" ))"
			);
	fprintf_command_result(stderr,
			"(<http://www.w3.org/2007/rif-builtin-function#substring> \"foobar\" \"3^^http://www.w3.org/2001/XMLSchema#integer\" )");
}

TEST(ExternalFunctionsStrings, substring2){
	check_command_true( 
			"(eq \"fo\"(<http://www.w3.org/2007/rif-builtin-function#substring> \"foobar\" \"0^^http://www.w3.org/2001/XMLSchema#integer\" \"3^^http://www.w3.org/2001/XMLSchema#integer\" ))"
			);
}

TEST(ExternalFunctionsStrings, stringlength){
	check_command_true( 
			"(eq \"3^^http://www.w3.org/2001/XMLSchema#integer\"(<http://www.w3.org/2007/rif-builtin-function#string-length> \"foo\" ))"
			);
}

TEST(ExternalFunctionsStrings, uppercase){
	check_command_true( 
			"(eq \"FOOBAR\"(<http://www.w3.org/2007/rif-builtin-function#upper-case> \"FooBar\" ))"
			);
}

TEST(ExternalFunctionsStrings, lowercase){
	check_command_true( 
			"(eq \"foobar\"(<http://www.w3.org/2007/rif-builtin-function#lower-case> \"FooBar\" ))"
			);
}

TEST(ExternalFunctionsStrings, encodeforuri){
	check_command_true( 
			"(eq \"RIF%2520Basic%2520Logic%2520Dialect\"(<http://www.w3.org/2007/rif-builtin-function#encode-for-uri> \"RIF%20Basic%20Logic%20Dialect\" ))"
			);
}

TEST(ExternalFunctionsStrings, iritouri){
	check_command_true( 
			"(eq \"http%3A%2F%2Fwww.example.com%2F~b%25C3%25A9b%25C3%25A9\"(<http://www.w3.org/2007/rif-builtin-function#iri-to-uri> \"http%3A%2F%2Fwww.example.com%2F~b%C3%A9b%C3%A9\" ))"
			);
}

TEST(ExternalFunctionsStrings, escapehtmluri){
	check_command_true( 
			"(eq \"javascript%3Aif%20%28navigator.browserLanguage%20%3D%3D%20%27fr%27%29%20window.open%28%27http%3A%2F%2Fwww.example.com%2F~b%25C3%25A9b%25C3%25A9%27%29%3B\"(<http://www.w3.org/2007/rif-builtin-function#escape-html-uri> \"javascript%3Aif%20%28navigator.browserLanguage%20%3D%3D%20%27fr%27%29%20window.open%28%27http%3A%2F%2Fwww.example.com%2F~b%C3%A9b%C3%A9%27%29%3B\" ))"
			);
}

TEST(ExternalFunctionsStrings, substringbefore){
	check_command_true( 
			"(eq \"foo\"(<http://www.w3.org/2007/rif-builtin-function#substring-before> \"foobar\" \"bar\" ))"
			);
}

TEST(ExternalFunctionsStrings, substringafter){
	check_command_true( 
			"(eq \"bar\"(<http://www.w3.org/2007/rif-builtin-function#substring-after> \"foobar\" \"foo\" ))"
			);
}

TEST(ExternalFunctionsStrings, replace){
	check_command_true( 
			"(eq \"%5B1%3Dab%5D%5B2%3D%5Dcd\"(<http://www.w3.org/2007/rif-builtin-function#replace> \"abcd\" \"%28ab%29%7C%28a%29\" \"%5B1%3D%241%5D%5B2%3D%242%5D\" ))"
			);
}

TEST(ExternalFunctionsStrings, contains){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#contains> \"foobar\" \"foo\" )"
			);
}

TEST(ExternalFunctionsStrings, startswith){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#starts-with> \"foobar\" \"foo\" )"
			);
}

TEST(ExternalFunctionsStrings, endswith){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#ends-with> \"foobar\" \"bar\" )"
			);
}

TEST(ExternalFunctionsStrings, matches){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#matches> \"abracadabra\" \"%5Ea.%2Aa%24\" )"
			);
}

