#pragma once

#include <ffi_clips_interface.h>

#ifndef CRIFI_IMPORT_DATA_INDEX
#define CRIFI_IMPORT_DATA_INDEX USER_ENVIRONMENT_DATA + 3
#endif

typedef struct crifiImportData{
} CRIFIImportData;

/** LoadingCRIFIImportData
 */
#define LoadingCRIFIImportData(theEnv) \
	((struct crifiImportData *) GetEnvironmentData(theEnv, CRIFI_IMPORT_DATA_INDEX))


#ifdef __cplusplus
extern "C" {
#endif

bool crifi_importdata_register_data(Environment *env);

#ifdef __cplusplus
}
#endif
