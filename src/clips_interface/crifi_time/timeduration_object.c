#include "timeduration_object.h"

void yearMonthDuration_regex_to_crifiDuration(char *lexical, regmatch_t matches[14], CrifiDuration* result){
	char tmp[22];
	size_t l;
	if (result == NULL || lexical == NULL) return;
	//"^P([0-9]+Y)?([0-9]+M)?$",
	if (matches[1].rm_so >= 0){ //there is a '-' as preamble
		result->is_negative_duration = true;
	} else result->is_negative_duration = false;
	if (matches[2].rm_so >= 0){
		l = matches[2].rm_eo - matches[2].rm_so;
		memcpy(tmp, lexical+matches[2].rm_so, l);
		tmp[l] = '\0';
		result->year = atoi(tmp);
	} else result->year=0;
	if (matches[3].rm_so >= 0){
		l = matches[3].rm_eo - matches[3].rm_so;
		memcpy(tmp, lexical+matches[3].rm_so, l);
		tmp[l] = '\0';
		result->month = atoi(tmp);
	} else result->month=0;
	result->day = 0;
	result->hour = 0;
	result->minute = 0;
	result->second = 0;
	result->millisecond = 0;
	normalize_duration(result);
}


void dayTimeDuration_regex_to_crifiDuration(char *lexical, regmatch_t matches[14], CrifiDuration* result){
	//"^P([0-9]+D)?(T([0-9]+H)?([0-9]+M)?([0-9]+S)?)?$",
	char tmp[22];
	size_t l;
	if (result == NULL || lexical == NULL) return;
	if (matches[1].rm_so >= 0){ //there is a '-' as preamble
		result->is_negative_duration = true;
	} else result->is_negative_duration = false;
	result->year=0;
	result->month=0;
	if (matches[2].rm_so >= 0){
		l = matches[2].rm_eo - matches[2].rm_so;
		memcpy(tmp, lexical+matches[2].rm_so, l);
		tmp[l] = '\0';
		result->day = atoi(tmp);
	} else result->day=0;
	if (matches[4].rm_so >= 0){
		l = matches[4].rm_eo - matches[4].rm_so;
		memcpy(tmp, lexical+matches[4].rm_so, l);
		tmp[l] = '\0';
		result->hour = atoi(tmp);
	} else result->hour=0;
	if (matches[5].rm_so >= 0){
		l = matches[5].rm_eo - matches[5].rm_so;
		memcpy(tmp, lexical+matches[5].rm_so, l);
		tmp[l] = '\0';
		result->minute = atoi(tmp);
	} else result->minute=0;
	if (matches[6].rm_so >= 0){
		l = matches[6].rm_eo - matches[6].rm_so;
		memcpy(tmp, lexical+matches[6].rm_so, l);
		tmp[l] = '\0';
		result->second = atoi(tmp);
	} else result->second=0;
	if (matches[7].rm_so >= 0){
		l = matches[8].rm_eo - matches[8].rm_so;
		memcpy(tmp, lexical+matches[8].rm_so, l);
		tmp[l] = '\0';
		if (l==1){
			result->millisecond = 100*atoi(tmp);
		} else if (l==2){
			result->millisecond = 10*atoi(tmp);
		} else { //l==3
			result->millisecond = atoi(tmp);
		}
	} else result->millisecond=0;
	normalize_duration(result);
}


void normalize_duration(CrifiDuration *result){
	bool repeat = true;
	bool applied_invert = false;
	while (repeat){
		if (result->month > 12){
			result->month -= 12;
			result->year += 1;
			repeat = true;
		} else if (result->month < 0) {
			result->month += 12;
			result->year -= 1;
			repeat = true;
		} else if (result->hour >= 24){
			result->day += 1;
			result->hour -= 24;
			repeat = true;
		} else if (result->hour < 0){
			result->day -= 1;
			result->hour += 24;
			repeat = true;
		} else if (result->minute >= 60){
			result->hour += 1;
			result->minute -= 60;
			repeat = true;
		} else if (result->minute < 0){
			result->hour -= 1;
			result->minute += 60;
			repeat = true;
		} else if (result->second >= 60){
			result->minute += 1;
			result->second -= 60;
			repeat = true;
		} else if (result->second < 0){
			result->minute -= 1;
			result->second += 60;
			repeat = true;
		} else if (result->millisecond >= 1000){
			result->second += 1;
			result->millisecond -= 1000;
			repeat = true;
		} else if (result->millisecond < 0){
			result->second -= 1;
			result->millisecond += 1000;
			repeat = true;
		} else if (
				(result->year < 0 || result->day < 0)
				&& !applied_invert)
		{
			applied_invert = true;
			result->year = -result->year;
			result->month = -result->month;
			result->day = -result->day;
			result->hour = -result->hour;
			result->minute = -result->minute;
			result->second = -result->second;
			result->millisecond = -result->millisecond;
			if (result->is_negative_duration){
				result->is_negative_duration = false;
			} else {
				result->is_negative_duration = true;
			}
			repeat = true;
		} else {
			repeat = false;
		}
	}
	if (result->year < 0 || result->month < 0 || result->day < 0 || result->hour < 0 || result->minute < 0 || result->second < 0 || result->millisecond < 0){
		fprintf(stderr, "ERROR: Couldnt normalize duration\n");
	}
}


