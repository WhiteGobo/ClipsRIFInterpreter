#include "crifi_timedata.h"

/**
 * method given at registration for tidying up timedata after Environment is
 * freed
 */
static void release_crifi_timedata(Environment *env){
	free_crifi_timedata(LoadingCRIFITimeData(env));
}

bool crifi_timedata_register_data(Environment *env){
	if (! AllocateEnvironmentData(env, CRIFI_TIME_DATA_INDEX,
						sizeof(CRIFITimeData),
						release_crifi_timedata))
	{
		Writeln(env, "Internal error 0. "
				"Cant load plugin for builtin time functions.");
		ExitRouter(env, EXIT_FAILURE);
		return false;
	}
	if(!initialize_crifi_timedata(LoadingCRIFITimeData(env))){
		return false;
	}
	return true;
}


//see rfc3339 `https://www.rfc-editor.org/rfc/rfc3339`_

#define _DIGIT "([0-9])"
#define _2DIGIT "([0-9][0-9])"
#define _4DIGIT "([0-9][0-9][0-9][0-9])"
#define DATE_FULLYEAR _4DIGIT
#define DATE_MONTH _2DIGIT
#define DATE_MDAY _2DIGIT
#define TIME_HOUR _2DIGIT
#define TIME_MINUTE _2DIGIT
#define TIME_SECOND _2DIGIT
#define TIME_SECFRAC "."_DIGIT
#define TIME_NUMOFFSET "[+-]" TIME_HOUR ":" TIME_MINUTE
#define TIME_OFFSET "(([Zz])|(" TIME_NUMOFFSET "))?"

#define PARTIAL_TIME TIME_HOUR ":" TIME_MINUTE ":" TIME_SECOND \
			"("TIME_SECFRAC")?"
#define FULL_DATE DATE_FULLYEAR "-" DATE_MONTH "-" DATE_MDAY
#define FULL_TIME PARTIAL_TIME TIME_OFFSET

#define DATE FULL_DATE TIME_OFFSET
#define DATE_TIME FULL_DATE "[Tt]" PARTIAL_TIME
#define DATE_TIME_STAMP FULL_DATE "[Tt]" FULL_TIME


bool initialize_crifi_timedata(CRIFITimeData *data){
	int err;
	err = regcomp(&(data->reg_date),
			"^"DATE"$",
			REG_EXTENDED);
	if (err != 0){
		free_crifi_timedata(data);
		return false;
	}
	err = regcomp(&(data->reg_dateTime),
			"^"DATE_TIME_STAMP"$",
			REG_EXTENDED);
	if (err != 0){
		free_crifi_timedata(data);
		return false;
	}
	err = regcomp(&(data->reg_dateTimeStamp),
			"^"DATE_TIME_STAMP"$",
			REG_EXTENDED);
	if (err != 0){
		free_crifi_timedata(data);
		return false;
	}
	err = regcomp(&(data->reg_time),
			"^"FULL_TIME"$",
			REG_EXTENDED);
	if (err != 0){
		free_crifi_timedata(data);
		return false;
	}
	err = regcomp(&(data->reg_dayTimeDuration),
			"^(-)?P([0-9]+D)?(T([0-9]+H)?([0-9]+M)?([0-9]+(.([0-9]))S)?)?$",
			REG_EXTENDED);
	if (err != 0){
		free_crifi_timedata(data);
		return false;
	}
	err = regcomp(&(data->reg_yearMonthDuration),
			"^(-)?P([0-9]+Y)?([0-9]+M)?$",
			REG_EXTENDED);
	if (err != 0){
		free_crifi_timedata(data);
		return false;
	}
	return true;
}

void free_crifi_timedata(CRIFITimeData *data){
	regfree(&(data->reg_date));
	regfree(&(data->reg_dateTime));
	regfree(&(data->reg_dateTimeStamp));
	regfree(&(data->reg_time));
	regfree(&(data->reg_dayTimeDuration));
	regfree(&(data->reg_yearMonthDuration));
}
