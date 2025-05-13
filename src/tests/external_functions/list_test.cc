#include <gtest/gtest.h>
#include <unistd.h>
#include <linux/limits.h>

#include <ffi_clips_interface.h>
#include <ntriplesParser.h>
#include "crifi_import.h"
#include "ffi_constants.h"

#include "info_query.h"
#include "helper.h"


TEST(ExternalFunctionsList, remove){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#remove> (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"  )  \"-5^^http://www.w3.org/2001/XMLSchema#integer\"  )  (<http://www.w3.org/2007/rif-builtin-function#make-list> \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"  ) )"

			);
}

TEST(ExternalFunctionsList, insertBefore){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#insert-before> (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"  )  \"-1^^http://www.w3.org/2001/XMLSchema#integer\"   \"99^^http://www.w3.org/2001/XMLSchema#integer\"  )  (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"99^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"  ) )"

			);
}

TEST(ExternalFunctionsList, count){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#count> (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"  ) )  \"5^^http://www.w3.org/2001/XMLSchema#integer\"  )"

			);
}

TEST(ExternalFunctionsList, listContaints){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#list-contains> (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"   (<http://www.w3.org/2007/rif-builtin-function#make-list> \"7^^http://www.w3.org/2001/XMLSchema#integer\"   \"8^^http://www.w3.org/2001/XMLSchema#integer\"  ) )  (<http://www.w3.org/2007/rif-builtin-function#make-list> \"7^^http://www.w3.org/2001/XMLSchema#integer\"   \"8^^http://www.w3.org/2001/XMLSchema#integer\"  ) )"
			);
}

TEST(ExternalFunctionsList, sublist){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#sublist> (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"  )  \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"5^^http://www.w3.org/2001/XMLSchema#integer\"  )  (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"  ) )"
			);
}

TEST(ExternalFunctionsList, except){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#except> (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"  )  (<http://www.w3.org/2007/rif-builtin-function#make-list> \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"  ) )  (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"  ) )"
			);
}

TEST(ExternalFunctionsList, reverse){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#reverse> (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"  ) )  (<http://www.w3.org/2007/rif-builtin-function#make-list> \"4^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"0^^http://www.w3.org/2001/XMLSchema#integer\"  ) )"
			);
}

TEST(ExternalFunctionsList, append){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#append> (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"  )  \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"  )  (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"  ) )"
			);
}

TEST(ExternalFunctionsList, distinctValues){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#distinct-values> (<http://www.w3.org/2007/rif-builtin-function#make-list> \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"  ) )  (<http://www.w3.org/2007/rif-builtin-function#make-list> \"3^^http://www.w3.org/2001/XMLSchema#integer\"  ) )"
			);
}

TEST(ExternalFunctionsList, intersect){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#intersect> (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"  )  (<http://www.w3.org/2007/rif-builtin-function#make-list> \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"  ) )  (<http://www.w3.org/2007/rif-builtin-function#make-list> \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"  ) )"
			);
}

TEST(ExternalFunctionsList, isList){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-list> (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   (<http://www.w3.org/2007/rif-builtin-function#make-list> \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"  ) ) )"
			);
}

TEST(ExternalFunctionsList, concatenate){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#concatenate> (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"  )  (<http://www.w3.org/2007/rif-builtin-function#make-list> \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"   \"5^^http://www.w3.org/2001/XMLSchema#integer\"  ) )  (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"   \"5^^http://www.w3.org/2001/XMLSchema#integer\"  ) )"
			);
}

TEST(ExternalFunctionsList, indexOf){
	check_command_true( 

			"(eq (<http://www.w3.org/2007/rif-builtin-function#index-of> (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"   \"5^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"  )  \"2^^http://www.w3.org/2001/XMLSchema#integer\"  )  (<http://www.w3.org/2007/rif-builtin-function#make-list> \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"6^^http://www.w3.org/2001/XMLSchema#integer\"   \"7^^http://www.w3.org/2001/XMLSchema#integer\"  ) )"
			);
}

TEST(ExternalFunctionsList, get){
	check_command_true( 

			"(eq (<http://www.w3.org/2007/rif-builtin-function#get> (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"  )  \"-1^^http://www.w3.org/2001/XMLSchema#integer\"  )  \"4^^http://www.w3.org/2001/XMLSchema#integer\"  )"
			);
}

TEST(ExternalFunctionsList, unionList){
	check_command_true( 

			"(eq (<http://www.w3.org/2007/rif-builtin-function#union> (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"  )  (<http://www.w3.org/2007/rif-builtin-function#make-list> \"4^^http://www.w3.org/2001/XMLSchema#integer\"  ) )  (<http://www.w3.org/2007/rif-builtin-function#make-list> \"0^^http://www.w3.org/2001/XMLSchema#integer\"   \"1^^http://www.w3.org/2001/XMLSchema#integer\"   \"2^^http://www.w3.org/2001/XMLSchema#integer\"   \"3^^http://www.w3.org/2001/XMLSchema#integer\"   \"4^^http://www.w3.org/2001/XMLSchema#integer\"  ) )"
			);
}
