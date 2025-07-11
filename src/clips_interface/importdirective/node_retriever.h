#include "clipsvalue_interface.h"

typedef void CRIFIImportClipsvalueRetrieverCleanupFunction(void *context);

typedef struct clipsvalueRetriever {
	ClipsvalueRetrieveFunction* function;
	void *context;
	struct clipsvalueRetriever* next;
	CRIFIImportDataCleanupFunction *cleanup_function;
} ClipsvalueRetriever;
