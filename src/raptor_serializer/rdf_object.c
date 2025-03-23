#include <stdlib.h>
#include "rdf_object.h"

typedef raptor_avltree PropertyPairs;
typedef struct {
	raptor_term *prop;
	raptor_term *obj;
} PropertyPairNode;

typedef struct Node_s {
	raptor_term *id;
	PropertyPairs* properties;
} Node;

typedef enum {
	NODEITERATOR_TYPE_RAPTOR_AVLTREE,
	NODEITERATOR_TYPE_RDFITERATOR
} NODEITERATOR_TYPE;

typedef struct {
	RDFContext* cntxt;
	NodeList* nodes;
	Node* current_list_element;
} RDFIterator;

struct NodeIterator_s {
	NODEITERATOR_TYPE type;
	union {
		raptor_avltree_iterator* raptor_tree;
		RDFIterator rdfiter;
	};
};// NodeIterator;

static Node* nodelist_search(NodeList* nodes, Node* searcher){
	return (Node*) raptor_avltree_search(nodes, searcher);
}
static int nodelist_add(NodeList* nodes, Node* n){
	return raptor_avltree_add(nodes, n);
}

/**
 * Compare two PropertyPair in avltree.
 * NULL in new->prop or new->obj is considered as wildcard.
 * There is no NULL-check for new, old, old->prop or old->obj.
 */
static int compare_property_pair(const PropertyPairNode* new, const PropertyPairNode* old){
	int diff;
	if (new->prop == NULL){
		if(new->obj == NULL){
			return 0;
		} else {
			return raptor_term_compare(new->obj, old->obj);
		}

	}
	diff = raptor_term_compare(new->prop, old->prop);
	if (diff != 0){
		return diff;
	}
	if (new->obj == NULL){
		return 0;
	}
	return raptor_term_compare(new->obj, old->obj);
}

static void free_property_pair(PropertyPairNode* pp){
	if (pp == NULL) return;
	raptor_free_term(pp->prop);
	raptor_free_term(pp->obj);
	free(pp);
}

/**
 * Compare for avltree for Node
 */
static int compare_nodes(const Node* n1, const Node* n2){
	if (n1 == NULL || n2 == NULL){
		return 0;
	}
	return raptor_term_compare(n1->id, n2->id);
}

/**
 * Free Node
 */
static void free_node(Node* n){
	if (n == NULL) return;
	raptor_free_avltree(n->properties);
	raptor_free_term(n->id);
	free(n);
}

static int add_property(Node *node, raptor_term *prop, raptor_term *obj){
	int err;
	PropertyPairNode *newpair = malloc(sizeof(PropertyPairNode));
	if(newpair == NULL){
		return 1;
	}
	newpair->prop = raptor_term_copy(prop);
	newpair->obj = raptor_term_copy(obj);
	err = raptor_avltree_add(node->properties, newpair);
	if (err != 0){
		free_property_pair(newpair);
		return 2;
	}
	return 0;
}

static Node *new_node(raptor_term *id){
	Node *ret = malloc(sizeof(Node));
	if (ret == NULL){
		return NULL;
	}
	raptor_avltree *properties = raptor_new_avltree(
			(raptor_data_compare_handler) compare_property_pair,
			(raptor_data_free_handler) free_property_pair,
			0);
	if (properties == NULL){
		free(ret);
		return NULL;
	}
	ret->id = raptor_term_copy(id);
	ret->properties = properties;
	return ret;
}

Node* retrieve_node(NodeList* nodes, raptor_term *id){
	int err;
	if (id == NULL) return NULL;
	Node searcher = {.id = id};
	Node *existing = nodelist_search(nodes, &searcher);
	if (existing == NULL){
		existing = new_node(id);
		if (existing == NULL){
			return NULL;
		}
		err = nodelist_add(nodes, existing);
		if (0 != err){
			free_node(existing);
			return NULL;
		}
	}
	return existing;
}

