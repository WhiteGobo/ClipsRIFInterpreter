#include "crifi_objects.h"

static IEQ_RET compare_atom_lists(Environment *env, Instance *left, Instance *right){
	GetSlotError err;
	CLIPSValue litems, ritems;
	err = DirectGetSlot(left, "items", &litems);
	if (err != GSE_NO_ERROR) {
		return IEQ_ERROR;
	}
	err = DirectGetSlot(right, "items", &ritems);
	if (err != GSE_NO_ERROR) {
		return IEQ_ERROR;
	}
	return internal_equal(env, &litems, &ritems);
}

static IEQ_RET compare_instances(Environment *env, Instance *linstance, Instance *rinstance){
	char *tmp;
	const char *classname;
	Defclass *lclass, *rclass, *atomListClass;
	if (linstance == rinstance) return true;
	lclass = InstanceClass(linstance);
	rclass = InstanceClass(rinstance);
	if (lclass != rclass) return false;
	atomListClass = FindDefclass(env, "AtomList");
	if (atomListClass == NULL){
		return IEQ_ERROR;
	}
	if (lclass == atomListClass){
		return compare_atom_lists(env, linstance, rinstance);
	}
	return IEQ_FALSE;
}


IEQ_RET internal_equal(Environment *env, CLIPSValue *left, CLIPSValue *right){
	bool check;
	IEQ_RET checka;
	size_t length;
	unsigned short ltype, rtype;
	Instance *linst, *rinst;
	ltype = left->header->type;
	rtype = right->header->type;
	if((ltype != rtype)
			&& !(((ltype == INSTANCE_NAME_TYPE)
					|| (ltype == INSTANCE_ADDRESS_TYPE))
				&& ((rtype == INSTANCE_NAME_TYPE)
					|| (rtype == INSTANCE_ADDRESS_TYPE) ) ) ){
		return false;
	}
	switch (left->header->type){
		case VOID_TYPE:
			return true; break;
		case STRING_TYPE:
		case SYMBOL_TYPE:
			if (left->lexemeValue == right->lexemeValue){
				return IEQ_TRUE;
			} else {
				if (0==strcmp(left->lexemeValue->contents,
						right->lexemeValue->contents)){
					return IEQ_TRUE;
				} else {return IEQ_FALSE;}
			}
			break;
		case INSTANCE_ADDRESS_TYPE:
		case INSTANCE_NAME_TYPE:
			if (ltype == INSTANCE_NAME_TYPE) {
				linst = FindInstance(env, NULL, left->lexemeValue->contents, true);
			} else if (ltype == INSTANCE_ADDRESS_TYPE){
				linst = left->instanceValue;
			}
			if (rtype == INSTANCE_NAME_TYPE) {
				rinst = FindInstance(env, NULL, right->lexemeValue->contents, true);
			} else if (rtype == INSTANCE_ADDRESS_TYPE){
				rinst = right->instanceValue;
			}
			if (linst == NULL || rinst == NULL) return IEQ_ERROR;
			if (compare_instances(env, linst, rinst)){
				return IEQ_TRUE;
			} else {return IEQ_FALSE;}
			break;
		case MULTIFIELD_TYPE:
			length = left->multifieldValue->length;
			if (length != right->multifieldValue->length)return false;
			for(int i = 0; i< length; i++){
				checka = internal_equal(env,
					left->multifieldValue->contents + i,
					right->multifieldValue->contents + i);
				if (checka != IEQ_TRUE) return checka;
			}
			return IEQ_TRUE;
			break;
	}
	return IEQ_ERROR;
}

