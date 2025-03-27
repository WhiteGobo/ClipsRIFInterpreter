/** \anchor ImportTest
 */
#include <gtest/gtest.h>
#include <unistd.h>
#include <linux/limits.h>

#include <ffi_clips_interface.h>
#include <ntriplesParser.h>
#include "ffi_constants.h"
#include "crifi_import_implementations.h"

static FILE *test_import_method(void *context){
	char data[] = "#asdf";
	return fmemopen(data, strlen(data), "r");
}

#define TESTADDRESSA "http://example.com/test_address_a"
#define TESTADDRESSB "http://example.com/test_address_b"

TEST(ImportTest, Basic){
	struct DynamicValue retval;
	crifi_graph* graph = init_graph();
	FilepathImportidPair importlocations[] = {
		{.id= TESTADDRESSA, .filepath="asdf"},
		{.id=NULL}
	};
	GetfileImportidPair importmethods[] = {
		{.id= TESTADDRESSB, .method=test_import_method, .context=NULL, .cleanup=NULL},
		{.id=NULL}
	};

	bool err = add_importlocations(graph, importlocations, importmethods);
	if (!err){
		FAIL() << "Failed to add import locations";
		close_graph(graph);
	}
	retval = eval(graph, "(<" _CRIFI_import_ "> <"TESTADDRESSB"> <" _RIFENTAIL_SIMPLE_ ">)");
	switch (retval.type){
		case CTC_DYNAMIC_ERROR:
			switch (retval.val.error){
				case CTC_CTD_PARSING_ERROR:
					FAIL() << "parsing error? test broken? "
						"crifi:import is maybe not "
						"loaded as "
						"user defined function";
				case CTC_CTD_PROCESSING_ERROR:
					FAIL() << "failed processing command.";
				case CTC_CTD_CANTTRANSLATE:
					FAIL() << "Cant process returned "
						"CLIPSValue to DynamicType";
				default:
					FAIL() << "eval import failed. "
						"Unhandled error.";
			}
			break;
		case CTC_DYNAMIC_BOOL:
			EXPECT_EQ(retval.val.boolean, true)
				<< "crifi:import return failure.";
			break;
		default:
			FAIL() << "crifi:import return unexpected value.";
	}


	retval = eval(graph, "(< 0 (length$ (find-fact ((?x TripleTemplate)) TRUE)))");
	switch (retval.type){
		case CTC_DYNAMIC_BOOL:
			EXPECT_EQ(retval.val.boolean, true)
				<< "crifi:import didnt assert any triple";
			break;
		default:
			FAIL() << "broken test?";
	}

	close_graph(graph);
	//FAIL() << "testfailure";
}
