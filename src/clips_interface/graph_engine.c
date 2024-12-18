#include "ffi_clips_interface.h"
#include "graph_engine.h"
#include <clips.h>
#include "dataspace_constants.h"
#include <n3parser.h>
#include <external_functions.h>

CLIPSValue getFactsFromEnvironment(Environment *env){
	CLIPSValue retList;
	GetFactList(env, &retList, NULL);
	if (retList.header->type != MULTIFIELD_TYPE){
		retList.header = NULL;
		return retList;
	}
	return retList;
	//return retList.multifieldValue->length;
}

/**
 * See also 'https://www.w3.org/TR/2013/REC-rif-bld-20130205/#Terms'_
 */
static const char *templates[] = {
	"(deftemplate TripleTemplate\n"
		"	(slot subject)\n"
		"	(slot predicate)\n"
		"	(slot object)\n"
		"	(slot context))\n",

	"(deftemplate Atom\n"
		"	(slot op)\n"
		"	(multislot args))\n",

	"(deftemplate Subclass\n"
		"	(slot sub)\n"
		"	(slot super))\n",

	"(deftemplate Member\n"
		"	(slot instance)\n"
		"	(slot class))\n",

	"(deftemplate Equal\n"
		"	(slot left)\n"
		"	(slot right))\n",

	"(deftemplate AtomList (multislot items))",

	NULL
};

static const char *baserules[] = {
	"(defrule rule1\n"
		"	(Subclass (sub ?cls) (super ?extracls))\n"
		"	(Member (instance ?x) (class ?cls))\n"
		"	=>\n"
		"	(assert (Member (instance ?x) (class ?extracls)))\n"
		")",
	
	//"(defrule remove-unneeded atomlists)"

	NULL
};

static bool load_basic_templates(Environment *env) {
	for (const char **deftempl = templates; *deftempl != NULL; deftempl++){
		BuildError err = Build(env, *deftempl);
		switch (err) {
			case BE_PARSING_ERROR:
				fprintf(stderr, "Critical Internal error. "
						"Failed loading basic "
						"templates. happened "
						"with: '%s'\n", *deftempl);
				return false;
				break;
			case BE_NO_ERROR:
				break;
		}
	}
	for (const char **defrule = baserules; *defrule != NULL; defrule++){
		BuildError err = Build(env, *defrule);
		switch (err) {
			case BE_PARSING_ERROR:
				fprintf(stderr, "Critical Internal error. "
						"Failed loading basic "
						"templates. happened "
						"with: '%s'\n", *defrule);
				return false;
				break;
			case BE_NO_ERROR:
				break;
		}
	}
	return true;
}

Environment *initEnvironment(){
	Environment *env = CreateEnvironment();
	load_basic_templates(env);
	if(!add_literal_user_functions(env)) {
		fprintf(stderr, "initEnvironment failed cause userfunctions.");
		DestroyEnvironment(env);
		return NULL;
	}
	return env;
}

LoadError load_config_internal(Environment *env, const char *fileName){
	return Load(env, fileName);
}

bool load_config_internal_mem(Environment *env, const char* string_config, size_t string_length){
	return LoadFromString(env, string_config, string_length);
}

bool closeEnvironment(Environment *env){
	Reset(env); //ensure environment isnt executing(??see documentation)
	return DestroyEnvironment(env);
}


CRI_RET_BUILDTRIPLE build_triple(Environment* env, Utf8String subject, Utf8String predicate, Utf8String object, Utf8String context){
	int err;
	FactBuilderError error;
	Fact *factaddress;
        FactBuilder *theFB;
        theFB = CreateFactBuilder(env, TRIPLETEMPLATE);
	//FBPutSlotSymbol(theFB, TRIPLESLOTSUBJECT, subject);
	err = add_n3_as_expression_at_slot(theFB, subject, TRIPLESLOTSUBJECT);
	if (err != 0) return err + 10;
	//FBPutSlotSymbol(theFB, TRIPLESLOTPREDICATE, predicate);
	err = add_n3_as_expression_at_slot(theFB, predicate, TRIPLESLOTPREDICATE);
	if (err != 0) return err + 20;
	//FBPutSlotSymbol(theFB, TRIPLESLOTOBJECT, object);
	err = add_n3_as_expression_at_slot(theFB, object, TRIPLESLOTOBJECT);
	if (err != 0) return err + 30;
	FBPutSlotSymbol(theFB, TRIPLESLOTCONTEXT, context);

        factaddress = FBAssert(theFB);
        FBDispose(theFB);
	if (factaddress == NULL){
		error = FBError(env);
		switch (error) {
			case FBE_NO_ERROR:
				break;
			case FBE_NULL_POINTER_ERROR:
				return 1;
				break;
			case FBE_DEFTEMPLATE_NOT_FOUND_ERROR:
				return 2;
				break;
			case FBE_IMPLIED_DEFTEMPLATE_ERROR:
				return 3;
				break;
			case FBE_COULD_NOT_ASSERT_ERROR:
				return 4;
				break;
			case FBE_RULE_NETWORK_ERROR:
				return 5;
				break;
		}
	}
	return CRI_RET_BUILDTRIPLE_NOERROR;
}

/* Just a prototype
void buildFact(Environment* env, void *myPointer, Fact *fact){
        FactBuilder *theFB;
        CLIPSValue cv;
        CLIPSExternalAddress *extAddr;
        theFB = CreateFactBuilder(env,"person");

        FBPutSlotString(theFB,"name","Mary Sue Smith");
        FBPutSlotSymbol(theFB,"gender","female");
        FBPutSlotInteger(theFB,"age",25);
        FBPutSlotFact(theFB,"randomfact", fact);
        extAddr = CreateCExternalAddress(env, myPointer);
        FBPutSlotCLIPSExternalAddress(theFB, "age", extAddr);
        FBAssert(theFB);
        FBDispose(theFB);
}
*/


/*
 *
 * blueprint for how to handle CLIPSValue
        switch (retList.header->type) {
                case EXTERNAL_ADDRESS_TYPE:
			return 0;
                        //printf("is external address %d\n", cv->externalAddressValue->contents);
                        break;
                case FACT_ADDRESS_TYPE:
			return 12;
                        //printf("is a fact address\n");
                        break;
                case FLOAT_TYPE:
                        //printf("is a float %f\n", retList->floatValue->contents);
			return 2;
                        break;
                case INSTANCE_ADDRESS_TYPE:
                        printf("is ainstance address\n");
			return 3;
                        break;
		case INSTANCE_NAME_TYPE:
                        printf("is an instance name\n");
			return 4;
                        break;
                case INTEGER_TYPE:
                        printf("is an integer\n");
			return 5;
                        break;
                case MULTIFIELD_TYPE:
                        printf("is a multifield\n");
			return 6;
                        break;
                case STRING_TYPE:
                        printf("is a string\n");
			return 7;
                        break;
                case SYMBOL_TYPE:
                        printf("is a symbol\n");
			return 8;
                        break;
                case VOID_TYPE:
                        printf("is nothing\n");
			return 9;
                        break;
        }
	*/
