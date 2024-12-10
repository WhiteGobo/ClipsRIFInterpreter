/** \anchor testcases_test.cc
 * testcases like those from w3c rif testcases
 */

#include <gtest/gtest.h>
#include <unistd.h>
#include <linux/limits.h>
#include <filesystem>


#include <ffi_clips_interface.h>
#include <ntriplesParser.h>
#include <resource_manager.h>
#include <cmrc/cmrc.hpp>

#include "ffi_constants.h"

namespace fs = std::filesystem;
CMRC_DECLARE(crifi_test);

#if _WIN32
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

/*typedef struct testdata_ {
	const char* skip;
	const char* premisepath;
	const char* conclusionpath;
} TestdataPET;
*/
class TestdataPET {
	public:
		const char* skip;
		std::string premisepath;
		std::string conclusionpath;
		std::string name;
		TestdataPET(
				std::string Name,
				const char* myskip,
				std::string premisePath,
				std::string conclusionPath){
			if (myskip != NULL){
				skip = myskip;
			} else {
				skip = NULL;
			}
			premisepath = premisePath;
			conclusionpath = conclusionPath;
			name = Name;
		}
		TestdataPET(
				std::string Name,
				std::string premisePath,
				std::string conclusionPath){
			skip = NULL;
			premisepath = premisePath;
			conclusionpath = conclusionPath;
			name = Name;
		}
};

std::ostream& operator<<(std::ostream& os, const TestdataPET& td){
	os << td.name;
	return os;
}

