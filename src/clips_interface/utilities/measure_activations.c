#include "crifi_utilities.h"

void fprint_activities_per_rule(FILE* out, crifi_graph* graph){
	CLIPSValue tmpval;
	const char* rulename;
	long long activations;
	long long total_activations = 0;
	Multifield *tmpmulti;
	CLIPSInteger *clipsactivations;
	for(Defrule* rule = GetNextDefrule(graph, NULL);
			rule = GetNextDefrule(graph, rule);
			rule != NULL)
	{
		rulename = DefruleName(rule);
		Matches(rule, TERSE, &tmpval);
        	switch (tmpval.header->type) {
			case MULTIFIELD_TYPE:
				break;
			default:
				continue;
		}
		tmpmulti = tmpval.multifieldValue;
		if (tmpmulti->length < 1){
			continue;
		}
        	switch (tmpmulti->contents[0].header->type) {
			case INTEGER_TYPE:
				clipsactivations = tmpmulti->contents[0].integerValue;
				activations = clipsactivations->contents;
				break;
			default:
				continue;
		}
		total_activations += activations;
		fprintf(out, "%s: %lld\n", rulename, activations);
	}
	fprintf(out, "total: %lld\n", rulename, total_activations);

}
