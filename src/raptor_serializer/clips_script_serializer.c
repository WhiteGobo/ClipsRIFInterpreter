#include "clips_script_serializer.h"
#include "raptor_serializer.h"
#include "info_query.h"
#include "crifi_raptor_interface.h"
#include "rdf_object.h"
#include "crifi_lists.h"

#define EX(suffix) "http://example.com/" suffix
#define CLIPS(suffix) "http://clips.script/" suffix
#define RDF(suffix) "http://www.w3.org/1999/02/22-rdf-syntax-ns#" suffix
#define RDFS(suffix) "http://www.w3.org/2000/01/rdf-schema#" suffix

enum {
	SAT_NOERROR = 0,
	SAT_SUBJ,
	SAT_PRED,
	SAT_OBJ,
	SAT_LISTITEMS,
	SAT_LISTIDFAILED,
	SAT_LISTELEMENTFAILED,
	SAT_SERIALIZEFAILED
};

typedef enum {
	uri,
	bnode
} IdType;

typedef struct {
	raptor_world* world;
	NodeList* nodes;
	RDFContext* rdf_cntxt;
	raptor_term *rdf_first;
	raptor_term *rdf_rest;
	raptor_term *rdf_nil;
	raptor_term *rdf_type;
	raptor_term *rdf_List;

	//used when creating a callable function
	raptor_term *clips_RootFunction;

	raptor_term *clips_Defrule;
	raptor_term *clips_rule_name;
	raptor_term *clips_conditional_element;
	raptor_term *clips_action;
	//raptor_term *clips_Pattern_CE
	
	raptor_term *clips_Deffacts;
	raptor_term *clips_deffacts_name;
	raptor_term *clips_rhs_pattern;
	
	raptor_term *clips_pattern_ce;
	raptor_term *clips_TemplatePatternCE;
	raptor_term *clips_NotCE;
	raptor_term *clips_AndCE;
	raptor_term *clips_OrCE;
	raptor_term *clips_ExistsCE;
	raptor_term *clips_TestCE;
	raptor_term *clips_FunctionCall;
	raptor_term *clips_function_name;
	raptor_term *clips_function_args;
	raptor_term *clips_expression;
	raptor_term *clips_assert;
	raptor_term *clips_find_all_facts;
	raptor_term *clips_fact_set_template;
	raptor_term *clips_fact_set_member_variable;
	raptor_term *clips_query;

	raptor_term *clips_deftemplate_name;
	raptor_term *clips_slot;
	raptor_term *clips_slot_name;
	raptor_term *clips_constraint;
	raptor_term *clips_constraints;
	raptor_term *clips_field;

	raptor_term *clips_symbol;
	raptor_term *clips_string;
	raptor_term *clips_variable_name;
	raptor_term *clips_Function;

	raptor_term *clips_SingleWildcard;
	raptor_term *clips_MultiWildcard;
} MyContext;


static int fprintf_raptor_term(FILE* stream, raptor_term* term){
	switch(term->type){
		case RAPTOR_TERM_TYPE_LITERAL:
			fprintf(stream, term->value.literal.string);
			break;
		default:
			fprintf(stderr, "Missing support in fprinf_term "
					"for type\n");
			return CRIFI_SERIALIZE_SCRIPT_UNKNOWN;
	}
	return CRIFI_SERIALIZE_SCRIPT_NOERROR;
}


#define URI raptor_new_term_from_uri_string
static MyContext* init_context(){
	MyContext *cntxt = malloc(sizeof(MyContext));
	if (cntxt == NULL){
		return NULL;
	}
	raptor_world *world = raptor_new_world();
	cntxt->world = world;
	cntxt->nodes = new_nodelist();
	cntxt->rdf_cntxt = init_rdf_context(world);
	cntxt->rdf_type = raptor_new_term_from_uri_string(world, RDF("type"));
	cntxt->rdf_first = raptor_new_term_from_uri_string(world, RDF("first"));
	cntxt->rdf_rest = raptor_new_term_from_uri_string(world, RDF("rest"));
	cntxt->rdf_nil = raptor_new_term_from_uri_string(world, RDF("nil"));

	cntxt->clips_RootFunction = URI(world, CLIPS("RootFunction"));

	cntxt->clips_Defrule = URI(world, CLIPS("Defrule"));
	cntxt->clips_rule_name = URI(world, CLIPS("rule-name"));

	cntxt->clips_Deffacts = URI(world, CLIPS("Deffacts"));
	cntxt->clips_deffacts_name = URI(world, CLIPS("deffacts-name"));
	cntxt->clips_rhs_pattern = URI(world, CLIPS("rhs-pattern"));

	cntxt->clips_conditional_element = URI(world, CLIPS("conditional-element"));
	cntxt->clips_action = URI(world, CLIPS("action"));
	cntxt->clips_TemplatePatternCE = URI(world, CLIPS("TemplatePatternCE"));
	cntxt->clips_deftemplate_name = URI(world, CLIPS("deftemplate-name"));
	cntxt->clips_slot = URI(world, CLIPS("slot"));
	cntxt->clips_slot_name = URI(world, CLIPS("slot-name"));
	cntxt->clips_constraint = URI(world, CLIPS("constraint"));
	cntxt->clips_constraints = URI(world, CLIPS("constraints"));
	cntxt->clips_field = URI(world, CLIPS("field"));
	cntxt->clips_SingleWildcard = URI(world, CLIPS("SingleWildcard"));
	cntxt->clips_MultiWildcard = URI(world, CLIPS("MultiWildcard"));

	cntxt->clips_function_name = URI(world, CLIPS("function-name"));
	cntxt->clips_function_args = URI(world, CLIPS("function-args"));

	cntxt->clips_assert = URI(world, CLIPS("assert"));
	cntxt->clips_find_all_facts = URI(world, CLIPS("FindAllFacts"));
	cntxt->clips_fact_set_template = URI(world, CLIPS("fact-set-template"));
	cntxt->clips_fact_set_member_variable = URI(world, CLIPS("fact-set-member-variable"));
	cntxt->clips_query = URI(world, CLIPS("query"));

	//constant thingies
	cntxt->clips_symbol = URI(world, CLIPS("symbol"));
	cntxt->clips_string = URI(world, CLIPS("string"));
	cntxt->clips_variable_name = URI(world, CLIPS("variable-name"));
	//cntxt-> = URI(world, CLIPS(""));
	return cntxt;
}

