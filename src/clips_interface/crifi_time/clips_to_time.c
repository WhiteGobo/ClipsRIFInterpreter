#include "crifi_time.h"
#include "crifi_timedata.h"
#include "ffi_constants.h"
#include <math.h>
#include "info_query.h"
#include "timedata_object.h"
#include "timeduration_object.h"

bool crifi_time_clips_to_duration(Environment *env, CLIPSValue *val, CrifiDuration *result){
	char *datatype, *lexical = NULL;
	CRIFITimeData *data = LoadingCRIFITimeData(env);
	int err = -1;
	regmatch_t matches[15];
	datatype = extract_datatype(env, val->header);
	if (datatype == NULL){
		return false;
	}
	lexical = extract_lexical(env, val->header);
	if (lexical == NULL){
		free(datatype);
		return false;
	}
	if (0 == strcmp(datatype, _XS_duration_)){
		err = regexec(&(data->reg_dayTimeDuration), lexical,
						15, matches, 0);
		if (err == 0){
			dayTimeDuration_regex_to_crifiDuration(lexical,
						matches, result);
		} else {
			err = regexec(&(data->reg_yearMonthDuration), lexical,
						15, matches, 0);
			if (err==0){
				yearMonthDuration_regex_to_crifiDuration(
						lexical, matches, result);
			}
		}
	} else if (0 == strcmp(datatype, _XS_dayTimeDuration_)){
		err = regexec(&(data->reg_dayTimeDuration), lexical,
						15, matches, 0);
		if (err == 0){
			dayTimeDuration_regex_to_crifiDuration(lexical,
						matches, result);
		}
	} else if (0 == strcmp(datatype, _XS_yearMonthDuration_)){
		err = regexec(&(data->reg_yearMonthDuration), lexical,
						15, matches, 0);
		if (err==0){
			yearMonthDuration_regex_to_crifiDuration(lexical,
						matches, result);
		}
	} else {
		err = 1;
	}
	free(datatype);
	free(lexical);
	if (err == 0){
		return true;
	} else {
		return false;
	}
}

bool crifi_time_clips_to_time(Environment *env, CLIPSValue *val, DateTimeStamp *result){
	char *datatype, *lexical = NULL;
	CRIFITimeData *data = LoadingCRIFITimeData(env);
	int err = -1;
	regmatch_t matches[MATCHESSIZETIME];
	datatype = extract_datatype(env, val->header);
	if (datatype == NULL){
		return false;
	}
	lexical = extract_lexical(env, val->header);
	if (lexical == NULL){
		free(datatype);
		return false;
	}
	if (0 == strcmp(datatype, _XS_date_)){
		err = regexec(&(data->reg_date), lexical,
						MATCHESSIZETIME, matches, 0);
		if (err==0){
			date_regex_to_crifiDateTimeStamp(lexical,
						matches, result);
		}
	} else if (0 == strcmp(datatype, _XS_dateTimeStamp_)){
		err = regexec(&(data->reg_dateTimeStamp), lexical,
						MATCHESSIZETIME, matches, 0);
		if (err==0){
			dateTimeStamp_regex_to_crifiDateTimeStamp(lexical,
						matches, result);
		}
	} else if (0 == strcmp(datatype, _XS_dateTime_)){
		err = regexec(&(data->reg_dateTime), lexical,
						MATCHESSIZETIME, matches, 0);
		if (err==0){
			dateTimeStamp_regex_to_crifiDateTimeStamp(lexical,
						matches, result);
		}
	} else if (0 == strcmp(datatype, _XS_time_)){
		err = regexec(&(data->reg_time), lexical,
						MATCHESSIZETIME, matches, 0);
		if (err==0){
			time_regex_to_crifiDateTimeStamp(lexical,
						matches, result);
		}
	} else {
		err = 1;
	}
	free(datatype);
	free(lexical);
	if (err == 0){
		return true;
	} else {
		return false;
	}
}

bool crifi_time_time_to_clips(Environment *env, const DateTimeStamp *val, CLIPSValue *result){
	CLIPSValue tmp;
	switch (val->type){
		case CRIFI_TIME_DATETIMESTAMP_DATETIME:
			tmp = crifi_create_dateTime(env, *val);
			result->value = tmp.value;
			return true;
		case CRIFI_TIME_DATETIMESTAMP_TIME:
			tmp = crifi_create_time(env, *val);
			result->value = tmp.value;
			return true;
		case CRIFI_TIME_DATETIMESTAMP_DATE:
			tmp = crifi_create_date(env, *val);
			result->value = tmp.value;
			return true;
		case CRIFI_TIME_DATETIMESTAMP_GYEARMONTH:
		case CRIFI_TIME_DATETIMESTAMP_GYEAR:
		case CRIFI_TIME_DATETIMESTAMP_GMONTHDAY:
		case CRIFI_TIME_DATETIMESTAMP_GMONTH:
		case CRIFI_TIME_DATETIMESTAMP_GDAY:
		case CRIFI_TIME_DATETIMESTAMP_UNKNOWN_TYPE:
		default:
			return false;
	}
}

bool crifi_time_duration_to_clips(Environment *env, CrifiDuration *val, CLIPSValue *result){
	float tmpd;
	bool ym_dur = false, dt_dur = false;
	char outstring[80], tmpout[82+ sizeof(_XS_dayTimeDuration_)];
	int offset = 0;
	if (val->is_negative_duration) {
		offset += sprintf(outstring+offset, "-P");
	} else {
		offset += sprintf(outstring+offset, "P");
	}
	if (val->year > 0){
		ym_dur = true;
		offset += sprintf(outstring+offset, "%dY", val->year);
	}
	if (val->month > 0){
		ym_dur = true;
		offset += sprintf(outstring+offset, "%dM", val->month);
	}
	if (val->day > 0){
		dt_dur = true;
		offset += sprintf(outstring+offset, "%dD", val->day);
	}
	if (val->hour > 0 || val->minute > 0 || val->second> 0 || val->millisecond >0){
		dt_dur = true;
		offset += sprintf(outstring+offset, "T");
		if (val->hour > 0){
			offset += sprintf(outstring+offset, "%dH", val->hour);
		}
		if (val->minute > 0){
			offset += sprintf(outstring+offset, "%dM", val->minute);
		}
		if (val->second > 0 && val->millisecond == 0){
			offset += sprintf(outstring+offset, "%dS", val->second);
		} else if (val->millisecond != 0){
			tmpd = val->second + (((float) val->millisecond)/1000);
			offset += sprintf(outstring+offset, "%.3fS", tmpd);
			//remove trailing '0'
			for (int i=0; i<2; i++){
				if (outstring[offset-2]=='0'){
					sprintf(outstring+offset-3, "S", tmpd);
					offset--;
				}
			}
		}
	}

	if (ym_dur && !dt_dur){
		value_and_datatype_to_slotstring(tmpout,
				outstring, strlen(outstring),
				_XS_yearMonthDuration_,
				sizeof(_XS_yearMonthDuration_));
	} else if (!ym_dur && dt_dur){
		value_and_datatype_to_slotstring(tmpout,
				outstring, strlen(outstring),
				_XS_dayTimeDuration_,
				sizeof(_XS_dayTimeDuration_));
	} else {
		value_and_datatype_to_slotstring(tmpout,
				outstring, strlen(outstring),
				_XS_duration_, sizeof(_XS_duration_));
	}
	result->lexemeValue = CreateString(env, tmpout);
	fprintf(stderr, "duration to clips: %s\n", tmpout);
	return result;
}
