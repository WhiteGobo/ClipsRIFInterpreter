#include <gtest/gtest.h>
#include "crifi_graph_models.h"

TEST(BuiltinModelTest, LoadModelA){
	crifi_graph *create_logic_graph = init_graph_modelA();
	close_graph(create_logic_graph);
	if (create_logic_graph == NULL){
		FAIL() << "Failed to create modelA";
	}
}
