/** \anchor BasicFactTest
 * For testing you have to provide the path to the assets:
 * eg: `env ASSETPATH_CLIPSSCRIPTS=path/to/assets ctest`
 */
#include <gtest/gtest.h>
#include <unistd.h>
#include <linux/limits.h>

#include <ffi_clips_interface.h>
#include <ntriplesParser.h>

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
	const char subj[] = "_:n1234";
	const char pred[] = "<http://example.com/asdf#qwer>";
	const char obj[] = "\"asdf\"^^<qwer>";
	struct TriplesLinkedList *retFacts;
	crifi_graph graph = init_graph();
	ASSERT_NE(graph, nullptr) << "Failed to initialize graph";
	CRI_RET_BUILDTRIPLE assert_fact_failed = assert_fact(graph, subj, pred, obj, "");
	EXPECT_EQ(assert_fact_failed, CRI_RET_BUILDTRIPLE_NOERROR) << "Couldnt assert fact.";
	retFacts = get_facts(graph, NULL, NULL, NULL);
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
	crifi_graph graph = init_graph();
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

TEST(BasicFactTest, ParseNTriplesFile){
	FILE *inputptr;
	char inputPath[PATH_MAX];
	struct TriplesLinkedList *retFacts;
	crifi_graph graph = init_graph();
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