static void free_context(MyContext* cntxt){
	if (cntxt != NULL){
		free_nodelist(cntxt->nodes);
		raptor_free_world(cntxt->world);
		free(cntxt);
	}
}

static CRIFI_SERIALIZE_SCRIPT_RET find_crifi_serialize_root_function(MyContext* cntxt, crifi_graph *graph){
	NodeIterator *iter_node = new_node_iterator(cntxt->nodes);
	if (iter_node == NULL){
		return CRIFI_SERIALIZE_SCRIPT_UNKNOWN;
	}
	for(Node* n = node_iterator_get(iter_node);
			n != NULL;
			n = node_iterator_get_next(iter_node)){
		if (check_property(n, cntxt->rdf_type, cntxt->clips_RootFunction)){
			fprintf(stderr, "brubru1 found rootfunction\n");
			free_node_iterator(iter_node);
			return CRIFI_SERIALIZE_SCRIPT_NOERROR;
		}
	}
	free_node_iterator(iter_node);
	fprintf(stderr, "brubru2 no rootfunction found\n");
	return CRIFI_SERIALIZE_BROKEN_GRAPH;
}

static CRIFI_SERIALIZE_SCRIPT_RET add_info_to_tree_list(MyContext* cntxt, crifi_graph *graph, Fact *l){
	int err, length;
	bool success;
	raptor_term *first = cntxt->rdf_cntxt->rdf_first;
	raptor_term *rest = cntxt->rdf_cntxt->rdf_rest;
	raptor_term *nil = cntxt->rdf_cntxt->rdf_nil;
	raptor_term *last = NULL;
	raptor_term *current = NULL;
	raptor_term *element = NULL;
	CLIPSValue l_val = {.factValue = l};
	CLIPSValue list_iterator_node = {.voidValue = VoidConstant(graph)};
	CLIPSValue *tmpval;// = {.voidValue = VoidConstant(graph)};
	CLIPSValue items = {.voidValue = VoidConstant(graph)};
	CLIPSValue clipsval_list = {.factValue = l};
	length = crifi_list_count(graph, &clipsval_list);
	if (length == 0){ //no further serializing needed
		return SAT_NOERROR;
	}
	if (!retrieve_items(graph, l_val, &items)){
		return SAT_LISTITEMS;
	}
	
	for (int i = 0; i<length; i++){
		if (!crifi_list_as_identifier(graph, &l_val, i, &list_iterator_node)){
			return SAT_LISTIDFAILED;
		}
		current = clipsvalue_to_raptorterm(cntxt->world, graph, list_iterator_node);
		if (current == NULL){
			return CRIFI_SERIALIZE_SCRIPT_OBJECT;
		}
		tmpval = items.multifieldValue->contents + i;
		element = clipsvalue_to_raptorterm(cntxt->world, graph, *tmpval);
		if (element == NULL){
			return SAT_LISTELEMENTFAILED;
		}
		err = add_triple(cntxt->nodes, current, first, element);
		switch (err){
			case 0: break;
			default: return CRIFI_SERIALIZE_SCRIPT_UNKNOWN;
		}
		if (last != NULL){
			err = add_triple(cntxt->nodes, last, rest, current);
			switch (err){
				case 0: break;
				default: return CRIFI_SERIALIZE_SCRIPT_UNKNOWN;
			}
			raptor_free_term(last);
		}
		last = current;
		current = NULL;
	}
	success = true;
	if (last != NULL){
		err = add_triple(cntxt->nodes, last, rest, nil);
		raptor_free_term(last);
		last = NULL;
	}
	switch (err){
		case 0: break;
		default:
			return CRIFI_SERIALIZE_SCRIPT_UNKNOWN;
	}
	return CRIFI_SERIALIZE_SCRIPT_NOERROR;
}


