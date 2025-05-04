#pragma once

#include <stdbool.h>

typedef enum {
	SC_NoCondition = 0,
	SC_All = 1<<1,
	SC_ModelA = 1<<2,
	SC_ModelFirst = 1<<3,
} SkipCondition;


#ifdef __cplusplus
extern "C" {
#endif

//bool skip_modelA(SkipCondition condition);
bool skip_modelA(long unsigned int condition);

#ifdef __cplusplus
}
#endif
