#include "crifi_raptor_interface.h"
#include "info_query.h"

raptor_term* clipsvalue_to_raptorterm(raptor_world *world, crifi_graph* graph, CLIPSValue val)
{
	raptor_term *retval;
	char *uri, *lexical, *lang, *datatype, *bnodeid;
	raptor_uri *dt_uri;
	if (clipsvalue_is_uri(graph, val)){
		uri = extract_uri(graph, val.header);
		retval = raptor_new_term_from_uri_string(world, uri);
		free(uri);
		return retval;
	} else if (clipsvalue_is_literal(graph, val)){
		lexical = extract_lexical(graph, val.header);
		lang = extract_lang(graph, val.header);
		if (lang != NULL){
			retval = raptor_new_term_from_literal(world, lexical,
								NULL, lang);
			free(lang);
		} else {
			datatype = extract_datatype(graph, val.header);
			if (datatype == NULL){
				free(lexical);
				return NULL;
			}
			dt_uri = raptor_new_uri(world, datatype);
			retval = raptor_new_term_from_literal(world, lexical,
								dt_uri, NULL);
			raptor_free_uri(dt_uri);
			free(datatype);
		}
		free(lexical);
		return retval;
	} else if (clipsvalue_is_bnode(graph, val)){
		bnodeid = extract_bnodeid(graph, val.header);
		retval = raptor_new_term_from_blank(world, bnodeid);
		free(bnodeid);
		return retval;
	}
	return NULL;
}