static CRIFI_SERIALIZE_SCRIPT_RET add_info_to_tree(MyContext* cntxt,
							crifi_graph *graph)
{
	int err;
	if (cntxt == NULL || graph == NULL){
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
		pred = clipsvalue_to_raptorterm(cntxt->world, graph, tmpValue);
		if (pred == NULL){
			return CRIFI_SERIALIZE_SCRIPT_PREDICATE;
		}

		GetFactSlot(f, TRIPLESLOTSUBJECT, &tmpValue);
		subj = clipsvalue_to_raptorterm(cntxt->world, graph, tmpValue);
		if (subj == NULL){
			raptor_free_term(pred);
			return CRIFI_SERIALIZE_SCRIPT_SUBJECT;
		}

		GetFactSlot(f, TRIPLESLOTOBJECT, &tmpValue);
		obj = clipsvalue_to_raptorterm(cntxt->world, graph, tmpValue);
		if (obj == NULL){
			raptor_free_term(subj);
			raptor_free_term(pred);
			return CRIFI_SERIALIZE_SCRIPT_OBJECT;
		}
		//triple = raptor_new_statement_from_nodes(world,
		//					subj, pred, obj, NULL);

		err = add_triple(cntxt->nodes, subj, pred, obj);
		switch (err){
			case 0:
				break;
			default:
				return CRIFI_SERIALIZE_SCRIPT_UNKNOWN;
		}
		//raptor_serializer_serialize_statement(my_serializer, triple);
		//raptor_free_statement(triple);
	}
	fprintf(stderr, "qwertzstart lists\n");
	for(Fact *l = get_next_list(graph, NULL);
			l != NULL;
			l = get_next_list(graph, l))
	{
		//fprintf(stderr, "convert list:\n");
		err = add_info_to_tree_list(cntxt, graph, l);
		if (err != CRIFI_SERIALIZE_SCRIPT_NOERROR){
			return err;
		}
	}
	return CRIFI_SERIALIZE_SCRIPT_NOERROR;
}


/* Parsing description */

#define FUNC_DESC(funcname) static CRIFI_SERIALIZE_SCRIPT_RET funcname(MyContext *cntxt, FILE* stream, Node* n)

FUNC_DESC(fprintf_lhs_slot);
FUNC_DESC(fprintf_template_pattern_ce);
FUNC_DESC(fprintf_conditional_element);
FUNC_DESC(fprintf_not_ce);
FUNC_DESC(fprintf_variable);
FUNC_DESC(fprintf_expression);
FUNC_DESC(fprintf_action);
FUNC_DESC(fprintf_defrule);
FUNC_DESC(fprintf_deffacts);
FUNC_DESC(fprintf_constraint);
FUNC_DESC(fprintf_term);
FUNC_DESC(fprintf_constant);
FUNC_DESC(fprintf_function);
FUNC_DESC(fprintf_assert);
FUNC_DESC(fprintf_find_facts);

FUNC_DESC(fprintf_template_rhs_pattern);
FUNC_DESC(fprintf_rhs_slot);
FUNC_DESC(fprintf_rhs_field);


/**
 * working through CRIFI_SERIALIZE_BROKEN_GRAPH is safe
 */
FUNC_DESC(fprintf_constant){
	raptor_term *symbol, *string;
	symbol = get_object(n, cntxt->clips_symbol);
	if (symbol != NULL){
		fprintf(stream, " ");
		fprintf_raptor_term(stream, symbol);
		fprintf(stream, " ");
		return CRIFI_SERIALIZE_SCRIPT_NOERROR;
	}
	string = get_object(n, cntxt->clips_string);
	if (string != NULL){
		fprintf(stream, " ");
		fprintf_raptor_term(stream, string);
		fprintf(stream, " ");
		return CRIFI_SERIALIZE_SCRIPT_NOERROR;
	}
	return CRIFI_SERIALIZE_BROKEN_GRAPH;
}

/**
 * <term> ::= <constant> |
 * 		<single-field-variable> |
 * 		multifield-variable> |
 * 		:<function-call> |
 * 		=<function-call>
 */
FUNC_DESC(fprintf_term){
	CRIFI_SERIALIZE_SCRIPT_RET err;
	err = fprintf_constant(cntxt, stream, n);
	if (err != CRIFI_SERIALIZE_BROKEN_GRAPH) return err;
	err = fprintf_variable(cntxt, stream, n);
	if (err != CRIFI_SERIALIZE_BROKEN_GRAPH) return err;
	return fprintf_function(cntxt, stream, n);
}

/**
 * <function-call> ::= (<function-name> <expression>*)
 * (<function-name> ::= literal value of given term)
 * <expression> ::= <constant> | <variable> | <function-call>
 * <term> ::= <constant> |
 * 		<single-field-variable> |
 * 		<multifield-variable> |
 * 		:<function-call> |
 * 		=<function-call>
 * <RHS-field> ::= <variable> | <constant> | <function-call>
 * <test-CE> ::= (test <function-call>)
 * <query> ::= <global-variable> | <function-call>
 */