int add_triple(NodeList* nodes, raptor_term *subj, raptor_term* prop, raptor_term* obj){
	int err;
	if (subj == NULL || prop == NULL || obj == NULL){
		return 1;
	}
	Node* n = retrieve_node(nodes, subj);
	if (n == NULL) return 2;
	return add_property(n, prop, obj);
}

NodeList* new_nodelist(){
	NodeList* nodes = raptor_new_avltree(
			(raptor_data_compare_handler) compare_nodes,
			(raptor_data_free_handler) free_node,
			0);
	return nodes;
}

void free_nodelist(NodeList* nodes){
	raptor_free_avltree(nodes);
}



bool check_property(Node* n, raptor_term* pred, raptor_term* obj){
	if (n == NULL) return false;
	if (pred == NULL && obj != NULL) return false;
	PropertyPairNode searcher = {.prop=pred, .obj=obj};
	void* result = raptor_avltree_search(n->properties, &searcher);
	return result != NULL;
}

bool check_id(Node* n, raptor_term* subject){
	return 0 == raptor_term_compare(n->id, subject);
}


raptor_term* get_object(Node* n, raptor_term* pred){
	PropertyPairNode searcher = {.prop=pred, .obj=NULL};
	PropertyPairNode* result;
	result = raptor_avltree_search(n->properties, &searcher);
	if (result == NULL) return NULL;
	return result->obj;
}

//needed for raptor_new_avltree_iterator
#define BACKWARDS 0
#define FORWARDS 1
static void no_free(void*){}

TermIterator* new_object_iterator(Node* n, raptor_term* pred){
	PropertyPairNode searcher = {.prop=pred, .obj=NULL};
	return raptor_new_avltree_iterator(n->properties, &searcher, no_free, FORWARDS);
}

raptor_term* object_iterator_get(TermIterator* iter){
	PropertyPairNode *result;
	result = raptor_avltree_iterator_get(iter);
	return result->obj;
}

raptor_term* object_iterator_get_next(TermIterator* iter){
	PropertyPairNode *result;
	if (0 != raptor_avltree_iterator_is_end(iter)){
		return NULL;
	}
	raptor_avltree_iterator_next(iter);
	result = raptor_avltree_iterator_get(iter);
	if (result == NULL) return NULL;
	return result->obj;
}

void free_object_iterator(TermIterator* iter){
	if(iter == NULL) return;
	raptor_free_avltree_iterator(iter);
}



void debug_fprintf_node(FILE* stream, char* before, Node* n, char* after){
	char* pred, *obj;
	raptor_avltree_iterator* iter;
	fprintf(stream, before);
	fprintf(stream, "%s", raptor_term_to_string(n->id));
	fprintf(stream, "[");
	iter = raptor_new_avltree_iterator(n->properties, NULL, no_free, FORWARDS);
	for (PropertyPairNode *p = (PropertyPairNode*) raptor_avltree_iterator_get(iter);
			p != NULL;
			p = (PropertyPairNode*) raptor_avltree_iterator_get(iter)
			){
		pred = raptor_term_to_string(p->prop);
		obj = raptor_term_to_string(p->obj);
		fprintf(stream, "%s->%s", pred, obj);
		if (0 != raptor_avltree_iterator_is_end(iter)) break;
		fprintf(stream, " ");
		raptor_avltree_iterator_next(iter);
	}
	raptor_free_avltree_iterator(iter);
	fprintf(stream, "]");
	fprintf(stream, after);
}


#define RDF(suffix) "http://www.w3.org/1999/02/22-rdf-syntax-ns#" suffix
#define RDFS(suffix) "http://www.w3.org/2000/01/rdf-schema#" suffix

#define URI raptor_new_term_from_uri_string
RDFContext* init_rdf_context(raptor_world *world){
	RDFContext *cntxt;
	if (world == NULL) return NULL;
	cntxt = malloc(sizeof(RDFContext));
	if (cntxt == NULL) return NULL;
	cntxt->rdf_type = URI(world, RDF("type"));
	cntxt->rdf_first = URI(world, RDF("first"));
	cntxt->rdf_rest = URI(world, RDF("rest"));
	cntxt->rdf_nil = URI(world, RDF("nil"));
	return cntxt;
}

