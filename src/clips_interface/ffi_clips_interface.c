/** \file ffi_clips_interface.c
 * 
 */
#include "ffi_clips_interface.h"
#include "graph_engine.h"
#include "clips_to_interface.h"
#include <n3parser.h>



FFI_PLUGIN_EXPORT crifi_graph* init_graph(){
	crifi_graph* graph_container = initEnvironment();
	/*if (graph_container.environment == NULL){
		graph_container.inErrorState = 1;
	} else {
		graph_container.inErrorState = 0;
	}
	graph_container.extensions = NULL;
	*/
	return graph_container;
}

FFI_PLUGIN_EXPORT RET_LOADCONFIG load_config_mem(
		crifi_graph* graph,
		const char* configString, size_t lengthString){
	if (graph_in_errorstate(graph, NULL)){
		return CTC_LC_UNKNOWN_STATE;
	}
	bool success = load_config_internal_mem(
			graph,
			configString,
			lengthString);

	if (graph_in_errorstate(graph, NULL)){
		return CTC_LC_PARSING_ERROR;
	}
	if (success) {
		eval(graph, "(reset)");
		return CTC_LC_NO_ERROR;
	}
	return CTC_LC_PARSING_ERROR;
}

FFI_PLUGIN_EXPORT RET_LOADCONFIG load_config(crifi_graph* graph_container, char *configPath){
	LoadError lerr = load_config_internal(graph_container, configPath);
	if (graph_in_errorstate(graph_container, NULL)){
		return CTC_LC_PARSING_ERROR;
	}
	switch(lerr){
		case LE_NO_ERROR:
			eval(graph_container, "(reset)");
			return CTC_LC_NO_ERROR;
			break;
		case LE_OPEN_FILE_ERROR:
			return CTC_LC_OPEN_FILE_ERROR;
			break;
		case LE_PARSING_ERROR:
			return CTC_LC_PARSING_ERROR;
			break;
	}
	return CTC_LC_UNKNOWN_STATE;
}


FFI_PLUGIN_EXPORT struct TriplesLinkedList *get_facts(crifi_graph* graph_container, char *filter_subject, char *filter_predicate, char *filter_object){
	struct TriplesLinkedList *retFacts = NULL;
	CLIPSValue factsObj = getFactsFromEnvironment(graph_container);
	if (factsObj.header == NULL) return NULL;
	if (factsObj.header->type != MULTIFIELD_TYPE){
		return NULL;
	}
	retFacts = copy_getfacts_to_list(graph_container, factsObj.multifieldValue, filter_subject, filter_predicate, filter_object);

	return retFacts;
}


FFI_PLUGIN_EXPORT void close_graph(crifi_graph* graph_container){
	if (graph_container == NULL) return;
	closeEnvironment(graph_container);
	return;
}

static void qq1(struct TriplesLinkedList *current){
		free(current->subject);
}
static void qq2(struct TriplesLinkedList *current){
		free(current->predicate);
}
static void qq3(struct TriplesLinkedList *current){
		free(current->object);
}

FFI_PLUGIN_EXPORT void free_linked_list(struct TriplesLinkedList *first){
	struct TriplesLinkedList *current = first;
	struct TriplesLinkedList *rest;
	while(current != NULL){
		qq1(current);
		qq2(current);
		qq3(current);
		//free(current->subject);
		//free(current->predicate);
		//free(current->object);
		rest = current->rest;
		free(current);
		current = rest;
	}
}


FFI_PLUGIN_EXPORT struct TriplesLinkedList *append_triple(struct TriplesLinkedList *first, const Utf8String subject, const Utf8String predicate, const Utf8String object){
	struct TriplesLinkedList *last;
	struct TriplesLinkedList *new;
	char *tmp_s, *tmp_p, *tmp_o;
	new = (struct TriplesLinkedList *)\
	      malloc(sizeof(struct TriplesLinkedList));

	tmp_s = (char*) malloc((strlen(subject)+1)*sizeof(char));
	new->subject = tmp_s;
	strcpy(tmp_s, subject);
	tmp_p = (char*) malloc((strlen(predicate)+1)*sizeof(char));
	strcpy(tmp_p, predicate);
	new->predicate = tmp_p;
	tmp_o = (char*) malloc((strlen(object)+1)*sizeof(char));
	new->object = tmp_o;
	strcpy(tmp_o, object);
	new->rest = NULL;
	if (first != NULL){
		last = last_triple(first);
		last->rest = new;
	}
	return new;
}

FFI_PLUGIN_EXPORT int concatenate_triples(struct TriplesLinkedList *first, struct TriplesLinkedList *second){
	struct TriplesLinkedList *last;
	if (first == NULL || second == NULL) return 1;
	last = last_triple(first);
	last->rest = second;
	return 0;
}

FFI_PLUGIN_EXPORT struct TriplesLinkedList *last_triple(struct TriplesLinkedList *first){
	struct TriplesLinkedList *next;
	struct TriplesLinkedList *current = first;
	if (current == NULL) return NULL;
	next = current->rest;
	while (next != NULL){
		current = next;
		next = current->rest;
	}
	return current;
}