FUNC_DESC(fprintf_function){
	CRIFI_SERIALIZE_SCRIPT_RET err = CRIFI_SERIALIZE_SCRIPT_NOERROR;
	NodeIterator* n_iter;
	raptor_term *name, *args, *assert;
	assert = get_object(n, cntxt->clips_assert);
	if (assert != NULL) return fprintf_assert(cntxt, stream, n);
	if (check_property(n, cntxt->rdf_type, cntxt->clips_find_all_facts)){
		return fprintf_find_facts(cntxt, stream, n);
	}
	name = get_object(n, cntxt->clips_function_name);
	if (name == NULL) return CRIFI_SERIALIZE_BROKEN_GRAPH;
	fprintf(stream, " (");
	fprintf_raptor_term(stream, name);

	args = get_object(n, cntxt->clips_function_args);
	if(args == NULL) return CRIFI_SERIALIZE_BROKEN_GRAPH;
	n_iter = new_rdflist_iterator(cntxt->rdf_cntxt, cntxt->nodes, args);
	if(n_iter == NULL) return CRIFI_SERIALIZE_BROKEN_GRAPH;
	for(Node* x = node_iterator_get(n_iter);
			x != NULL;
			x = node_iterator_get_next(n_iter)){
		err = fprintf_expression(cntxt, stream, x);
		if (err != CRIFI_SERIALIZE_SCRIPT_NOERROR) break;
		fprintf(stream, " ");
	}
	free_node_iterator(n_iter); n_iter = NULL;
	fprintf(stream, ")");
	return err;

}

/**
 * (find-all-facts <fact-set-template> <query>)
 * <fact-set-template> ::= (<fact-set-member-template>+)
 * <fact-set-member-template>
 * 	::= (<fact-set-member-variable> <deftemplate-restrictions>)
 * <fact-set-member-variable> ::= <single-field-variable>
 * <deftemplate-restrictions> ::= <deftemplate-name-expression>+
 * (<deftemplate-name-expression> == <deftemplate-name>)
 * (query == <boolean-expression> == <function>)
 *
 * TODO: Missing implementation for multiple deftemplate-name-expression
 */
FUNC_DESC(fprintf_find_facts){
	CRIFI_SERIALIZE_SCRIPT_RET err = CRIFI_SERIALIZE_SCRIPT_NOERROR;
	raptor_term *type, *var_templates, *query_facts, *tmpfactvar, *tmprestriction;
	Node *tmpfactvar_n, *tmprestriction_n, *query_facts_n;
	raptor_term *find_all_facts = cntxt->clips_find_all_facts;
	raptor_term *fact_set_template = cntxt->clips_fact_set_template;
	raptor_term *fact_set_member_variable = cntxt->clips_fact_set_member_variable;
	raptor_term *deftemplate_name = cntxt->clips_deftemplate_name;
	raptor_term *query = cntxt->clips_query;
	NodeIterator* n_iter;

	type = get_object(n, cntxt->rdf_type);
	if (0 != raptor_term_equals(type, find_all_facts)){
		fprintf(stream, " (find-all-facts ");
	} else {
		return CRIFI_SERIALIZE_BROKEN_GRAPH;
	}
	var_templates = get_object(n, fact_set_template);
	n_iter = new_rdflist_iterator(cntxt->rdf_cntxt, cntxt->nodes, var_templates);
	if(n_iter == NULL){
		fprintf(stderr, "cs:fact-set-template should target a rdf:List\n");
		return CRIFI_SERIALIZE_BROKEN_GRAPH;
	}
	for(Node* x = node_iterator_get(n_iter);
			x != NULL;
			x=node_iterator_get_next(n_iter)){
		fprintf(stream, "(");
		tmpfactvar = get_object(x, fact_set_member_variable);
		tmpfactvar_n = retrieve_node(cntxt->nodes, tmpfactvar);
		if(tmpfactvar_n == NULL){
			err = CRIFI_SERIALIZE_BROKEN_GRAPH;
			break;
		}
		err = fprintf_variable(cntxt, stream, tmpfactvar_n);
		if (err != CRIFI_SERIALIZE_SCRIPT_NOERROR){
			break;
		}

		tmprestriction = get_object(x, deftemplate_name);
		if(tmprestriction == NULL){
			err = CRIFI_SERIALIZE_BROKEN_GRAPH;
			break;
		}
		err = fprintf_raptor_term(stream, tmprestriction);
		if (err != CRIFI_SERIALIZE_SCRIPT_NOERROR){
			break;
		}
		fprintf(stream, ")");
	}
	free_node_iterator(n_iter);
	n_iter = NULL;
	if (err != CRIFI_SERIALIZE_SCRIPT_NOERROR ){
		return err;
	}

	query_facts = get_object(n, cntxt->clips_query);
	query_facts_n = retrieve_node(cntxt->nodes, query_facts);
	if(query_facts_n == NULL){
		return CRIFI_SERIALIZE_BROKEN_GRAPH;
	}
	fprintf_function(cntxt, stream, query_facts_n);

	fprintf(stream, ") ");
	return err;
}

