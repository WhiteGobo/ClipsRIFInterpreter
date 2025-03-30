/** \anchor ImportTest
 */
#include <gtest/gtest.h>
#include <unistd.h>
#include <linux/limits.h>

#include <ffi_clips_interface.h>
#include <ntriplesParser.h>
#include "ffi_constants.h"
#include "crifi_import_implementations.h"

#include "testdata.h"

static char data[] = "[] <http://example.com/propA> 3; <http://example.com/propB> [].\n";

static FILE *test_import_method(void *context){
	FILE *qq = fmemopen(data, strlen(data), "r");
	if (qq == NULL){
		fprintf(stderr, "test_import_method failed\n");
	}
	return qq;
}

#define TESTADDRESSA "http://example.com/test_address_a"
#define TESTADDRESSB "http://example.com/test_address_b"

static void execute_import(crifi_graph* graph, const char *address, const char *entailment){
	struct DynamicValue retval;
	char *qq = (char*) malloc(1 + sizeof("(<" _CRIFI_import_ "> <> <>)") + strlen(address) + strlen(entailment));
	sprintf(qq, "(<" _CRIFI_import_ "> <%s> <%s>)", address, entailment);
	retval = eval(graph, qq);
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
			ASSERT_EQ(retval.val.boolean, true)
				<< "crifi:import return failure.";
			break;
		default:
			FAIL() << "crifi:import return unexpected value.";
	}
}

static void check_any_triples(crifi_graph *graph){
	struct DynamicValue retval;
	retval = eval(graph, "(< 0 (length$ (find-fact ((?x TripleTemplate)) TRUE)))");
	switch (retval.type){
		case CTC_DYNAMIC_BOOL:
			EXPECT_EQ(retval.val.boolean, true)
				<< "crifi:import didnt assert any triple";
			break;
		default:
			FAIL() << "broken test?";
	}
}

TEST(ImportTest, Basic){
	struct DynamicValue retval;
	crifi_graph* graph = init_graph();
	FilepathImportidPair importlocations[] = {
		{.id= TESTADDRESSA, .filepath="asdf", .syntax=_SYNTAX_TURTLE_},
		{.id=NULL}
	};
	GetfileImportidPair importmethods[] = {
		{.id= TESTADDRESSB, .method=test_import_method, .context=NULL, .cleanup=NULL, .syntax=_SYNTAX_TURTLE_},
		{.id=NULL}
	};

	bool err = add_importlocations(graph, importlocations, importmethods);
	if (!err){
		FAIL() << "Failed to add import locations";
		close_graph(graph);
	}
	execute_import(graph, TESTADDRESSB, _RIFENTAIL_SIMPLE_);

	check_any_triples(graph);

	close_graph(graph);
	//FAIL() << "testfailure";
}

TEST(ImportTest, SourceImport){
	struct DynamicValue retval;
	crifi_graph* graph = init_graph();


	if(!testdata_add_importlocations(graph)){
		FAIL() << "Failed to add import locations";
		close_graph(graph);
	}
	execute_import(graph, "http://example.com/testdata#shared_bnode",
			_RIFENTAIL_SIMPLE_);

	check_any_triples(graph);

	eval(graph, "(facts)");
	close_graph(graph);
	//FAIL() << "testfailure";
}