FFI_PLUGIN_EXPORT CRI_RET_BUILDTRIPLE assert_fact(
		crifi_graph* graph,
		const N3String subject, const N3String predicate,
		const N3String object, const char* context
		){
	CRI_RET_BUILDTRIPLE error = build_triple(graph, subject, predicate, object, context);
	return error;
}


FFI_PLUGIN_EXPORT long long run_rules(crifi_graph* graph, long long limit){
	return Run(graph, limit);
}

FFI_PLUGIN_EXPORT int build(crifi_graph* graph, Utf8String command){
	BuildError err = Build(graph, command);
	switch (err) {
		case BE_NO_ERROR:
			return 0;
		case BE_COULD_NOT_BUILD_ERROR:
			return 1;
		case BE_CONSTRUCT_NOT_FOUND_ERROR:
			return 2;
		case BE_PARSING_ERROR:
			return 3;
	}
}

static void fprint_dynamic_value(crifi_graph *graph, FILE* f, struct DynamicValue retval);

FFI_PLUGIN_EXPORT bool graph_in_errorstate(crifi_graph* graph, FILE* f){
	struct DynamicValue retval = eval(graph, "(get-error)");
	switch (retval.type){
		case CTC_DYNAMIC_BOOL:
			if (retval.val.boolean && (f != NULL)){
				fprintf(f, "graph in errorstate: ");
				fprint_dynamic_value(graph, f, retval);
				fprintf(f, "\n");
			}
			return retval.val.boolean;
		case CTC_DYNAMIC_STRING:
		case CTC_DYNAMIC_LIST:
		case CTC_DYNAMIC_ERROR:
		case CTC_DYNAMIC_VOID:
		case CTC_DYNAMIC_INT:
		default:
			if (f != NULL){
				fprintf(f, "graph in errorstate: ");
				fprint_dynamic_value(graph, f, retval);
				fprintf(f, "\n");
			}
			return true;
	}
}

FFI_PLUGIN_EXPORT struct DynamicValue eval(crifi_graph* graph, Utf8String command){
	CLIPSValue evalValue;
	struct DynamicValue ret;
	EvalError err = Eval(graph, command, &evalValue);
	switch (err) {
		case EE_PARSING_ERROR:
			ret.type = CTC_DYNAMIC_ERROR;
			ret.val.error = CTC_CTD_PARSING_ERROR;
			return ret;
		case EE_PROCESSING_ERROR:
			ret.type = CTC_DYNAMIC_ERROR;
			ret.val.error = CTC_CTD_PROCESSING_ERROR;
			return ret;
		case EE_NO_ERROR:
			break;
	}
	return clipsToDynamic(&evalValue);
}

FFI_PLUGIN_EXPORT void free_container(struct DynamicValue value){
	switch (value.type) {
		case CTC_DYNAMIC_VOID:
			free(value.val.content);
			break;
		case CTC_DYNAMIC_INT:
		case CTC_DYNAMIC_ERROR:
			break;
		case CTC_DYNAMIC_LIST:
			if (value.val.values != NULL){
				for (struct DynamicValue* v=value.val.values;
						v->type != CTC_DYNAMIC_VOID;
						v++){
					free_container(*v);
				}
				free(value.val.values);
			}
			break;
		case CTC_DYNAMIC_STRING:
			free(value.val.string);
			break;
	}
}

FFI_PLUGIN_EXPORT bool load_script(crifi_graph* graph, Utf8String script){
	return LoadFromString(graph, script, strlen(script));
}


FFI_PLUGIN_EXPORT void free_dynamic_value(struct DynamicValue val){
	switch (val.type) {
		case CTC_DYNAMIC_STRING:
			free(val.val.string);
			break;
	}
}

/*
FFI_PLUGIN_EXPORT void add_plugin(struct clips_graph_container *graph){
	CRIFIExtension *lastext = NULL;
	CRIFIExtension *newext;
	for (CRIFIExtension *tmpext = graph->extensions; tmpext != NULL; tmpext = tmpext->nextExtension){
		lastext = tmpext;
	}
	newext = malloc(sizeof(CRIFIExtension));
	if (lastext==NULL){
		graph->extensions = newext;
	} else {
		lastext->nextExtension = newext;
	}
}
*/

static void fprint_dynamic_value(crifi_graph *graph, FILE* f, struct DynamicValue retval){
	switch (retval.type){
		case CTC_DYNAMIC_ERROR:
			fprintf(f, "(not implemented clipsvaluetype)");
			break;
		case CTC_DYNAMIC_LIST:
			fprintf(f, "[");
			if (retval.val.values != NULL){
				for (struct DynamicValue* v=retval.val.values;
						v->type != CTC_DYNAMIC_VOID;
						v++){
					fprint_dynamic_value(graph, f, *v);
					fprintf(f, ", ");
				}
			}
			fprintf(f, "]");
			break;
		case CTC_DYNAMIC_STRING:
			fprintf(f, "%s", retval.val.string);
			break;
		case CTC_DYNAMIC_BOOL:
			if (retval.val.boolean){
				fprintf(f, "true");
			} else {
				fprintf(f, "false");
			}
			break;
		case CTC_DYNAMIC_VOID:
			fprintf(f, "void");
			break;
		case CTC_DYNAMIC_INT:
			fprintf(f, "%d", retval.val.integer);
			break;
		default:
			fprintf(f, "(unhandled type %d)", retval.type);
			break;
	}
}