/**
 * (assert <RHS-pattern>+)
 */
FUNC_DESC(fprintf_assert){
	CRIFI_SERIALIZE_SCRIPT_RET err = CRIFI_SERIALIZE_SCRIPT_NOERROR;
	raptor_term *assert;
	Node *assert_n;
	assert = get_object(n, cntxt->clips_assert);
	if (assert == NULL){
		fprintf(stderr, "fprintf_assert failed to find assert target\n");
		return CRIFI_SERIALIZE_BROKEN_GRAPH;
	}
	assert_n = retrieve_node(cntxt->nodes, assert);
	fprintf(stream, "(assert");
	err = fprintf_template_rhs_pattern(cntxt, stream, assert_n);
	fprintf(stream, ")");
	return err;
}

static CRIFI_SERIALIZE_SCRIPT_RET fprintf_lhs_slot(MyContext *cntxt, FILE* stream, Node* n){
	CRIFI_SERIALIZE_SCRIPT_RET err = CRIFI_SERIALIZE_SCRIPT_NOERROR;
	raptor_term *name, *constraint, *constraints;
	Node* constraint_n;
	NodeIterator* n_iter;
	name = get_object(n, cntxt->clips_slot_name);
	if (name == NULL) return CRIFI_SERIALIZE_BROKEN_GRAPH;
	fprintf(stream, " (");
	fprintf_raptor_term(stream, name);
	fprintf(stream, " ");

	constraint = get_object(n, cntxt->clips_constraint);
	if (constraint != NULL){
		constraint_n = retrieve_node(cntxt->nodes, constraint);
		if (constraint_n == NULL) return CRIFI_SERIALIZE_BROKEN_GRAPH;
		fprintf_constraint(cntxt, stream, constraint_n);
		//fprintf_raptor_term(stream, constraint);
	} else {
		constraints = get_object(n, cntxt->clips_constraints);
		n_iter = new_rdflist_iterator(cntxt->rdf_cntxt, cntxt->nodes, constraints);
		for(Node* x = node_iterator_get(n_iter);
				x != NULL;
				x = node_iterator_get_next(n_iter)){
			err = fprintf_constraint(cntxt, stream, x);
			if (err != CRIFI_SERIALIZE_SCRIPT_NOERROR) break;
		}
		free_node_iterator(n_iter);
	}
	fprintf(stream, ")");
	return err;
}

/**
 * <RHS-pattern> ::= <ordered-RHS-pattern> | <template-RHS-pattern>
 * <template-RHS-pattern> ::= (<deftemplate-name> <RHS-slot>*)
 */
static CRIFI_SERIALIZE_SCRIPT_RET fprintf_template_rhs_pattern(MyContext *cntxt, FILE* stream, Node* n){
	CRIFI_SERIALIZE_SCRIPT_RET err;
	raptor_term *name, *slots;
	NodeIterator* n_iter;
	name = get_object(n, cntxt->clips_deftemplate_name);
	fprintf(stream, "(");
	if (name == NULL){
		fprintf(stderr, "template_rhs_pattern is missing a name\n");
		return CRIFI_SERIALIZE_BROKEN_GRAPH;
	}
	fprintf_raptor_term(stream, name);
	slots = get_object(n, cntxt->clips_slot);
	n_iter = new_rdflist_iterator(cntxt->rdf_cntxt, cntxt->nodes, slots);
	for(Node* x = node_iterator_get(n_iter);
			x != NULL;
			x=node_iterator_get_next(n_iter)){
		err = fprintf_rhs_slot(cntxt, stream, x);
		if (err != CRIFI_SERIALIZE_SCRIPT_NOERROR) break;
	}
	free_node_iterator(n_iter);

	fprintf(stream, ")");
	return err;
}

/**
 * <RHS-slot> ::= <single-field-RHS-slot> |
 * 		<multifield-RHS-slot>
 * <single-field-RHS-slot> ::= (<slot-name> <RHS-field>)
 * <multifield-RHS-slot> ::= (<slot-name> <RHS-field>*)
 */
