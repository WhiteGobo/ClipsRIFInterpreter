#include "model_support.h"

//bool skip_modelA(SkipCondition condition){
bool skip_modelA(long unsigned int condition){
	if (condition & (SC_ModelA | SC_All)){
		return true;
	}
	return false;
}

bool skip_model_first(long unsigned int condition){
	if (condition & (SC_ModelFirst | SC_All)){
		return true;
	}
	return false;
}


bool expects_handling_inconsistency(long unsigned int condition){
	if (condition & SC_InconsistencyError){
		return true;
	}
	return false;
}
