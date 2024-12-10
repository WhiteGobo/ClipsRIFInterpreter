/** \file clips_to_interface.h
 * Methods to convert between clips data and interface data
 */
#pragma once

#include <clips.h>

/**
 * transforms given CLIPSValue. Im not sure how exactly
 */
char *FactToTerm(CLIPSValue value);

/**
 * with given triple, determines if given filter by name is true.
 */
bool filter_triples(
		char *filter_subject,
		char *filter_predicate,
		char *filter_object,
		char *subject, char *predicate, char *object
);

/**
 * copy factlist
 */
struct TriplesLinkedList *copy_getfacts_to_list(Environment *, Multifield *, char *filter_subject, char *filter_predicate, char *filter_object);

/**
 * placeholder
 */
struct DynamicValue clipsToDynamic(CLIPSValue *val);