static auto petTestdata = testing::Values(
		TestdataPET("Core_PET_Builtin_literal-not-identical",
			"Builtin_literal-not-identical-premise.ntriples",
			"Builtin_literal-not-identical-conclusion.ntriples"),
		TestdataPET("Core_PET_Builtins_Binary",
			"not implemented",
			"Builtins_Binary-premise.ntriples",
			"PET_Builtins_Binary-conclusion.ntriples"),
		TestdataPET("Core_PET_Builtins_List",
			"Builtins_List-premise.ntriples",
			"Builtins_List-conclusion.ntriples"),
		TestdataPET("Core_PET_Builtins_Numeric",
			"Builtins_Numeric-premise.ntriples",
			"Builtins_Numeric-conclusion.ntriples"),
		TestdataPET("Core_PET_Builtins_PlainLiteral",
			"not implemented",
			"Builtins_PlainLiteral-premise.ntriples",
			"Builtins_PlainLiteral-conclusion.ntriples"),
		TestdataPET("Core_PET_Builtins_String",
			"not implemented",
			"Builtins_String-premise.ntriples",
			"Builtins_String-conclusion.ntriples"),
		TestdataPET("Core_PET_Builtins_Time",
			"not implemented",
			"Builtins_Time-premise.ntriples",
			"Builtins_Time-conclusion.ntriples"),
		TestdataPET("Core_PET_Builtins_XMLLiteral",
			"not implemented",
			"Builtins_XMLLiteral-premise.ntriples",
			"Builtins_XMLLiteral-conclusion.ntriples"),
		TestdataPET("Core_PET_Builtins_anyURI",
			"not implemented",
			"Builtins_anyURI-premise.ntriples",
			"Builtins_anyURI-conclusion.ntriples"),
		TestdataPET("Core_PET_Builtins_boolean",
			"not implemented",
			"Builtins_boolean-premise.ntriples",
			"Builtins_boolean-conclusion.ntriples"),
		TestdataPET("Core_PET_Chaining_strategy_numeric-add_1",
			"Chaining_strategy_numeric-add_1-premise.ntriples",
			"Chaining_strategy_numeric-add_1-conclusion.ntriples"),
		TestdataPET("Core_PET_Chaining_strategy_numeric-subtract_2",
			"Chaining_strategy_numeric-subtract_2-premise.ntriples",
			"Chaining_strategy_numeric-subtract_2-conclusion.ntriples"),
		TestdataPET("Core_PET_EBusiness_Contract",
			"not implemented",
			"EBusiness_Contract-premise.ntriples",
			"EBusiness_Contract-conclusion.ntriples"),
		TestdataPET("Core_PET_Factorial_Forward_Chaining",
			"This needs better automatic rulecreation",
			"Factorial_Forward_Chaining-premise.ntriples",
			"Factorial_Forward_Chaining-conclusion.ntriples"),
		TestdataPET("Core_PET_Frame_slots_are_independent",
			"Frame_slots_are_independent-premise.ntriples",
			"Frame_slots_are_independent-conclusion.ntriples"),
		TestdataPET("Core_PET_Frames",
			"Frames-premise.ntriples",
			"Frames-conclusion.ntriples"),
		TestdataPET("Core_PET_Guards_and_subtypes",
			"Guards_and_subtypes-premise.ntriples",
			"Guards_and_subtypes-conclusion.ntriples"),
		TestdataPET("Core_PET_Modeling_Brain_Anatomy",
			"not implemented",
			"Modeling_Brain_Anatomy-premise.ntriples",
			"Modeling_Brain_Anatomy-conclusion.ntriples"),
		TestdataPET("Core_PET_OWL_Combination_Vocabulary_Separation_Inconsistency_1",
			"not implemented",
			"OWL_Combination_Vocabulary_Separation_Inconsistency_1-premise.ntriples",
			"OWL_Combination_Vocabulary_Separation_Inconsistency_1-conclusion.ntriples"),
		TestdataPET("Core_PET_OWL_Combination_Vocabulary_Separation_Inconsistency_2",
			"not implemented",
			"OWL_Combination_Vocabulary_Separation_Inconsistency_2-premise.ntriples", "OWL_Combination_Vocabulary_Separation_Inconsistency_2-conclusion.ntriples"),
		TestdataPET("Core_PET_Positional_Arguments",
			"Positional_Arguments-premise.ntriples",
			"Positional_Arguments-conclusion.ntriples"),
		TestdataPET("Core_PET_RDF_Combination_Blank_Node",
			"RDF_Combination_Blank_Node-premise.ntriples",
			"RDF_Combination_Blank_Node-conclusion.ntriples"),
		TestdataPET("Core_PET_RDF_Combination_Constant_Equivalence_1",
			"not implemented",
			"RDF_Combination_Constant_Equivalence_1-premise.ntriples",
			"RDF_Combination_Constant_Equivalence_1-conclusion.ntriples"),
		TestdataPET("Core_PET_RDF_Combination_Constant_Equivalence_2",
			"not implemented",
			"RDF_Combination_Constant_Equivalence_2-premise.ntriples",
			"RDF_Combination_Constant_Equivalence_2-conclusion.ntriples"),
		TestdataPET("Core_PET_RDF_Combination_Constant_Equivalence_3",
			"not implemented",
			"RDF_Combination_Constant_Equivalence_3-premise.ntriples",
			"RDF_Combination_Constant_Equivalence_3-conclusion.ntriples"),
		TestdataPET("Core_PET_RDF_Combination_Constant_Equivalence_4",
				"not implemented",
				"RDF_Combination_Constant_Equivalence_4-premise.ntriples", "RDF_Combination_Constant_Equivalence_4-conclusion.ntriples"),
		TestdataPET("Core_PET_RDF_Combination_Constant_Equivalence_Graph_Entailment",
				"not implemented",
				"RDF_Combination_Constant_Equivalence_Graph_Entailment-premise.ntriples", "RDF_Combination_Constant_Equivalence_Graph_Entailment-conclusion.ntriples"),
		TestdataPET("Core_PET_RDF_Combination_SubClass_2",
				"not implemented",
				"RDF_Combination_SubClass_2-premise.ntriples", "RDF_Combination_SubClass_2-conclusion.ntriples"),
		TestdataPET("BLD_PET_Chaining_strategy_numeric-add_2",
				"not implemented",
				"Chaining_strategy_numeric-add_2-premise.ntriples", "Chaining_strategy_numeric-add_2-conclusion.ntriples"),
		TestdataPET("BLD_PET_Chaining_strategy_numeric-subtract_1",
				"not implemented",
				"Chaining_strategy_numeric-subtract_1-premise.ntriples", "Chaining_strategy_numeric-subtract_1-conclusion.ntriples"),
		TestdataPET("BLD_PET_Class_Membership",
				"not implemented",
				"Class_Membership-premise.ntriples", "Class_Membership-conclusion.ntriples"),
		TestdataPET("BLD_PET_Classification-inheritance",
				"not implemented",
				"Classification-inheritance-premise.ntriples", "Classification-inheritance-conclusion.ntriples"),
		TestdataPET("BLD_PET_ElementEqualityFromListEquality",
				"not implemented",
				"ElementEqualityFromListEquality-premise.ntriples", "ElementEqualityFromListEquality-conclusion.ntriples"),
		TestdataPET("BLD_PET_EntailEverything",
				"not implemented",
				"EntailEverything-premise.ntriples", "EntailEverything-conclusion.ntriples"),
		TestdataPET("BLD_PET_Equality_in_conclusion_1",
				"not implemented",
				"Equality_in_conclusion_1-premise.ntriples", "Equality_in_conclusion_1-conclusion.ntriples"),
		TestdataPET("BLD_PET_Equality_in_conclusion_2",
				"not implemented",
				"Equality_in_conclusion_2-premise.ntriples", "Equality_in_conclusion_2-conclusion.ntriples"),
		TestdataPET("BLD_PET_Equality_in_conclusion_3",
				"not implemented",
				"Equality_in_conclusion_3-premise.ntriples", "Equality_in_conclusion_3-conclusion.ntriples"),
		TestdataPET("BLD_PET_Equality_in_condition",
				"not implemented",
				"Equality_in_condition-premise.ntriples", "Equality_in_condition-conclusion.ntriples"),
		TestdataPET("BLD_PET_Factorial_Functional",
				"not implemented",
				"Factorial_Functional-premise.ntriples", "Factorial_Functional-conclusion.ntriples"),
		TestdataPET("BLD_PET_Factorial_Relational",
				"not implemented",
				"Factorial_Relational-premise.ntriples", "Factorial_Relational-conclusion.ntriples"),
		TestdataPET("BLD_PET_IRI_from_IRI",
				"not implemented",
				"IRI_from_IRI-premise.ntriples", "IRI_from_IRI-conclusion.ntriples"),
		TestdataPET("BLD_PET_Inconsistent_Entailment",
				"not implemented",
				"Inconsistent_Entailment-premise.ntriples", "Inconsistent_Entailment-conclusion.ntriples"),
		TestdataPET("BLD_PET_Individual-Data_Separation_Inconsistency",
				"not implemented",
				"Individual-Data_Separation_Inconsistency-premise.ntriples", "Individual-Data_Separation_Inconsistency-conclusion.ntriples"),
		TestdataPET("BLD_PET_ListConstantEquality",
				"not implemented",
				"ListConstantEquality-premise.ntriples", "ListConstantEquality-conclusion.ntriples"),
		TestdataPET("BLD_PET_ListEqualityFromElementEquality",
				"not implemented",
				"ListEqualityFromElementEquality-premise.ntriples", "ListEqualityFromElementEquality-conclusion.ntriples"),
		TestdataPET("BLD_PET_ListLiteralEquality",
				"not implemented",
				"ListLiteralEquality-premise.ntriples", "ListLiteralEquality-conclusion.ntriples"),
		TestdataPET("BLD_PET_Arbitrary_Entailment",
				"not implemented",
				"Arbitrary_Entailment-premise.ntriples", "Arbitrary_Entailment-conclusion.ntriples"),
		TestdataPET("BLD_PET_Multiple_IRIs_from_String",
				"not implemented",
				"Multiple_IRIs_from_String-premise.ntriples",
				"Multiple_IRIs_from_String-conclusion.ntriples"),
		TestdataPET("BLD_PET_Multiple_Strings_from_IRI",
				"not implemented",
				"Multiple_Strings_from_IRI-premise.ntriples",
				"Multiple_Strings_from_IRI-conclusion.ntriples"),
		TestdataPET("BLD_PET_Named_Arguments",
				"not implemented",
				"Named_Arguments-premise.ntriples",
				"Named_Arguments-conclusion.ntriples"),
		TestdataPET("BLD_PET_RDF_Combination_Member_1",
				"not implemented",
				"RDF_Combination_Member_1-premise.ntriples",
				"RDF_Combination_Member_1-conclusion.ntriples"),
		TestdataPET("BLD_PET_RDF_Combination_SubClass_4",
				"not implemented",
				"RDF_Combination_SubClass_4-premise.ntriples",
				"RDF_Combination_SubClass_4-conclusion.ntriples"),
		TestdataPET("BLD_PET_RDF_Combination_SubClass_6",
				"not implemented",
				"RDF_Combination_SubClass_6-premise.ntriples",
				"RDF_Combination_SubClass_6-conclusion.ntriples"),
		TestdataPET("BLD_PET_YoungParentDiscount_1",
				"not implemented",
				"YoungParentDiscount_1-premise.ntriples",
				"YoungParentDiscount_1-conclusion.ntriples"),
		TestdataPET("PRD_PET_Assert_", //_ makes unique
				"Assert-premise.ntriples",
				"Assert-conclusion.ntriples"),
		TestdataPET("PRD_PET_AssertRetract",
				"AssertRetract-premise.ntriples",
				"AssertRetract-conclusion.ntriples"),
		TestdataPET("PRD_PET_AssertRetract2",
				"not implemented",
				"AssertRetract2-premise.ntriples",
				"AssertRetract2-conclusion.ntriples"),
		TestdataPET("PRD_PET_Modify1",
				"Modify-premise.ntriples",
				"Modify-conclusion.ntriples"),
		TestdataPET("PRD_PET_Modify_loop",
				"not implemented",
				"Modify_loop-premise.ntriples",
				"Modify_loop-conclusion.ntriples")
		);

