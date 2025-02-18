#pragma once

#include <raptor.h>
#include <stdbool.h>

typedef raptor_avltree NodeList;
typedef struct Node_s Node;
typedef raptor_avltree_iterator TermIterator;

typedef struct RDFContext_s {
	raptor_term *rdf_first;
	raptor_term *rdf_rest;
	raptor_term *rdf_nil;
	raptor_term *rdf_type;
	raptor_term *rdf_List;
} RDFContext;


typedef struct NodeIterator_s NodeIterator;

#ifdef __cplusplus
extern "C" {
#endif

NodeList* new_nodelist();
void free_nodelist(NodeList* nodes);
int add_triple(NodeList* nodes, raptor_term *subj, raptor_term* prop, raptor_term* obj);

Node* retrieve_node(NodeList* nodes, raptor_term *id);

bool check_property(Node* n, raptor_term* pred, raptor_term* obj);

bool check_id(Node* n, raptor_term* subject);

raptor_term* get_object(Node* n, raptor_term* pred);
TermIterator* new_object_iterator(Node* n, raptor_term* pred);
raptor_term* object_iterator_get(TermIterator*);
raptor_term* object_iterator_get_next(TermIterator*);
void free_object_iterator(TermIterator*);

/**
 * helper function to print node info
 */
void debug_fprintf_node(FILE* stream, char* before, Node* n, char* after);

RDFContext* init_rdf_context(raptor_world *world);
void free_rdf_context(RDFContext*);



NodeIterator* new_node_iterator(NodeList*);
NodeIterator* new_rdflist_iterator(RDFContext* cntxt, NodeList* nodes, raptor_term* startnode);

Node* node_iterator_get(NodeIterator*);
Node* node_iterator_get_next(NodeIterator*);
void free_node_iterator(NodeIterator*);


#ifdef __cplusplus
} //extern "C"
#endif
