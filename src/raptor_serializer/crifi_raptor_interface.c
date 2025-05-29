#include "crifi_raptor_interface.h"
#include "info_query.h"
#include "ffi_constants.h"

raptor_term* clipsvalue_to_raptorterm(raptor_world *world, crifi_graph* graph, CLIPSValue val)
{
	//fprintf(stderr, "clipsvalue_to_raptorterm\n");
	raptor_term *retval = NULL;
	char *uri, *lexical, *lang, *datatype, *bnodeid;
	raptor_uri *dt_uri;
	if (clipsvalue_is_uri(graph, val)){
		//fprintf(stderr, "is uri\n");
		uri = extract_uri(graph, val.header);
		retval = raptor_new_term_from_uri_string(world, uri);
		free(uri);
	} else if (clipsvalue_is_literal(graph, val)){
		//fprintf(stderr, "is literal\n");
		lexical = extract_lexical(graph, val.header);
		if (lexical == NULL){
			//fprintf(stderr, "fail1\n");
			return NULL;
		}
		lang = extract_lang(graph, val.header);
		if (lang != NULL){
			//fprintf(stderr, "lang\n");
			retval = raptor_new_term_from_literal(world, lexical,
								NULL, lang);
			free(lang);
		} else {
			//fprintf(stderr, "datatype\n");
			datatype = extract_datatype(graph, val.header);
			if (datatype == NULL){
				free(lexical);
				return NULL;
			}
			if (0 == strcmp(datatype, _XS_string_)){
				dt_uri = NULL;
			} else {
				dt_uri = raptor_new_uri(world, datatype);
			}
			retval = raptor_new_term_from_literal(world, lexical,
								dt_uri, NULL);
			raptor_free_uri(dt_uri);
			free(datatype);
		}
		free(lexical);
	} else if (clipsvalue_is_bnode(graph, val)){
		//fprintf(stderr, "is bnode\n");
		bnodeid = extract_bnodeid(graph, val.header);
		if (bnodeid == NULL){
			//fprintf(stderr, "failed to generate bnode\n");
			return NULL;
		}
		//fprintf(stderr, "brubru %s\n", bnodeid);
		retval = raptor_new_term_from_blank(world, bnodeid);
		free(bnodeid);
	}
	if (retval == NULL) {
		return NULL;
	}
	switch(retval->type){
		case RAPTOR_TERM_TYPE_URI:
		case RAPTOR_TERM_TYPE_LITERAL:
		case RAPTOR_TERM_TYPE_BLANK:
			return retval;
		default:
			return NULL;
	}
}
