#include "timedata_object.h"
#include "macros_date_to_days.h"

static size_t get_match_length(regmatch_t match);

#define MATCHESSIZETIME 12

void normalize_dateTimeStamp(DateTimeStamp *result){
	bool repeat = true;
	while (repeat){
		if (result->month > 12){
			result->month -= 12;
			result->year += 1;
			repeat = true;
		} else if (result->month <1) {
			result->month += 12;
			result->year -= 1;
			repeat = true;
		} else if (MONTH28(result) && result->day > 28){
			result->month += 1;
			result->day -= 28;
			repeat = true;
		} else if (MONTH29(result) && result->day > 29){
			result->month += 1;
			result->day -= 29;
			repeat = true;
		} else if (MONTH30(result) && result->day > 30){
			result->month += 1;
			result->day -= 30;
			repeat = true;
		} else if (result->day > 31){
			result->month += 1;
			result->day -= 31;
			repeat = true;
		} else if (result->day < 1){
			if (MONTH28L(result) && result->day > 28){
				result->month -= 1;
				result->day += 28;
			} else if (MONTH29L(result) && result->day > 29){
				result->month -= 1;
				result->day += 29;
			} else if (MONTH30L(result) && result->day > 30){
				result->month -= 1;
				result->day += 30;
			} else {
				result->month -= 1;
				result->day += 31;
			}
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
		} else {
			repeat = false;
		}
	}
}


void date_regex_to_crifiDateTimeStamp(char *lexical,
			regmatch_t matches[MATCHESSIZETIME],
			DateTimeStamp* result){
	transform_date_match(lexical, matches, result);
	normalize_dateTimeStamp(result);
	result->type = CRIFI_TIME_DATETIMESTAMP_DATE;
}

void dateTimeStamp_regex_to_crifiDateTimeStamp(char *lexical,
			regmatch_t matches[MATCHESSIZETIME],
			DateTimeStamp* result){
	transform_dateTimeStamp_match(lexical, matches, result);
	normalize_dateTimeStamp(result);
	result->type = CRIFI_TIME_DATETIMESTAMP_DATETIME;
}

void time_regex_to_crifiDateTimeStamp(char *lexical,
			regmatch_t matches[MATCHESSIZETIME],
			DateTimeStamp* result){
	transform_time_match(lexical, matches, result);
	normalize_dateTimeStamp(result);
	result->type = CRIFI_TIME_DATETIMESTAMP_TIME;
}


void transform_date_match(char *lexical, regmatch_t matches[MATCHESSIZETIME], DateTimeStamp* result){
	char tmp[5];
	if (matches[1].rm_so >= 0){
		memcpy(tmp, lexical+matches[1].rm_so, 4);
		tmp[4] = '\0';
		result->year = atoi(tmp);
	} else result->year=0;
	if (matches[2].rm_so >= 0){
		memcpy(tmp, lexical+matches[2].rm_so, 2);
		tmp[2] = '\0';
		result->month = atoi(tmp);
	} else result->month=0;
	if (matches[3].rm_so >= 0){
		memcpy(tmp, lexical+matches[3].rm_so, 2);
		tmp[2] = '\0';
		result->day = atoi(tmp);
	} else result->day=0;
	result->hour = 0;
	result->minute = 0;
	result->second = 0;
	result->millisecond = 0;
	result->timezone_minute=0;
	if (matches[5].rm_so >= 0) {//Z (zero)
		result->no_timezone_data = false;
	} else if (matches[6].rm_so >= 0){
		result->no_timezone_data = false;
		memcpy(tmp, lexical+matches[7].rm_so, 2); //hours
		tmp[2] = '\0';
		result->timezone_minute = 60*atoi(tmp);
		memcpy(tmp, lexical+matches[8].rm_so, 2); //minutes
		tmp[2] = '\0';
		result->timezone_minute += atoi(tmp);
		if (lexical[matches[6].rm_so] == '-') {
			result->timezone_minute = - result->timezone_minute;
		} else {// == '+'
		}
	} else {
		result->no_timezone_data = true;
	}
}