void transform_yearMonthDuration_match(char *lexical, regmatch_t matches[14], YearMonthDuration* result){
	char tmp[22];
	size_t l;
	//"^P([0-9]+Y)?([0-9]+M)?$",
	if (matches[1].rm_so >= 0){ //there is a '-' as preamble
		result->is_negative_duration = true;
	} else result->is_negative_duration = false;
	if (matches[2].rm_so >= 0){
		l = matches[2].rm_eo - matches[2].rm_so;
		memcpy(tmp, lexical+matches[2].rm_so, l);
		tmp[l] = '\0';
		result->year = atoi(tmp);
	} else result->year=0;
	if (matches[3].rm_so >= 0){
		l = matches[3].rm_eo - matches[3].rm_so;
		memcpy(tmp, lexical+matches[3].rm_so, l);
		tmp[l] = '\0';
		result->month = atoi(tmp);
	} else result->month=0;
}

void transform_dayTimeDuration_match(char *lexical, regmatch_t matches[14], DateTimeStamp* result){
	//"^P([0-9]+D)?(T([0-9]+H)?([0-9]+M)?([0-9]+S)?)?$",
	char tmp[22];
	size_t l;
	if (matches[1].rm_so >= 0){ //there is a '-' as preamble
		result->is_negative_duration = true;
	} else result->is_negative_duration = false;
	result->year=0;
	result->month=0;
	if (matches[2].rm_so >= 0){
		l = matches[2].rm_eo - matches[2].rm_so;
		memcpy(tmp, lexical+matches[2].rm_so, l);
		tmp[l] = '\0';
		result->day = atoi(tmp);
	} else result->day=0;
	if (matches[4].rm_so >= 0){
		l = matches[4].rm_eo - matches[4].rm_so;
		memcpy(tmp, lexical+matches[4].rm_so, l);
		tmp[l] = '\0';
		result->hour = atoi(tmp);
	} else result->hour=0;
	if (matches[5].rm_so >= 0){
		l = matches[5].rm_eo - matches[5].rm_so;
		memcpy(tmp, lexical+matches[5].rm_so, l);
		tmp[l] = '\0';
		result->minute = atoi(tmp);
	} else result->minute=0;
	if (matches[6].rm_so >= 0){
		l = matches[6].rm_eo - matches[6].rm_so;
		memcpy(tmp, lexical+matches[6].rm_so, l);
		tmp[l] = '\0';
		result->second = atoi(tmp);
	} else result->second=0;
	if (matches[7].rm_so >= 0){
		l = matches[8].rm_eo - matches[8].rm_so;
		memcpy(tmp, lexical+matches[8].rm_so, l);
		tmp[l] = '\0';
		if (l==1){
			result->millisecond = 100*atoi(tmp);
		} else if (l==2){
			result->millisecond = 10*atoi(tmp);
		} else { //l==3
			result->millisecond = atoi(tmp);
		}
	} else result->millisecond=0;
	result->timezone_minute=0;
}


CrifiDuration crifi_new_dayTimeDuration(bool invert, int day, int hour, int minute, int seconds, int milliseconds){
	CrifiDuration ret;
	ret.year = 0;
	ret.month = 0;
	ret.day = day;
	ret.hour = hour;
	ret.minute = minute;
	ret.second = seconds;
	ret.millisecond = milliseconds;
	ret.is_negative_duration = invert;

	normalize_duration(&ret);
	return ret;
}

CrifiDuration crifi_new_yearMonthDuration(bool invert, int year, int month){
	CrifiDuration ret;
	ret.year = year;
	ret.month = month;
	ret.day = 0;
	ret.hour = 0;
	ret.minute = 0;
	ret.second = 0;
	ret.millisecond = 0;
	ret.is_negative_duration = invert;

	normalize_duration(&ret);
	return ret;
}