//_CORE_NST=Core_NonSafeness Core_NonSafeness_2

//_CORE_PST=Core_Safeness Core_Safeness_2 Core_Safeness_3

//_CORE_NET=Local_Constant Local_Predicate NestedListsAreNotFlatLists Non-Annotation_Entailment RDF_Combination_SubClass

//_CORE_IRT=Multiple_Context_Error OWL_Combination_Invalid_DL_Formula OWL_Combination_Invalid_DL_Import RDF_Combination_Invalid_Constant_1 RDF_Combination_Invalid_Constant_2 RDF_Combination_Invalid_Profiles_1


//_BLD_NET=Classification_non-inheritance
/*
Named_Argument_Uniterms_non-polymorphic
OpenLists
RDF_Combination_SubClass_3
*/
//_BLD_NST=No_free_variables


//_PRD_NST=No_free_variables

//_PRD_NET=RDF_Combination_SubClass_5
//Retract


fs::path get_asset_path(const char* filename) {
	fs::path qq = fs::path("data");
	qq += PATH_SEPARATOR;
	qq += filename;
	return fs::absolute(qq);
}

class TestCasesTest : public testing::TestWithParam<TestdataPET> {
	protected:
		void SetUp() override {
			TestdataPET q = GetParam();
			if (q.skip != NULL) {
				GTEST_SKIP() << q.skip;
			}
		}
};

