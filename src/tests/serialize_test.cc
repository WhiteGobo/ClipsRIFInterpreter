#include <gtest/gtest.h>
#include <ffi_clips_interface.h>
#include <raptor_serializer.h>
#include <crifi_raptor.h>

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
	close_graph(graph);
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
}

static char* RaptorParseExample = ""
"@prefix ex: <http://example.com/>.\n"
"[] ex:a \"asdf\" ;\n"
"\t ex:b \"qwer\" .\n";

TEST(SerializingTest, RaptorParse){
	CRIFI_PARSE_RET err;
	crifi_graph* graph = init_graph();
	FILE *source;
       
	source = fmemopen(RaptorParseExample, strlen(RaptorParseExample), "r");
	
	err = crifi_parse_to_triples(graph, source, "turtle", "http://example.com/");
	fclose(source); source = NULL;
	switch(err){
		case CRIFI_PARSE_NOERROR:
			break;
		case CRIFI_PARSE_INITERROR:
			close_graph(graph);
			FAIL() << "Initialization of raptor framework failed.";
		case CRIFI_PARSE_BASEERROR:
			close_graph(graph);
			FAIL() << "Couldnt parse given base as uri.";
		case CRIFI_PARSE_TERM_CONVERT:
			close_graph(graph);
			FAIL() << "Couldnt convert some term to clipsvalue.";
		case CRIFI_PARSE_UNKNOWN:
			close_graph(graph);
			FAIL() << "undescribed error";
		default:
			close_graph(graph);
			FAIL() << "unhandled error";
	}
	//ignore if succesful. just for debugging purposes.
	eval(graph, "(facts)");
	crifi_serialize_all_triples(graph, stdout, "turtle", "");
	close_graph(graph);
	//FAIL() << "success";
}

static char* RDFClipsScript = ""
"@prefix cs: <http://clips.script/>.\n"
"_:rule2 a cs:Defrule ;\n"
"    cs:rule-name \"myrule\" ;\n"
"    cs:conditional-element (<pattern1>) ;\n"
"    cs:action (_:funcA) .\n"
"_:rule1 a cs:Deffact ;\n"
"    cs:rule-name \"myfacts\" .\n"
"<pattern1> a cs:TemplatePatternCE ;\n"
"    cs:deftemplate-name \"TripleTemplate\";"
"    cs:slot (\n"
"        [cs:slot-name \"subject\"; cs:constraint _:varA]\n"
"        [cs:slot-name \"predicate\"; cs:constraints (_:literalA)]\n"
"        [cs:slot-name \"object\"; cs:constraint cs:SingleWildcard]\n"
"    ).\n"
"_:varA cs:variable-name \"a\".\n"
"_:uriA cs:symbol \"<http://example.com/a>\".\n"
"_:literalA cs:string \"string^^http://example.com/dt\".\n"
"_:funcA cs:function-name \"myfunc\" ;\n"
"	cs:function-args (_:varA _:uriA).\n"
;

TEST(SerializingTest, ClipsScript){
	CRIFI_PARSE_RET err;
	crifi_graph* graph = init_graph();
	FILE *source;
       
	source = fmemopen(RDFClipsScript, strlen(RDFClipsScript), "r");
	
	err = crifi_parse_to_triples(graph, source, "turtle", "http://example.com/");
	fclose(source); source = NULL;

	if (err != CRIFI_PARSE_NOERROR){
		GTEST_SKIP() << "Couldnt parse turtle";
	}

	//working
	int ctrl = serialize_information_as_clips_script(stdout, graph);
	close_graph(graph);
	switch (ctrl){
		case CRIFI_SERIALIZE_SCRIPT_NOERROR:
			break;
		case CRIFI_SERIALIZE_BROKEN_GRAPH:
			FAIL() << "Broken Graph";
		case CRIFI_SERIALIZE_MALLOC_ERROR:
			FAIL() << "Malloc error";
		case CRIFI_SERIALIZE_SCRIPT_INPUT:
			FAIL() << "Input has void pointer.";
		case CRIFI_SERIALIZE_SCRIPT_CANT_CREATE_NODE:
			FAIL() << "Cant malloc new node.";
		case CRIFI_SERIALIZE_SCRIPT_CANT_CREATE_STRUCTS:
			FAIL() << "Initialization problem.";
		case CRIFI_SERIALIZE_SCRIPT_UNHANDLED_PREDICATE:
			FAIL() << "didnt recognize a predicate";
		case CRIFI_SERIALIZE_SCRIPT_SUBJECT:
			FAIL() << "failed getting raptor term from subject";
		case CRIFI_SERIALIZE_SCRIPT_PREDICATE:
			FAIL() << "failed getting raptor term from predicate";
		case CRIFI_SERIALIZE_SCRIPT_OBJECT:
			FAIL() << "failed getting raptor term from object";
		case CRIFI_SERIALIZE_SCRIPT_FAILED_ADDING_NEW_NODE:
			FAIL() << "Failed adding new node.";
		case CRIFI_SERIALIZE_SCRIPT_UNKNOWN:
		default:
			FAIL() << "unhandled error";
	}
	//FAIL() << "success";
}