static CRIFI_SERIALIZE_SCRIPT_RET fprintf_rhs_slot(MyContext *cntxt, FILE* stream, Node* n){
	CRIFI_SERIALIZE_SCRIPT_RET err = CRIFI_SERIALIZE_SCRIPT_NOERROR;
	int i = 0;
	raptor_term *name, *field, *fields;
	Node* constraint_n;
	NodeIterator* n_iter;
	name = get_object(n, cntxt->clips_slot_name);
	if (name == NULL){
		fprintf(stderr, "fprintf_rhs_slot is missing a cs:slot-name\n");
		return CRIFI_SERIALIZE_BROKEN_GRAPH;
	}
	fprintf(stream, " (");
	fprintf_raptor_term(stream, name);
	fprintf(stream, " ");

	fields = get_object(n, cntxt->clips_field);
	if(fields == NULL){
		fprintf(stderr, "fprintf_rhs_slot is missing cs:field\n");
		return CRIFI_SERIALIZE_BROKEN_GRAPH;
	}
	n_iter = new_rdflist_iterator(cntxt->rdf_cntxt, cntxt->nodes, fields);
	if(n_iter == NULL){
		fprintf(stderr, "cs:field should target a rdf:List\n");
		return CRIFI_SERIALIZE_BROKEN_GRAPH;
	}
	i = 0;
	for(Node* x = node_iterator_get(n_iter);
			x != NULL;
			x = node_iterator_get_next(n_iter)){
		i++;
		err = fprintf_rhs_field(cntxt, stream, x);
		if (err != CRIFI_SERIALIZE_SCRIPT_NOERROR) break;
	}
	if (i == 0){
		fprintf(stderr, "list for cs:field must be non empty.\n");
		return CRIFI_SERIALIZE_BROKEN_GRAPH;
	}
	free_node_iterator(n_iter);
	fprintf(stream, ")");
	return err;
}

/**
 * <RHS-field> ::= <variable> | <constant> | <function-call>
 */
FUNC_DESC(fprintf_rhs_field){
	CRIFI_SERIALIZE_SCRIPT_RET err;
	err = fprintf_constant(cntxt, stream, n);
	switch (err){
		case CRIFI_SERIALIZE_SCRIPT_NOERROR:
			return CRIFI_SERIALIZE_SCRIPT_NOERROR;
		case CRIFI_SERIALIZE_BROKEN_GRAPH:
			break;
		default:
			fprintf(stderr, "fprintf_constant failed\n");
			return err;
	}
	err = fprintf_variable(cntxt, stream, n);
	switch (err){
		case CRIFI_SERIALIZE_SCRIPT_NOERROR:
			return CRIFI_SERIALIZE_SCRIPT_NOERROR;
		case CRIFI_SERIALIZE_BROKEN_GRAPH:
			break;
		default:
			fprintf(stderr, "fprintf_variable failed\n");
			return err;
	}
	return fprintf_function(cntxt, stream, n);
}


static CRIFI_SERIALIZE_SCRIPT_RET fprintf_template_pattern_ce(MyContext *cntxt, FILE* stream, Node* n){
	CRIFI_SERIALIZE_SCRIPT_RET err;
	raptor_term *name, *slots;
	NodeIterator* n_iter;
	name = get_object(n, cntxt->clips_deftemplate_name);
	fprintf(stream, "(");
	if (name == NULL) return CRIFI_SERIALIZE_BROKEN_GRAPH;
	fprintf_raptor_term(stream, name);
	slots = get_object(n, cntxt->clips_slot);
	n_iter = new_rdflist_iterator(cntxt->rdf_cntxt, cntxt->nodes, slots);
	for(Node* x = node_iterator_get(n_iter);
			x != NULL;
			x=node_iterator_get_next(n_iter)){
		err = fprintf_lhs_slot(cntxt, stream, x);
		if (err != CRIFI_SERIALIZE_SCRIPT_NOERROR) return err;
	}
	free_node_iterator(n_iter);

	fprintf(stream, ")");
	return CRIFI_SERIALIZE_SCRIPT_NOERROR;
}

/**
 * <conditional-element> ::= <pattern-CE> |
 * 			<assigned-pattern-CE> |
 * 			<not-CE> |
 * 			<and-CE> |
 * 			<or-CE> |
 * 			<logical-CE> |
 * 			<test-CE> |
 * 			<exists-CE> |
 * 			<forall-CE>
 */
static CRIFI_SERIALIZE_SCRIPT_RET fprintf_conditional_element(MyContext *cntxt, FILE* stream, Node* n){
	if (check_property(n, cntxt->rdf_type, cntxt->clips_TemplatePatternCE)){
		return fprintf_template_pattern_ce(cntxt, stream, n);
	} else if (check_property(n, cntxt->rdf_type, cntxt->clips_NotCE)){
		return fprintf_not_ce(cntxt, stream, n);
	}
	debug_fprintf_node(stderr, "failed conditional element ", n, "\n");
	return CRIFI_SERIALIZE_BROKEN_GRAPH;
}

FUNC_DESC(fprintf_not_ce){
	CRIFI_SERIALIZE_SCRIPT_RET err = CRIFI_SERIALIZE_SCRIPT_NOERROR;
	raptor_term *targets;
	NodeIterator* n_iter;
	bool at_least_one = false;

	fprintf(stream, "(not\n");
	targets = get_object(n, cntxt->clips_conditional_element);
	n_iter = new_rdflist_iterator(cntxt->rdf_cntxt, cntxt->nodes, targets);
	if(n_iter == NULL){
		return CRIFI_SERIALIZE_BROKEN_GRAPH;
	}
	for(Node* x = node_iterator_get(n_iter);
			x != NULL;
			x=node_iterator_get_next(n_iter)){
		at_least_one = true;
		err = fprintf_conditional_element(cntxt, stream, x);
		if (err != CRIFI_SERIALIZE_SCRIPT_NOERROR){
			break;
		}
		fprintf(stream, "\n");
	}
	free_node_iterator(n_iter);
	if (err != CRIFI_SERIALIZE_SCRIPT_NOERROR && !at_least_one){
		err = CRIFI_SERIALIZE_BROKEN_GRAPH;
	}
	//err = fprintf_conditional_element(cntxt, stream, target_n);
	fprintf(stream, ")");
	return err;
}


