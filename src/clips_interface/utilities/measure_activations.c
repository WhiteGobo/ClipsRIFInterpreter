#include "crifi_utilities.h"

void fprint_activities_per_rule(FILE* out, crifi_graph* graph){
	CLIPSValue tmpval;
	const char* rulename;
	long long activations;
	long long matches_pattern, matches_partial;
	long long total_points = 0;
	Multifield *tmpmulti;
	CLIPSInteger *tmpclipsint;
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
		if (tmpmulti->length != 3){
			continue;
		}
        	switch (tmpmulti->contents[0].header->type) {
			case INTEGER_TYPE:
				tmpclipsint = tmpmulti->contents[0].integerValue;
				matches_pattern = tmpclipsint->contents;
				break;
			default:
				continue;
		}
        	switch (tmpmulti->contents[1].header->type) {
			case INTEGER_TYPE:
				tmpclipsint = tmpmulti->contents[1].integerValue;
				matches_partial = tmpclipsint->contents;
				break;
			default:
				continue;
		}
		total_points += matches_pattern + matches_partial;
		fprintf(out, "%s: (%lld %lld)\n",
				rulename, matches_pattern, matches_partial);
	}
	fprintf(out, "total: %lld\n", total_points);

}
