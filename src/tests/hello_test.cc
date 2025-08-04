/** \anchor BasicFactTest
 * For testing you have to provide the path to the assets:
 * eg: `env ASSETPATH_CLIPSSCRIPTS=path/to/assets ctest`
 */
#include <gtest/gtest.h>
#include <unistd.h>
#include <linux/limits.h>

#include <ffi_clips_interface.h>
#include <ntriplesParser.h>
#include "crifi_import.h"
#include "ffi_constants.h"

#include "info_query.h"

/*
#include <gmock/gmock.h>

using ::testing::AllOf;
using ::testing::Gt;
using ::testing::Lt;
using ::testing::MatchesRegex;
using ::testing::StrEq;
*/


#if _WIN32
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

static int get_asset_path(char *buffer, size_t size, const char* filename) {
	//if (getcwd(buffer, size) == NULL){
	//	//getcwd error
	//	return 1;
	//}
	strcpy(buffer, getenv("ASSETPATH_CLIPSSCRIPTS"));
	strcat(buffer, PATH_SEPARATOR);
	strcat(buffer, "assets");
	strcat(buffer, PATH_SEPARATOR);
	if (filename != NULL){
		strcat(buffer, filename);
	}
	return 0;
}


TEST(BasicFactTest, BasicAssert){
	struct DynamicValue errval;
	const char subj[] = "_:n1234";
	const char pred[] = "<http://example.com/asdf#qwer>";
	const char obj[] = "\"asdf\"^^<qwer>";
	struct TriplesLinkedList *retFacts;
	crifi_graph* graph = init_graph();
	ASSERT_NE(graph, nullptr) << "Failed to initialize graph";
	CRI_RET_BUILDTRIPLE assert_fact_failed = assert_fact(graph, subj, pred, obj, "");
	EXPECT_EQ(assert_fact_failed, CRI_RET_BUILDTRIPLE_NOERROR) << "Couldnt assert fact.";
	retFacts = get_facts(graph, NULL, NULL, NULL);
	EXPECT_EQ(false, graph_in_errorstate(graph, stderr));
	if(graph_in_errorstate(graph, stderr)){
		eval(graph, "(println \"graph in errorstate: \" (get-error))");
		return;
	}

	ASSERT_NE(retFacts, nullptr) << "No fact returned.";
	EXPECT_STREQ(retFacts->subject, subj) << "wrong subject";
	EXPECT_STREQ(retFacts->predicate, pred) << "wrong predicate";
	EXPECT_STREQ(retFacts->object, obj) << "wrong object";
	free_linked_list(retFacts);
	close_graph(graph);
}


TEST(BasicFactTest, ParseTriplesMemory){
	const char subj[] = "_:n1234";
	const char pred[] = "<http://example.com/asdf#qwer>";
	const char obj[] = "\"äsdf\"^^<qwer>";
	char input[] = "_:n1234 <http://example.com/asdf#qwer> 'äsdf'^^<qwer> ." ;

	size_t l = sizeof(input);
	struct TriplesLinkedList *retFacts;
	crifi_graph* graph = init_graph();
	ASSERT_NE(graph, nullptr) << "Failed to initialize graph";
	RET_NTRIPLESPARSE err = ntriples_parse(graph, input, l, 0);
	ASSERT_NE(err, NTP_PARSE_ERROR) << "parsing ofinput file failed";
	ASSERT_NE(err, NTP_INTERNAL_ERROR) << "internal error";
	ASSERT_EQ(err, NTP_NO_ERROR) << "couldnt parse input triples.";

	retFacts = get_facts(graph, NULL, NULL, NULL);
	ASSERT_NE(retFacts, nullptr) << "no fact returned";
	EXPECT_STREQ(retFacts->subject, subj);
	EXPECT_STREQ(retFacts->predicate, pred);
	EXPECT_STREQ(retFacts->object, obj);
	free_linked_list(retFacts);
	close_graph(graph);
}

static RET_CRIFI_IMPORT test_import_function(crifi_graph *graph,
		ImportProcess *process, const char *import_location,
		CLIPSValue *values, int number_values, void *context){
	int *qq = (int*) context;

	*qq = 1;
	fprintf(stderr, "test_import_function\n");
	return RET_CRIFI_IMPORT_NOERROR;
}

TEST(BasicFactTest, TestImport){
	int qq = 0;
	struct DynamicValue retval;
	crifi_graph* graph = init_graph();
	int err = crifi_add_import_function(graph, test_import_function, &qq, NULL);
	switch (err){
		case 0:
			break;
		default:
			close_graph(graph);
			FAIL() << "unhandled error in "
				"crifi_add_import_function";
	}
	retval = eval(graph, "(<" _CRIFI_import_ "> <http://example.com/import> <" _RIFENTAIL_SIMPLE_ ">)");
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
			EXPECT_EQ(retval.val.boolean, true);
			break;
		default:
			FAIL() << "crifi:import return unexpected value.";
	}
	EXPECT_EQ(qq, 1) << "test_import_function wasnt executed.";
	close_graph(graph);
}


TEST(BasicFactTest, ParseNTriplesFile){
	FILE *inputptr;
	char inputPath[PATH_MAX];
	struct TriplesLinkedList *retFacts;
	crifi_graph* graph = init_graph();
	ASSERT_NE(graph, nullptr) << "Failed to initialize graph";
	char input[] = "#comment1\n"
		"_:n1234 <http://example.com/asdf#qwer> 'äsdf'^^<qwer> ." ;
	inputptr = fmemopen(input, sizeof(input), "r");

	//ASSERT_NE(inputptr, nullptr) << "couldnt open assets for test";
	RET_NTRIPLESPARSE err = ntriples_parse_f(graph, inputptr, 0);
	fclose(inputptr);
	ASSERT_NE(err, NTP_PARSE_ERROR) << "parsing ofinput file failed";
	ASSERT_NE(err, NTP_INTERNAL_ERROR) << "internal error";
	ASSERT_EQ(err, NTP_NO_ERROR) << "couldnt parse ntriples file.";

	retFacts = get_facts(graph, NULL, NULL, NULL);
	ASSERT_NE(retFacts, nullptr) << "no facts returned";
	EXPECT_STREQ(retFacts->subject, "_:n1234");
	EXPECT_STREQ(retFacts->predicate, "<http://example.com/asdf#qwer>");
	//algorithm returns literals with "
	EXPECT_STREQ(retFacts->object, "\"äsdf\"^^<qwer>");
	close_graph(graph);
	free_linked_list(retFacts);
}


