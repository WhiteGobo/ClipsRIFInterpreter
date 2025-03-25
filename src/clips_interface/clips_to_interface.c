#include "clips_to_interface.h"
#include "dataspace_constants.h"
#include "ffi_clips_interface.h"
#include "n3parser.h"

bool filter_triples(
		char *filter_subject,
		char *filter_predicate,
		char *filter_object,
		char *subject, char *predicate, char *object
){
	if (filter_subject != NULL){
		if (0 != strcmp(filter_subject, subject)){
			return false;
		}
	}
	if (filter_predicate != NULL){
		if (0 != strcmp(filter_predicate, predicate)){
			return false;
		}
	}
	if (filter_object != NULL){
		if (0 != strcmp(filter_object, object)){
			return false;
		}
	}
	return true;
}

struct TriplesLinkedList *copy_getfacts_to_list(Environment *env, Multifield *facts, char *filter_subject, char *filter_predicate, char *filter_object){
	struct TriplesLinkedList *first = NULL;
	struct TriplesLinkedList **nextPointerPosition = &first;
	struct TriplesLinkedList *rest;
	CLIPSValue tmpValue;
	CLIPSValue *itValue;
	Fact *currentFact;
	Deftemplate *tmpTempl;
	Deftemplate *tripletemplate = FindDeftemplate(env, TRIPLETEMPLATE);
	//CLIPSLexeme *compSymbol = CreateSymbol(env, symbolname);
	for (size_t i = 0; i < facts->length; i++)
	{
		itValue = &facts->contents[i];
		if(itValue->header->type == FACT_ADDRESS_TYPE){
			currentFact = itValue->factValue;
			tmpTempl = FactDeftemplate(currentFact);
			if (tmpTempl == tripletemplate) {
				rest = (struct TriplesLinkedList *)
					malloc(sizeof(struct TriplesLinkedList));
				GetFactSlot(currentFact, TRIPLESLOTSUBJECT, &tmpValue);
				rest->subject = clipsvalue_to_n3(env, tmpValue);
				GetFactSlot(currentFact, TRIPLESLOTPREDICATE, &tmpValue);
				rest->predicate = clipsvalue_to_n3(env, tmpValue);
				GetFactSlot(currentFact, TRIPLESLOTOBJECT, &tmpValue);
				rest->object = clipsvalue_to_n3(env, tmpValue);
				rest->rest = NULL;
				if (filter_triples(filter_subject, filter_predicate, filter_object, rest->subject, rest->predicate, rest->object)){
					*nextPointerPosition = rest;
					nextPointerPosition = &(rest->rest);
				} else {
					free_linked_list(rest);
				}
			}
		}
	}
	return first;
}


struct DynamicValue clipsToDynamic(CLIPSValue *val){
	struct DynamicValue retVal;
	int length;
        switch (val->header->type) {
		case MULTIFIELD_TYPE:
			retVal.type = CTC_DYNAMIC_LIST;
			length = val->multifieldValue->length;
			retVal.val.values
				= calloc(length+1, sizeof(struct DynamicValue));
			for (int i=0; i<length; i++){
				retVal.val.values[i] = clipsToDynamic(
					val->multifieldValue->contents + i);
			}
			retVal.val.values[length].type = CTC_DYNAMIC_VOID;
			return retVal;
                case INTEGER_TYPE:
			retVal.type = CTC_DYNAMIC_INT;
			retVal.val.integer = val->integerValue->contents;
			return retVal;
                case STRING_TYPE:
                case SYMBOL_TYPE:
					//val.lexemeValue == FalseSymbol(env)
					//val.lexemeValue == TrueSymbol(env)
			if (0==strcmp(val->lexemeValue->contents, "TRUE")){
				retVal.type = CTC_DYNAMIC_BOOL;
				retVal.val.boolean = true;
			} else if (0==strcmp(val->lexemeValue->contents, "FALSE")){
				retVal.type = CTC_DYNAMIC_BOOL;
				retVal.val.boolean = false;
			} else {
				retVal.type = CTC_DYNAMIC_STRING;
				retVal.val.string = (char*)malloc(strlen(val->lexemeValue->contents)+1);
				strcpy(retVal.val.string, val->lexemeValue->contents);
			}
			return retVal;
		case VOID_TYPE:
			retVal.type = CTC_DYNAMIC_VOID;
			retVal.val.content = NULL;
			return retVal;
			//VoidConstant(env)
                case FLOAT_TYPE:
		default:
			retVal.type = CTC_DYNAMIC_ERROR;
			retVal.val.error = CTC_CTD_CANTTRANSLATE;
			return retVal;

	}
}
