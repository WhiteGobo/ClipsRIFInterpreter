#include <gtest/gtest.h>
#include <unistd.h>
#include <linux/limits.h>
#include "ffi_constants.h"
#include <ffi_clips_interface.h>

#include "helper.h"

TEST(ExternalFunctionsSystem, SetGraphInErrorstate){
	const char *command = "(<" _CRIFI_set_graph_in_errorstate_ "> \"Errordescription\" )";
	crifi_graph* graph = init_graph();
	if (graph == NULL){
		GTEST_SKIP() << "couldnt init graph";
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
		default:
			//Dont expect any specific output
			break;
	}
	if (!errorstate){
		FAIL() << "graph didnt end up in errorstate after: " << command;
	}
}