void transform_dateTimeStamp_match(
		char *lexical, regmatch_t matches[MATCHESSIZETIME],
	       	DateTimeStamp* result)
{
	char tmp[5];
	int year, month, day, hour, minute, second, millisecond;
	if (matches[1].rm_so >= 0){
		memcpy(tmp, lexical+matches[1].rm_so, 4);
		tmp[4] = '\0';
		result->year = atoi(tmp);
	} else result->year=0;
	if (matches[2].rm_so >= 0){
		memcpy(tmp, lexical+matches[2].rm_so, 2);
		tmp[2] = '\0';
		result->month = atoi(tmp);
	} else result->month=0;
	if (matches[3].rm_so >= 0){
		memcpy(tmp, lexical+matches[3].rm_so, 2);
		tmp[2] = '\0';
		result->day = atoi(tmp);
	} else result->day=0;
	if (matches[4].rm_so >= 0){
		memcpy(tmp, lexical+matches[4].rm_so, 2);
		tmp[2] = '\0';
		result->hour = atoi(tmp);
	} else result->hour=0;
	if (matches[5].rm_so >= 0){
		memcpy(tmp, lexical+matches[5].rm_so, 2);
		tmp[2] = '\0';
		result->minute = atoi(tmp);
	} else result->minute=0;
	if (matches[6].rm_so >= 0){
		memcpy(tmp, lexical+matches[6].rm_so, 2);
		tmp[2] = '\0';
		result->second = atoi(tmp);
	} else result->second=0;
	if (matches[9].rm_so >= 0){
		tmp[0] = lexical[matches[9].rm_so];
		tmp[1] = '\0';
		result->millisecond = 100*atoi(tmp);
	} else result->millisecond=0;
	result->timezone_minute=0;
	if (matches[10].rm_so >= 0) {//Z (zero)
	} else if (matches[11].rm_so >= 0){
		memcpy(tmp, lexical+matches[12].rm_so, 2); //hours
		tmp[2] = '\0';
		result->timezone_minute = 60*atoi(tmp);
		memcpy(tmp, lexical+matches[13].rm_so, 2); //minutes
		tmp[2] = '\0';
		result->timezone_minute += atoi(tmp);
		if (lexical[matches[11].rm_so] == '-') {
			result->timezone_minute = - result->timezone_minute;
		} else {// == '+'
		}
	}
}

void transform_time_match(char *lexical,
		regmatch_t matches[MATCHESSIZETIME],
		DateTimeStamp* result){
	size_t l;
	char tmp[5] = {'\0', '\0', '\0', '\0', '\0'};
	if (lexical == NULL){return;}
	result->year=0;
	result->month=0;
	result->day=0;
	if (matches[1].rm_so >= 0){
		memcpy(tmp, lexical+matches[1].rm_so, 2);
		tmp[2] = '\0';
		result->hour = atoi(tmp);
	} else result->hour=0;
	if (matches[2].rm_so >= 0){
		memcpy(tmp, lexical+matches[2].rm_so, 2);
		tmp[2] = '\0';
		result->minute = atoi(tmp);
	} else result->minute=0;
	if (matches[3].rm_so >= 0){
		memcpy(tmp, lexical+matches[3].rm_so, 2);
		tmp[2] = '\0';
		result->second = atoi(tmp);
	} else result->second=0;
	if (matches[4].rm_so >= 0){
		tmp[0] = lexical[matches[4].rm_so];
		tmp[1] = '\0';
		result->millisecond = 100*atoi(tmp);
	} else result->millisecond=0;

	if (matches[7].rm_so >= 0){
		//this is the Z. im not sure for what z means
		result->timezone_minute = 0;
	} else if (matches[8].rm_so >= 0){
		result->timezone_minute = 0;
		l = get_match_length(matches[9]);
		memcpy(tmp, lexical+matches[9].rm_so, l); //hours
		tmp[l] = '\0';
		result->timezone_minute = 60*atoi(tmp);
		l = get_match_length(matches[10]);
		memcpy(tmp, lexical+matches[10].rm_so, l); //minutes
		tmp[l] = '\0';
		result->timezone_minute += atoi(tmp);
		if (lexical[matches[8].rm_so] == '-') {
			result->timezone_minute = - result->timezone_minute;
		} else {// == '+'
		}
	} else {
		result->timezone_minute = 0;
	}
}


static size_t get_match_length(regmatch_t match){
	return match.rm_eo - match.rm_so;
}
