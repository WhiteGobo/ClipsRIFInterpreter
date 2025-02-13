#include "clips_script_serializer.h"
#include "raptor_serializer.h"
#include "info_query.h"
#include "crifi_raptor_interface.h"

#define EX(suffix) "http://example.com/" suffix
#define RDF(suffix) "http://example.com/" suffix

enum {
	SAT_NOERROR = 0,
	SAT_SUBJ,
	SAT_PRED,
	SAT_OBJ
};

typedef enum {
	uri,
	bnode
} IdType;

typedef struct {
	raptor_term *rdf_first;
	raptor_term *rdf_rest;
	raptor_term *rdf_nil;
	raptor_term *rdf_type;
	raptor_term *rdf_List;

	raptor_term *ex_prop1;
} MyContext;

typedef struct {
	raptor_term *id;

	//RDF:
	raptor_term *type;
	raptor_term *rest;
	raptor_term *first;

	//own:
	
	//multifield: raptor_sequence *;
	//single: raptor_term *;
} Node;

static int compare_nodes(const Node* n1, const Node* n2){
	if (n1 == NULL || n2 == NULL){
		return 0;
	}
	return raptor_term_compare(n1->id, n2->id);
}

static void free_node(const Node* n){
}

static Node *new_node(raptor_term *id){
	Node *ret = malloc(sizeof(Node));
	if (ret == NULL){
		return NULL;
	}
	ret->id = id;

	ret->type = NULL;
	ret->first = NULL;
	ret->rest = NULL;
	return ret;
}

static int add_predicate(MyContext *cntxt, Node *node, raptor_term *predicate, raptor_term *object){
	if (0 != raptor_term_equals(predicate, cntxt->rdf_rest)){
		node->rest = object;
		node->type = cntxt->rdf_List;
	} else if (0 != raptor_term_equals(predicate, cntxt->rdf_first)){
		node->first = object;
		node->type = cntxt->rdf_List;
	} else if (0 != raptor_term_equals(predicate, cntxt->rdf_type)){
		node->type = object;
	} else if (0 != raptor_term_equals(predicate, cntxt->ex_prop1)){
	} else {
		printf("couldnt identify predicate\n");
		return 0;
		return CRIFI_SERIALIZE_SCRIPT_UNHANDLED_PREDICATE;
	}
	return 0;
}

static int add_triple_to_nodes(MyContext *cntxt, raptor_avltree *tree, raptor_term *subject, raptor_term *predicate, raptor_term *object){
	int err;
	Node searcher = {.id = subject};
	Node *existing_node;
	existing_node = (Node*) raptor_avltree_search(tree, &searcher);
	if (existing_node == NULL){
		existing_node = new_node(subject);
		if (existing_node == NULL){
			return CRIFI_SERIALIZE_SCRIPT_CANT_CREATE_NODE;
		}
		err = raptor_avltree_add(tree, existing_node);
		if (0 != err){
			free_node(existing_node);
			return CRIFI_SERIALIZE_SCRIPT_FAILED_ADDING_NEW_NODE;
		}
	}
	err = add_predicate(cntxt, existing_node, predicate, object);
	if (0 != err){
		free_node(existing_node);
		return err;
	}
	return 0;
}

static int add_info_to_tree(raptor_world *world, crifi_graph *graph, raptor_avltree *tree, MyContext *cntxt){
	int err;
	if (world == NULL || tree == NULL || graph == NULL){
		return CRIFI_SERIALIZE_SCRIPT_CANT_CREATE_STRUCTS;
	}
	CLIPSValue tmpValue;
	raptor_statement *triple;
	raptor_term *subj, *pred, *obj;
	for(Fact *f = get_next_triple(graph, NULL);
			f != NULL;
			f = get_next_triple(graph, f))
	{
		GetFactSlot(f, TRIPLESLOTPREDICATE, &tmpValue);
		pred = clipsvalue_to_raptorterm(world, graph, tmpValue);
		if (pred == NULL){
			return CRIFI_SERIALIZE_SCRIPT_PREDICATE;
		}
		if (false){//supported_uri(pred, cntxt)
			raptor_free_term(pred);
			continue;
		}

		GetFactSlot(f, TRIPLESLOTSUBJECT, &tmpValue);
		subj = clipsvalue_to_raptorterm(world, graph, tmpValue);
		if (subj == NULL){
			raptor_free_term(pred);
			return CRIFI_SERIALIZE_SCRIPT_SUBJECT;
		}

		GetFactSlot(f, TRIPLESLOTOBJECT, &tmpValue);
		obj = clipsvalue_to_raptorterm(world, graph, tmpValue);
		if (obj == NULL){
			raptor_free_term(subj);
			raptor_free_term(pred);
			return CRIFI_SERIALIZE_SCRIPT_OBJECT;
		}
		//triple = raptor_new_statement_from_nodes(world,
		//					subj, pred, obj, NULL);

		err = add_triple_to_nodes(cntxt, tree, subj, pred, obj);
		if (err != 0){
			return err;
		}
		//raptor_serializer_serialize_statement(my_serializer, triple);
		//raptor_free_statement(triple);
	}
	return 0;
}

static MyContext* init_context(raptor_world *world){
	MyContext *cntxt = malloc(sizeof(MyContext));
	cntxt->rdf_type = raptor_new_term_from_uri_string(world, RDF("type"));
	cntxt->rdf_first = raptor_new_term_from_uri_string(world, RDF("first"));
	cntxt->rdf_rest = raptor_new_term_from_uri_string(world, RDF("rest"));
	cntxt->rdf_nil = raptor_new_term_from_uri_string(world, RDF("nil"));
	cntxt->ex_prop1 = raptor_new_term_from_uri_string(world, EX("prop1"));
	return cntxt;
}

static void free_context(MyContext* cntxt){
	free(cntxt);
}

/**
 * `https://librdf.org/raptor/api/raptor2-section-avltree.html`_
 */
int toot(crifi_graph* graph){
	int err;
	raptor_world *world = raptor_new_world();
	MyContext *cntxt = init_context(world);
	raptor_avltree *nodes = raptor_new_avltree(
			(raptor_data_compare_handler) compare_nodes,
			(raptor_data_free_handler) free_node,
			0);

	err = add_info_to_tree(world, graph, nodes, cntxt);
	raptor_free_avltree(nodes);
	free_context(cntxt);
	raptor_free_world(world);
	return err;
}