TEST_P(TestCasesTest, BasicPET) {
	struct clips_graph_container graph;
	graph = init_graph();
	std::string *logicAsString = nullptr;
	std::string *statementVerifierAsString = nullptr;
	RET_NTRIPLESPARSE parse_err;
	RET_LOADCONFIG script_err;
	TestdataPET q = GetParam();
	struct TriplesLinkedList *retFacts;
	FILE *premise_f;
	FILE *conclusion_f;
	//fs::path premisepath = get_asset_path(q.premisepath.c_str());
	//fs::path conclusionpath = get_asset_path(q.conclusionpath.c_str());
	//premise_f = fopen(premisepath.c_str(), "r");
	auto fs = cmrc::crifi_test::get_filesystem();
	cmrc::file asfile = fs.open(q.premisepath.c_str());
	//std::string premise_data = std::string(asfile.begin(), asfile.end());
	premise_f = fmemopen((char*) asfile.begin(), asfile.size(), "r");

	ASSERT_NE(premise_f, (void*) NULL)
		<< "broken test setup. missing premisefile";
	retFacts = ntriples_parse_triples_f(premise_f, 0);
	ASSERT_NE(retFacts, (void*) NULL)
			<< "no information for premise loaded";
	fclose(premise_f);
	fprintf(stderr, "generate rif logic\n");
	logicAsString = generate_rif_logic(retFacts);
	free_linked_list(retFacts);
	ASSERT_NE(logicAsString, nullptr);
	fprintf(stderr, "plain output logic:\n%s\n\n", logicAsString->c_str());

	//conclusion_f = fopen(conclusionpath.c_str(), "r");
	cmrc::file conc_mem = fs.open(q.conclusionpath.c_str());
	conclusion_f = fmemopen((char*) conc_mem.begin(), conc_mem.size(), "r");
	ASSERT_NE(conclusion_f, (void*) NULL) << "broken test setup. missing conc";
	retFacts = ntriples_parse_triples_f(conclusion_f, 0);
	fclose(conclusion_f);
	ASSERT_NE(retFacts, (void*) NULL)
			<< "no information for conclusion loaded";
	fprintf(stderr, "generate rif statement\n");
	statementVerifierAsString = generate_rif_statement(retFacts);
	free_linked_list(retFacts);
	ASSERT_NE(statementVerifierAsString, nullptr);
	ASSERT_NE(std::string::npos,
			statementVerifierAsString->find("check-statements"))
			<< "No check-statements declaration produced";
	fprintf(stderr, "plain output statement:\n%s\n\n",
					statementVerifierAsString->c_str());
	script_err = load_config_mem(graph, logicAsString->c_str(),
					logicAsString->length());
	EXPECT_NE(script_err, CTC_LC_PARSING_ERROR)
		<< "Failed parsing of produced logic";
	EXPECT_EQ(script_err, 0) << "failed to load produced logic into clips";
	script_err = load_config_mem(graph, statementVerifierAsString->c_str(),
					statementVerifierAsString->length());
	EXPECT_NE(script_err, CTC_LC_PARSING_ERROR)
		<< "Failed parsing of statement";
	EXPECT_EQ(script_err, 0)
		<< "failed to load produced statement into clips";
	//eval(graph, "(watch all)");
	eval(graph, "(watch activations <http://white.gobo/success>)");
	//eval(graph, "(watch all <http://white.gobo/success>)");
	int numberExecutions = run_rules(graph, 100);
	printf("Number of rules, that have ran in resulting graph: %d\n",
			numberExecutions);
	auto qq = eval(graph, "(get-error)");
	EXPECT_EQ(qq.type, CTC_DYNAMIC_BOOL);
	if (qq.type != CTC_DYNAMIC_BOOL){
		printf("Graph resulted in errorstate\n");
		if (qq.type == CTC_DYNAMIC_STRING){
			printf("%s\n", qq.val.string);
		}
		return;
	} else {
		ASSERT_EQ(false, qq.val.boolean)\
			<< "graph resulted in errorstate";
	}
	free_dynamic_value(qq);
	bool success = check_statements(graph);

	EXPECT_EQ(true, success);
	printf("run (facts):\n");
	eval(graph, "(facts)");
	eval(graph, "(matches <" _CRIFI_success_ ">)");
	close_graph(graph);
	delete(statementVerifierAsString);
	delete(logicAsString);

	//struct clips_graph_container graph = init_graph();
	//RET_NTRIPLESPARSE err = ntriples_parse_f(&graph, inputptr);
}


INSTANTIATE_TEST_SUITE_P(
		MeenyMinyMoe,
		TestCasesTest,
		petTestdata);
