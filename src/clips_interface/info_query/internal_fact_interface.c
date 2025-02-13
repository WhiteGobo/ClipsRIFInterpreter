#include "info_query.h"

#define CHECK_VALID_CLIPSVALUE(val) true

CrifiAssertTripleError assert_triple(Environment *env, CLIPSValue *subject, CLIPSValue *predicate, CLIPSValue *object){
	FactBuilderError error;
	Fact *factaddress;
        FactBuilder *theFB;
	if (!CHECK_VALID_CLIPSVALUE(subject)) return CRIFI_ASSTR_SUBJECT;
	if (!CHECK_VALID_CLIPSVALUE(predicate)) return CRIFI_ASSTR_PREDICATE;
	if (!CHECK_VALID_CLIPSVALUE(object)) return CRIFI_ASSTR_OBJECT;
        theFB = CreateFactBuilder(env, TRIPLETEMPLATE);
	FBPutSlot(theFB, TRIPLESLOTSUBJECT, subject);
	FBPutSlot(theFB, TRIPLESLOTPREDICATE, predicate);
	FBPutSlot(theFB, TRIPLESLOTOBJECT, object);
	FBPutSlotSymbol(theFB, TRIPLESLOTCONTEXT, "");

        factaddress = FBAssert(theFB);
        FBDispose(theFB);
	if (factaddress == NULL){
		error = FBError(env);
		switch (error) {
			case FBE_NO_ERROR:
				break;
			case FBE_NULL_POINTER_ERROR:
			case FBE_IMPLIED_DEFTEMPLATE_ERROR:
			case FBE_DEFTEMPLATE_NOT_FOUND_ERROR:
			case FBE_COULD_NOT_ASSERT_ERROR:
			case FBE_RULE_NETWORK_ERROR:
			default:
				return CRIFI_ASSTR_UNKNOWN;
		}
	}
	return CRIFI_ASSTR_NO_ERROR;
}
