#include "helper.h"


void check_command_true(const char* command){
	crifi_graph* graph = init_graph();
	if (graph == NULL){
		FAIL() << "couldnt init graph";
	}
	bool errorstate;
	struct DynamicValue retval;
	retval = eval(graph, command);
	errorstate = graph_in_errorstate(graph, stderr);
	close_graph(graph);
	switch (retval.type){
		case CTC_DYNAMIC_ERROR:
			switch (retval.val.error){
				case CTC_CTD_PARSING_ERROR:
					FAIL() << "Parsing error. Used: "
						<< command;
				case CTC_CTD_PROCESSING_ERROR:
					FAIL() << "Processing error. Used: "
						<< command;
				case CTC_CTD_CANTTRANSLATE:
					FAIL() << "Cant process returned "
						"CLIPSValue to DynamicType. "
						"Used: " << command;
				default:
					FAIL() << "eval returned unhandled "
						"error. Used: " << command;
			}
			break;
		case CTC_DYNAMIC_BOOL:
			ASSERT_EQ(retval.val.boolean, true)
				<< "Command returned false. Used:\n"
				<< command;
			break;
		default:
			FAIL() << "command returned unexpected value. "
				"Expected bool. Used: "
				<< command;
	}
	if (errorstate){
		FAIL() << "graph ended up in errorstate after import\n";
	}
}

void fprintf_command_result(FILE *f, const char *command){
	crifi_graph *graph = init_graph();
	if (graph == NULL){
		FAIL() << "couldnt init empty graph.";
	}
	bool errorstate;
	struct DynamicValue retval;
	retval = eval(graph, command);
	errorstate = graph_in_errorstate(graph, stderr);
	switch (retval.type){
		case CTC_DYNAMIC_ERROR:
			switch (retval.val.error){
				case CTC_CTD_PARSING_ERROR:
					FAIL() << "Parsing error. Used: "
						<< command;
				case CTC_CTD_PROCESSING_ERROR:
					FAIL() << "Processing error. Used: "
						<< command;
				case CTC_CTD_CANTTRANSLATE:
					FAIL() << "Cant process returned "
						"CLIPSValue to DynamicType. "
						"Used: " << command;
				default:
					FAIL() << "eval returned unhandled "
						"error. Used: " << command;
			}
			break;
		case CTC_DYNAMIC_STRING:
			fprintf(stderr, "Used command produced string.\n"
					"command: %s\noutput: %s\n",
					command, retval.val.string);
			break;
		case CTC_DYNAMIC_INT:
			fprintf(stderr, "Used command produced int %d.\n"
					"command: %s\n",
					retval.val.integer, command);
			break;
		case CTC_DYNAMIC_BOOL:
			if (retval.val.boolean){
				fprintf(stderr, "following command return "
						"TRUE:\n%s\n", command);
			} else {
				fprintf(stderr, "following command return "
						"FALSE:\n%s\n", command);
			}
			break;
		case CTC_DYNAMIC_LIST:
		default:
			free_dynamic_value(retval);
			FAIL() << "command returned unexpected value. Used: "
				<< command;
	}
	free_dynamic_value(retval);
	if (errorstate){
		FAIL() << "graph ended up in errorstate after eval. Used:\n"
			<< command;
	}
	close_graph(graph);
}
