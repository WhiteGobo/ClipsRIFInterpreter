#include <gtest/gtest.h>
#include <ffi_clips_interface.h>
#include <raptor_serializer.h>

#define EX(suffix) "<http://example.com/" suffix ">"
#define LITERAL(value) "\"" value "\""

TEST(SerializingTest, Basic){
	const char *subj, *pred, *obj;
	CRI_RET_BUILDTRIPLE assert_err;
	const size_t l = 2;
	const char triples[l][3][30] = {
		{EX("node"), EX("prop1"), LITERAL("asdf")},
		{EX("node"), EX("prop2"), LITERAL("qwer")},
	};
	crifi_graph* graph = init_graph();

	//init
	for (int i=0; i<l; i++){
		subj = triples[i][0];
		pred = triples[i][1];
		obj = triples[i][2];
		assert_err = assert_fact(graph, subj, pred, obj, "");
		if(assert_err != CRI_RET_BUILDTRIPLE_NOERROR){
		       	GTEST_SKIP() << "Couldnt assert fact.";
		}
	}

	//working
	int ctrl = crifi_serialize_all_triples(graph, stdout, "turtle", "");
	switch (ctrl){
		case CRIFI_SERIALIZE_NOERROR:
			break;
		case CRIFI_SERIALIZE_TERM:
			FAIL() << "Couldnt transform all terms";
		case CRIFI_SERIALIZE_MISSING_FORMAT:
		case CRIFI_SERIALIZE_MISSING_BASE:
			FAIL() << "Input error";
		default:
			FAIL() << "unhandled error";
	}
	close_graph(graph);
}
