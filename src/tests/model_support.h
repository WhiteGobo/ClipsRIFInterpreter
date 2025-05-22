#pragma once

#include <stdbool.h>

typedef enum {
	SC_NoCondition = 0,
	SC_All = 1<<1,
	SC_ModelA = 1<<2,
	SC_ModelFirst = 1<<3,
	SC_InconsistencyError = 1<<4,
} SkipCondition;


#ifdef __cplusplus
extern "C" {
#endif

//bool skip_modelA(SkipCondition condition);
bool skip_modelA(long unsigned int condition);
bool skip_model_first(long unsigned int condition);
bool expects_handling_inconsistency(long unsigned int condition);

#ifdef __cplusplus
}
#endif
