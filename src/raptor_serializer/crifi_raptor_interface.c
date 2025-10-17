#include "crifi_raptor_interface.h"
#include "info_query.h"
#include "ffi_constants.h"

static raptor_term* qq_cv_uri(raptor_world *world, crifi_graph* graph, CLIPSValue val){
	raptor_term *retval;
	char *uri = extract_uri(graph, val.header);
	retval = raptor_new_term_from_uri_string(world, uri);
	free(uri);
	return retval;
}

static raptor_term* qq_cv_literal(raptor_world *world, crifi_graph* graph, CLIPSValue val){
	raptor_term *retval = NULL;
	char *uri, *lexical, *lang, *datatype, *bnodeid;
	raptor_uri *dt_uri;
	lexical = extract_lexical(graph, val.header);
	if (lexical == NULL){
		return NULL;
	}
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
	return retval;
}

static raptor_term* qq_cv_bnode(raptor_world *world, crifi_graph* graph, CLIPSValue val){
	raptor_term *retval = NULL;
	char *uri, *lexical, *lang, *datatype, *bnodeid;
	raptor_uri *dt_uri;
	bnodeid = extract_bnodeid(graph, val.header);
	if (bnodeid == NULL){
		return NULL;
	}
	retval = raptor_new_term_from_blank(world, bnodeid);
	free(bnodeid);
	return retval;
}

raptor_term* clipsvalue_to_raptorterm(raptor_world *world, crifi_graph* graph, CLIPSValue val)
{
	raptor_term *retval = NULL;
	char *uri, *lexical, *lang, *datatype, *bnodeid;
	raptor_uri *dt_uri;
	if (clipsvalue_is_uri(graph, val)){
		retval = qq_cv_uri(world, graph, val);
	} else if (clipsvalue_is_literal(graph, val)){
		retval = qq_cv_literal(world, graph, val);
	} else if (clipsvalue_is_bnode(graph, val)){
		retval = qq_cv_bnode(world, graph, val);
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
			raptor_free_term(retval);
			return NULL;
	}
}
