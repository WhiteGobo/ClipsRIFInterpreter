#include "clipsvalue_interface.h"

typedef struct clipsvalueRetriever {
	ClipsvalueRetrieveFunction* function;
	void *context;
	struct clipsvalueRetriever* next;
} ClipsvalueRetriever;
