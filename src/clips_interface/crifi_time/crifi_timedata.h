#pragma once

#include <clips.h>
#include <regex.h>

/** CRIFI_TIME_DATA_INDEX
 * index in which clips Environment stores data needed for crifi_time.
 * Can be overwritten if there is an index conflict.
 * Otherwise will be internally handled.
 */
#ifndef CRIFI_TIME_DATA_INDEX
#define CRIFI_TIME_DATA_INDEX USER_ENVIRONMENT_DATA + 1
#endif

typedef struct crifiTimeData{
	regex_t reg_date;
	regex_t reg_dateTime;
	regex_t reg_dateTimeStamp;
	regex_t reg_time;
	regex_t reg_dayTimeDuration;
	regex_t reg_yearMonthDuration;
	regex_t reg_generalDuration;
} CRIFITimeData;

/** LoadingCRIFITimeData
 */
#define LoadingCRIFITimeData(theEnv) \
	((struct crifiTimeData *) GetEnvironmentData(theEnv,CRIFI_TIME_DATA_INDEX))


bool crifi_timedata_register_data(Environment *env);
bool initialize_crifi_timedata(CRIFITimeData *data);
void free_crifi_timedata(CRIFITimeData *data);
