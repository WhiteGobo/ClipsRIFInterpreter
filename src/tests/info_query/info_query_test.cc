/** \anchor InfoQueryTest
 */
#include <gtest/gtest.h>
#include <unistd.h>
#include <linux/limits.h>

#include <ffi_clips_interface.h>
#include "example_info_query.h"

#define EX(suffix) "<http://example.com/" suffix ">"
#define LITERAL(value) "\"" value "\""

TEST(InfoQueryTest, Example){
	const char *subj, *pred, *obj;
	CRI_RET_BUILDTRIPLE assert_err;
	const size_t l = 2;
	const char triples[l][3][30] = {
		{EX("node"), EX("prop1"), LITERAL("asdf")},
		{EX("node"), EX("prop2"), LITERAL("qwer")},
	};
	crifi_graph* graph = init_graph();
	for (int i=0; i<l; i++){
		subj = triples[i][0];
		pred = triples[i][1];
		obj = triples[i][2];
		assert_err = assert_fact(graph, subj, pred, obj, "");
		if(assert_err != CRI_RET_BUILDTRIPLE_NOERROR){
		       	GTEST_SKIP() << "Couldnt assert fact.";
		}
	}
	ASSERT_EQ(l, example_info_query(graph)) << "expected number of triples";
	close_graph(graph);
}
