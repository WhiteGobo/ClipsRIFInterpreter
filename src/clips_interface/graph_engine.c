#include "ffi_clips_interface.h"
#include "graph_engine.h"
#include <clips.h>
#include "dataspace_constants.h"
#include <n3parser.h>
#include <external_functions.h>
#include <crifi_timedata.h>

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
 * All Atomic formulas except externally defined atomic formulas
 * should be representable by a deftemplate.
 * See `https://www.w3.org/TR/2013/REC-rif-prd-20130205/#Atomic_formulas`_ for
 * more information about Atomic Formulas.
 *
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

	if(!crifi_n3parserdata_register_data(env)){
		fprintf(stderr, "initEnvironment failed cause n3parser "
				"couldnt initialize data.");
		DestroyEnvironment(env);
		return NULL;
	}

	if(!crifi_timedata_register_data(env)){
		fprintf(stderr, "initEnvironment failed cause crifi_time "
				"couldnt initialize data.");
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
	CLIPSValue tmpval;
        theFB = CreateFactBuilder(env, TRIPLETEMPLATE);
	err = n3_as_clipsvalue(env, subject, &tmpval);
	if (err == 1){
		return CRI_RET_PARSING_ERROR_SUBJECT;
	} else if (err != 0){
		return CRI_RET_INTERNAL_ERROR;
	}
	FBPutSlot(theFB, TRIPLESLOTSUBJECT, &tmpval);
	err = n3_as_clipsvalue(env, predicate, &tmpval);
	if (err == 1){
		return CRI_RET_PARSING_ERROR_PREDICATE;
	} else if (err != 0){
		return CRI_RET_INTERNAL_ERROR;
	}
	FBPutSlot(theFB, TRIPLESLOTPREDICATE, &tmpval);
	err = n3_as_clipsvalue(env, object, &tmpval);
	if (err == 1){
		return CRI_RET_PARSING_ERROR_OBJECT;
	} else if (err != 0){
		return CRI_RET_INTERNAL_ERROR;
	}
	FBPutSlot(theFB, TRIPLESLOTOBJECT, &tmpval);
	FBPutSlotSymbol(theFB, TRIPLESLOTCONTEXT, context);

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
				return CRI_RET_MISSING_TRIPLE_TEMPLATE;
				break;
			case FBE_COULD_NOT_ASSERT_ERROR:
				return CRI_RET_NOT_ASSERT_ERROR;
				break;
			case FBE_RULE_NETWORK_ERROR:
				return CRI_RET_BROKEN_RULE_NETWORK;
				break;
			default:
				return CRI_RET_INTERNAL_ERROR;
		}
	}
	return CRI_RET_BUILDTRIPLE_NOERROR;
}