/**
 * working through CRIFI_SERIALIZE_BROKEN_GRAPH is safe.
 * <global-variable> and <multifield-variable> are not implemented.
 *
 * <term> ::= <constant> |
 * 		<single-field-variable> |
 * 		<multifield-variable> |
 * 		:<function-call> |
 * 		=<function-call>
 * <expression> ::= <constant> || <variable> || <function-call>
 * <variable> ::= <single-field-variable> |
 * 		<multifield-variable> |
 * 		<global-variable>
 */
static CRIFI_SERIALIZE_SCRIPT_RET fprintf_variable(MyContext *cntxt, FILE* stream, Node* n){
	raptor_term *varname;
	varname = get_object(n, cntxt->clips_variable_name);
	if (varname != NULL){
		fprintf(stream, " ?");
		fprintf_raptor_term(stream, varname);
		fprintf(stream, " ");
		return CRIFI_SERIALIZE_SCRIPT_NOERROR;
	}
	return CRIFI_SERIALIZE_BROKEN_GRAPH;
}


/**
 * <constraint> ::= ? | $? | <connected-constraint>
 * <connected-constraint> ::= 
 * 			<single-constraint> |
 * 			<single-constraint> & <connected-constraint> |
 * 			<single-constraint> | <connected-constraint>
 * <single-constraint> ::= <term> | ~<term>
 */
FUNC_DESC(fprintf_constraint){
	CRIFI_SERIALIZE_SCRIPT_RET err;
	if (check_id(n, cntxt->clips_SingleWildcard)){
		fprintf(stream, " ? ");
	} else if (check_id(n, cntxt->clips_MultiWildcard)){
		fprintf(stream, " $? ");
	} else {
		//no connected constraint implemented
		return fprintf_term(cntxt, stream, n);
	}
	return CRIFI_SERIALIZE_SCRIPT_NOERROR;
}

/**
 * <action> ::= <expression>
 * <function-call> ::= (<function-name> <expression>*)
 * <expression> ::= <constant> || <variable> || <function-call>
 */
static CRIFI_SERIALIZE_SCRIPT_RET fprintf_expression(MyContext *cntxt, FILE* stream, Node* n){
	CRIFI_SERIALIZE_SCRIPT_RET err;
	err = fprintf_constant(cntxt, stream, n);
	if (err != CRIFI_SERIALIZE_BROKEN_GRAPH) return err;
	err = fprintf_variable(cntxt, stream, n);
	if (err != CRIFI_SERIALIZE_BROKEN_GRAPH) return err;
	return fprintf_function(cntxt, stream, n);
}

static CRIFI_SERIALIZE_SCRIPT_RET fprintf_action(MyContext *cntxt, FILE* stream, Node* n){
	return fprintf_expression(cntxt, stream, n);
}


/**
 *
 * <defrule-construct> ::= (defrule <rule-name> [<comment>]
 * 			[<declaration>]
 * 			<conditional-element>*
 * 			=>
 * 			<action>*)
 * (<rule-name> ::= literal value of given term)
 * <action> ::= <expression>
 */
static CRIFI_SERIALIZE_SCRIPT_RET fprintf_defrule(MyContext *cntxt, FILE* stream, Node* n){

	CRIFI_SERIALIZE_SCRIPT_RET err;
	NodeIterator* n_iter;
	TermIterator* iter;
	raptor_term *name, *condition, *action, *entry;
	Node *tmpnode = NULL;

	fprintf(stream, "(defrule ");
	name = get_object(n, cntxt->clips_rule_name);
	if (name != NULL){
		fprintf_raptor_term(stream, name);
	} else {
		fprintf(stream, "rule%x", n);
	}
	fprintf(stream, "\n");
	condition = get_object(n, cntxt->clips_conditional_element);
	n_iter = new_rdflist_iterator(cntxt->rdf_cntxt, cntxt->nodes, condition);
	if(n_iter == NULL){
		fprintf(stderr, "cs:conditional-element should target a rdf:List\n");
		return CRIFI_SERIALIZE_BROKEN_GRAPH;
	}
	for(Node* x = node_iterator_get(n_iter);
			x != NULL;
			x=node_iterator_get_next(n_iter)){
		err = fprintf_conditional_element(cntxt, stream, x);
		if (err != CRIFI_SERIALIZE_SCRIPT_NOERROR) return err;
		fprintf(stream, "\n");
	}
	free_node_iterator(n_iter); n_iter = NULL;

	fprintf(stream, "\t=>\n");

	action = get_object(n, cntxt->clips_action);
	n_iter = new_rdflist_iterator(cntxt->rdf_cntxt, cntxt->nodes, action);
	for(Node* x = node_iterator_get(n_iter);
			x != NULL;
			x=node_iterator_get_next(n_iter)){
		err = fprintf_action(cntxt, stream, x);
		if (err != CRIFI_SERIALIZE_SCRIPT_NOERROR) return err;
	}
	free_node_iterator(n_iter); n_iter = NULL;
	fprintf(stream, ")");
	return CRIFI_SERIALIZE_SCRIPT_NOERROR;
}