void free_rdf_context(RDFContext* cntxt){
	free(cntxt);
}

NodeIterator* new_rdflist_iterator(RDFContext* cntxt, NodeList* nodes, raptor_term* startnode){
	NodeIterator* retval;
	if (cntxt == NULL || nodes == NULL || startnode == NULL){
		return NULL;
	}
	Node* startnode_n = retrieve_node(nodes, startnode);
	if (startnode_n == NULL) return NULL;
	retval = malloc(sizeof(NodeIterator));
	retval->type = NODEITERATOR_TYPE_RDFITERATOR;
	retval->rdfiter.current_list_element = startnode_n;
	retval->rdfiter.cntxt = cntxt;
	retval->rdfiter.nodes = nodes;
	return retval;
}

static Node* rdflist_node_iterator_get(NodeIterator* iter){
	raptor_term *entry_term;
	Node* list = iter->rdfiter.current_list_element;
	if (list == NULL) return NULL;
	entry_term = get_object(list, iter->rdfiter.cntxt->rdf_first);
	if (entry_term == NULL) return NULL;
	return retrieve_node(iter->rdfiter.nodes, entry_term);
}

static Node* rdflist_node_iterator_get_next(NodeIterator* iter){
	Node *sublist;
	raptor_term* sublist_term;
	sublist_term = get_object(iter->rdfiter.current_list_element,
						iter->rdfiter.cntxt->rdf_rest);

	if (0 == raptor_term_compare(sublist_term,
					iter->rdfiter.cntxt->rdf_nil)){
		iter->rdfiter.current_list_element = NULL;
	} else {
		sublist = retrieve_node(iter->rdfiter.nodes, sublist_term);
		iter->rdfiter.current_list_element = sublist;
	}
	return rdflist_node_iterator_get(iter);
}

static Node* raptor_avltree_node_iterator_get(NodeIterator* iter){
	return raptor_avltree_iterator_get(iter->raptor_tree);
}

static Node* raptor_avltree_node_iterator_get_next(NodeIterator* iter){
	if (0 != raptor_avltree_iterator_is_end(iter->raptor_tree)){
		return NULL;
	}
	raptor_avltree_iterator_next(iter->raptor_tree);
	return raptor_avltree_iterator_get(iter->raptor_tree);
}

static void raptor_avltree_free_node_iterator(NodeIterator* iter){
	raptor_free_avltree_iterator(iter->raptor_tree);
	free(iter);
}


Node* node_iterator_get(NodeIterator* iter){
	if (iter == NULL) return NULL;
	switch (iter->type){
		case NODEITERATOR_TYPE_RAPTOR_AVLTREE:
			return raptor_avltree_node_iterator_get(iter);
			break;
		case NODEITERATOR_TYPE_RDFITERATOR:
			return rdflist_node_iterator_get(iter);
			break;
	}
	return NULL;
}

Node* node_iterator_get_next(NodeIterator* iter){
	if (iter == NULL) return NULL;
	switch (iter->type){
		case NODEITERATOR_TYPE_RAPTOR_AVLTREE:
			return raptor_avltree_node_iterator_get_next(iter);
			break;
		case NODEITERATOR_TYPE_RDFITERATOR:
			return rdflist_node_iterator_get_next(iter);
			break;
	}
	return NULL;
}

void free_node_iterator(NodeIterator* iter){
	if (iter == NULL) return;
	switch (iter->type){
		case NODEITERATOR_TYPE_RAPTOR_AVLTREE:
			raptor_avltree_free_node_iterator(iter);
			break;
		case NODEITERATOR_TYPE_RDFITERATOR:
			free(iter);
			break;
	}
}

NodeIterator* new_node_iterator(NodeList* nodes){
	if (nodes == NULL) return NULL;
	NodeIterator* retval = malloc(sizeof(NodeIterator));
	retval->type = NODEITERATOR_TYPE_RAPTOR_AVLTREE;
	retval->raptor_tree = raptor_new_avltree_iterator(nodes, NULL, no_free,
							FORWARDS);
	return retval;
}
