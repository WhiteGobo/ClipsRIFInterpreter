#include "crifi_utilities.h"

void print_activities_per_rule(crifi_graph* graph){
	CLIPSValue tmpval;
	const char* rulename;
	for(Defrule* rule = GetNextDefrule(graph, NULL);
			rule = GetNextDefrule(graph, rule);
			rule != NULL)
	{
		rulename = DefruleName(rule);
		Write(graph, rulename);
		Write(graph, ": ");
		Matches(rule, TERSE, &tmpval);
		WriteCLIPSValue(graph, STDOUT, &tmpval);
		Writeln(graph, "");
	}

}