/**
 * ::= (deffacts <deffacts-name> [<comment>] <RHS-pattern>*)
 */
FUNC_DESC(fprintf_deffacts){
	CRIFI_SERIALIZE_SCRIPT_RET err = CRIFI_SERIALIZE_SCRIPT_NOERROR;
	NodeIterator* n_iter;
	raptor_term *rhspatterns, *name, *args, *assert;
	fprintf(stream, "(deffacts ");
	name = get_object(n, cntxt->clips_deffacts_name);
	if (name != NULL){
		fprintf_raptor_term(stream, name);
	} else {
		fprintf(stream, "facts%x", n);
	}
	fprintf(stream, "\n");

	rhspatterns = get_object(n, cntxt->clips_rhs_pattern);
	n_iter = new_rdflist_iterator(cntxt->rdf_cntxt, cntxt->nodes, rhspatterns);
	if(n_iter == NULL){
		return CRIFI_SERIALIZE_BROKEN_GRAPH;
	}
	for(Node* x = node_iterator_get(n_iter);
			x != NULL;
			x = node_iterator_get_next(n_iter)){
		err = fprintf_template_rhs_pattern(cntxt, stream, x);
		fprintf(stream, "\n");
		if (err != CRIFI_SERIALIZE_SCRIPT_NOERROR){
			break;
		}
	}
	free_node_iterator(n_iter);
	fprintf(stream, ")");
	return err;
}


static CRIFI_SERIALIZE_SCRIPT_RET fprintf_script(MyContext *cntxt, FILE* stream){
	CRIFI_SERIALIZE_SCRIPT_RET err;
	NodeIterator *iter_node = new_node_iterator(cntxt->nodes);
	//If cntxt is initialized correctly this should never happen.
	if (iter_node == NULL){
		return CRIFI_SERIALIZE_SCRIPT_UNKNOWN;
	}
	for(Node* n = node_iterator_get(iter_node);
			n != NULL;
			n = node_iterator_get_next(iter_node)){
		if (check_property(n, cntxt->rdf_type, cntxt->clips_Defrule)){
			err = fprintf_defrule(cntxt, stream, n);
			if (err != CRIFI_SERIALIZE_SCRIPT_NOERROR){
				return err;
			}
			fprintf(stream, "\n\n");
		} else if (check_property(n, cntxt->rdf_type, cntxt->clips_Deffacts)){
			err = fprintf_deffacts(cntxt, stream, n);
			if (err != CRIFI_SERIALIZE_SCRIPT_NOERROR){
				return err;
			}
			fprintf(stream, "\n\n");
		}
	}
	free_node_iterator(iter_node);
	return CRIFI_SERIALIZE_SCRIPT_NOERROR;
}

/* main method */

CRIFI_SERIALIZE_SCRIPT_RET serialize_information_as_clips_script(FILE* stream, crifi_graph* graph){
	int err = 0;
	if (stream == NULL || graph == NULL){
		return CRIFI_SERIALIZE_SCRIPT_INPUT;
	}
	MyContext *cntxt = init_context();
	if (cntxt == NULL){
		return CRIFI_SERIALIZE_SCRIPT_CANT_CREATE_STRUCTS;
	}
	err = add_info_to_tree(cntxt, graph);
	if (err == 0){
		err = fprintf_script(cntxt, stream);
	}
	free_context(cntxt);
	return err;
}

CRIFI_SERIALIZE_SCRIPT_RET serialize_information_as_clips_function(FILE* stream, crifi_graph* graph){
	int err = 0;
	if (stream == NULL || graph == NULL){
		return CRIFI_SERIALIZE_SCRIPT_INPUT;
	}
	MyContext *cntxt = init_context();
	if (cntxt == NULL){
		return CRIFI_SERIALIZE_SCRIPT_CANT_CREATE_STRUCTS;
	}
	err = add_info_to_tree(cntxt, graph);
	if (err != 0){
		free_context(cntxt);
		return err;
	}
	err = find_crifi_serialize_root_function(cntxt, graph);
	if (err != 0){
		free_context(cntxt);
		return err;
	}
	if (err == 0){
		err = CRIFI_SERIALIZE_SCRIPT_UNKNOWN;
		//fprintf(stream, "(eq 1 1)");
		//err = fprintf_script(cntxt, stream);
	}
	free_context(cntxt);
	return err;
}
