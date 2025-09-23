
set(PREFIX_TESTDATA_W3C_IMPORT
	"http://www.w3.org/2005/rules/test/repository/tc/")
set(PREFIX_TESTDATA_OWN_IMPORT
	"http://white.gobo/crifi/owntestdata/")
set(TESTDATA_W3C_AS_HEADER
	"${CMAKE_CURRENT_BINARY_DIR}/testdata_w3c_as_header.h")

list(APPEND targetendings "-conclusion" "-premise" "-import001" "-nonconclusion" "-input")
list(APPEND rdfformats "ttl" "ntriples")


#find_file(qq "AssertRetract-conclusion.ntriples" HINTS "${CMAKE_CURRENT_SOURCE_DIR}/data/" NO_CACHE)
#set(qq1 "${qq}")
#set(qq)
#find_file(qq "Arbitrary_Entailment-conclusion.ntriples" HINTS "${CMAKE_CURRENT_SOURCE_DIR}/data/" NO_CACHE)
#set(qq2 "${qq}")

list(APPEND owntargets
	openlist_as_pattern
	stacked_conditionals1
	circular_patterns1
	circular_patterns2
	compile_execute
	Assert2
	Assert3
	Assert4
	Assert5
	assign_var1
	assign_var2
	assign_var3
	assign_var4
	assign_var5
	assign_var6
	assign_var7
	assign_var8
	assign_var9
	assign_var10
	assign_var11
	failed_assign_var1
	failed_assign_var2
	PRD_priority1
	PRD_priority2
	Membership
	Subclass
	actionvar1
	actionvar2
)

foreach(base ${owntargets})
	foreach(ending ${targetendings})
		unset(targetfile)
		set(targeturi "${PREFIX_TESTDATA_OWN_IMPORT}${base}/${base}${ending}")
		foreach(fmt ${rdfformats})
			set(targetfilename "${base}${ending}.${fmt}")
			find_file(targetfile "${targetfilename}" HINTS "owntestdata/" NO_CACHE)
			if(targetfile)
				list(APPEND compilelist ${targeturi} ${targetfile})
				break()
			endif()
		endforeach()
	endforeach()
endforeach()

list(APPEND w3ctargets
	AssertRetract
	Arbitrary_Entailment
	Assert
	AssertRetract2
	Builtin_literal-not-identical
	Builtins_Binary
	Builtins_List
	Builtins_Numeric
	Builtins_PlainLiteral
	Builtins_String
	Builtins_Time
	Builtins_XMLLiteral
	Builtins_anyURI
	Builtins_boolean
	Chaining_strategy_numeric-add_1
	Chaining_strategy_numeric-add_2
	Chaining_strategy_numeric-subtract_1
	Chaining_strategy_numeric-subtract_2
	Class_Membership
	Classification-inheritance-conclusion.ntriples
	Classification_non-inheritance-nonconclusion.ntriples
	Core_NonSafeness
	Core_NonSafeness_2
	Core_Safeness
	Core_Safeness_2
	Core_Safeness_3
	EBusiness_Contract
	ElementEqualityFromListEquality
	EntailEverything
	Equality_in_conclusion_1
	Equality_in_conclusion_2
	Equality_in_conclusion_3
	Equality_in_condition
	Factorial_Forward_Chaining
	Factorial_Functional
	Factorial_Relational
	Frame_slots_are_independent
	Frames
	Guards_and_subtypes
	IRI_from_IRI
	Inconsistent_Entailment
	Individual-Data_Separation_Inconsistency
	ListConstantEquality
	ListEqualityFromElementEquality
	ListLiteralEquality
	Local_Constant
	Local_Predicate
	Modeling_Brain_Anatomy
	Modify
	Modify_loop
	Multiple_Context_Error
	Multiple_IRIs_from_String
	Multiple_Strings_from_IRI
	Named_Argument_Uniterms_non-polymorphic
	Named_Arguments
	NestedListsAreNotFlatLists
	No_free_variables
	Non-Annotation_Entailment
	OWL_Combination_Invalid_DL_Formula
	OWL_Combination_Invalid_DL_Import
	OWL_Combination_Vocabulary_Separation_Inconsistency_1
	OWL_Combination_Vocabulary_Separation_Inconsistency_1
	OWL_Combination_Vocabulary_Separation_Inconsistency_2
	OpenLists
	Positional_Arguments
	RDF_Combination_Blank_Node
	RDF_Combination_Constant_Equivalence_1
	RDF_Combination_Constant_Equivalence_2
	RDF_Combination_Constant_Equivalence_3
	RDF_Combination_Constant_Equivalence_4
	RDF_Combination_Constant_Equivalence_Graph_Entailment
	RDF_Combination_Invalid_Constant_1
	RDF_Combination_Invalid_Constant_2
	RDF_Combination_Invalid_Profiles_1
	RDF_Combination_Member_1
	RDF_Combination_SubClass
	RDF_Combination_SubClass_2
	RDF_Combination_SubClass_3
	RDF_Combination_SubClass_4
	RDF_Combination_SubClass_5
	RDF_Combination_SubClass_6
	Retract
	YoungParentDiscount_1
)

#set(compilelist)
#list(APPEND targetendings "-conclusion.ntriples" "-premise.ntriples" "-import001.ntriples" "-nonconclusion.ntriples" "-input.ntriples" "-conclusion.ttl" "-premise.ttl")
#list(APPEND targetendings "-conclusion" "-premise" "-import001" "-nonconclusion" "-input")
#list(APPEND rdfformats "ttl" "ntriples")
foreach(base ${w3ctargets})
	foreach(ending ${targetendings})
		unset(targetfile)
		set(targeturi "${PREFIX_TESTDATA_W3C_IMPORT}${base}/${base}${ending}")
		foreach(fmt ${rdfformats})
			set(targetfilename "${base}${ending}.${fmt}")
			find_file(targetfile "${targetfilename}" HINTS "data/" NO_CACHE)
			if(targetfile)
				list(APPEND compilelist ${targeturi} ${targetfile})
				break()
			endif()
		endforeach()
	endforeach()
endforeach()
compile_resources(w3ctestcases ${TESTDATA_W3C_AS_HEADER}
	FUNCTIONNAME "w3ctestcases_add_importlocations"
	TARGETS ${compilelist})

add_executable(w3c_tests
	builtins_model_test.cc
	testcases2_test.cc
	graph_generation_test.cc
	model_support.h
	model_support.c
	${TESTDATA_W3C_AS_HEADER}
)

target_link_libraries(w3c_tests PRIVATE
	GTest::gtest_main
	ffi_clips_interface
	crifi_import_implementations
	crifi_graph_models
	crifi_raptor
)

target_include_directories(w3c_tests PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

include(GoogleTest)
gtest_discover_tests(w3c_tests)
