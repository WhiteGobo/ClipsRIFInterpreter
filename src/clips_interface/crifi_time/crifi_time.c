#include "crifi_time.h"
#include "crifi_timedata.h"
#include <n3parser.h>
#include "ffi_constants.h"
#include <math.h>
#include "timedata_object.h"
#include "timeduration_object.h"

#include "macros_date_to_days.h"

static void normalize_dayTimeDuration(DateTimeStamp *result){
	result->second += result->millisecond / 1000;
	result->millisecond = result->millisecond % 1000;
	if (result->millisecond < 0) {
		result->millisecond += 1000;
		result->second -= 1;
	}
	result->minute += result->second / 60;
	result->second = result->second % 60;
	if (result->second < 0) {
		result->second += 60;
		result->minute -= 1;
	}
	result->hour += result->minute / 60;
	result->minute = result->minute % 60;
	if (result->minute < 0) {
		result->minute += 60;
		result->hour -= 1;
	}
	result->day += result->hour / 24;
	result->hour = result->hour % 24;
	if (result->hour < 0) {
		result->hour += 24;
		result->day -= 1;
	}

	if (result->day < 0){
		result->is_negative_duration = !result->is_negative_duration;
		if (result->millisecond > 0){
			result->millisecond = 1000 - result->millisecond;
			result->second += 1;
		}
		if (result->second > 0){
			result->second = 60 - result->second;
			result->minute += 1;
		}
		if (result->minute > 0){
			result->minute = 60 - result->minute;
			result->hour += 1;
		}
		if (result->hour > 0){
			result->hour = 24 - result->hour;
			result->day += 1;
		}
		result->day = - result->day;
	}
}


bool check_is_date(Environment *env, CLIPSValue val, DateTimeStamp *result){
	int err;
	char *datatype, *lexical;
	CRIFITimeData *data = LoadingCRIFITimeData(env);
	regmatch_t matches[15];

	if (val.header->type != STRING_TYPE){
		return false;
	}
	datatype = lexeme_extract_datatype(env, val.lexemeValue);
	if (0!=strcmp(datatype, _XS_date_)){
		free(datatype);
		return false;
	}
	free(datatype);
	lexical = lexeme_extract_lexical(env, val.lexemeValue);

	err = regexec(&(data->reg_date), lexical, 15, matches, 0);
	if (err!=0){
		free(lexical);
		return false;
	} else if (result != NULL){
		transform_date_match(lexical, matches, result);
		normalize_dateTimeStamp(result);
	}
	free(lexical);
	return true;
}


bool check_is_dateTime(Environment *env, CLIPSValue val, DateTimeStamp *result){
	int err;
	char *datatype, *lexical;
	CRIFITimeData *data = LoadingCRIFITimeData(env);
	regmatch_t matches[14];

	datatype = lexeme_extract_datatype(env, val.lexemeValue);
	if (datatype == NULL){
		return false;
	}
	if (0!=strcmp(datatype, _XS_dateTime_)){
		free(datatype);
		return false;
	}
	free(datatype);
	lexical = lexeme_extract_lexical(env, val.lexemeValue);

	err = regexec(&(data->reg_dateTime), lexical, 14, matches, 0);
	if (err!=0){
		free(lexical);
		return false;
	} else if (result != NULL){
		transform_dateTimeStamp_match(lexical, matches, result);
		normalize_dateTimeStamp(result);
	}
	free(lexical);
	return true;
}

bool check_is_dateTimeStamp(Environment *env, CLIPSValue val, DateTimeStamp *result){
	int err;
	char *datatype, *lexical;
	CRIFITimeData *data = LoadingCRIFITimeData(env);
	regmatch_t matches[14];

	if (val.header->type != STRING_TYPE){
		return false;
	}
	datatype = lexeme_extract_datatype(env, val.lexemeValue);
	if (0!=strcmp(datatype, _XS_dateTimeStamp_)){
		free(datatype);
		return false;
	}
	free(datatype);
	lexical = lexeme_extract_lexical(env, val.lexemeValue);

	err = regexec(&(data->reg_dateTimeStamp), lexical, 14, matches, 0);
	if (err!=0){
		free(lexical);
		return false;
	} else if (result != NULL){
		transform_dateTimeStamp_match(lexical, matches, result);
		normalize_dateTimeStamp(result);
	}
	free(lexical);
	return true;
}


bool check_is_time(Environment *env, CLIPSValue val, DateTimeStamp *result){
	int err;
	char *datatype, *lexical;
	CRIFITimeData *data = LoadingCRIFITimeData(env);
	regmatch_t matches[MATCHESSIZETIME];

	if (val.header->type != STRING_TYPE){
		return false;
	}
	datatype = lexeme_extract_datatype(env, val.lexemeValue);
	if (0!=strcmp(datatype, _XS_time_)){
		free(datatype);
		return false;
	}
	free(datatype);
	lexical = lexeme_extract_lexical(env, val.lexemeValue);

	err = regexec(&(data->reg_time), lexical, MATCHESSIZETIME, matches, 0);
	if (err!=0){
		free(lexical);
		return false;
	} else if (result != NULL){
		transform_time_match(lexical, matches, result);
		normalize_dateTimeStamp(result);
	}
	free(lexical);
	return true;
}


bool check_is_dayTimeDuration(Environment *env, CLIPSValue val, DateTimeStamp *result){
	int err;
	char *datatype, *lexical;
	CRIFITimeData *data = LoadingCRIFITimeData(env);
	regmatch_t matches[10];

	if (val.header->type != STRING_TYPE){
		return false;
	}
	datatype = lexeme_extract_datatype(env, val.lexemeValue);
	if (0!=strcmp(datatype, _XS_dayTimeDuration_)){
		free(datatype);
		return false;
	}
	free(datatype);
	lexical = lexeme_extract_lexical(env, val.lexemeValue);

	err = regexec(&(data->reg_dayTimeDuration), lexical, 10, matches, 0);
	if (err!=0){
		free(lexical);
		return false;
	} else if (result != NULL){
		transform_dayTimeDuration_match(lexical, matches, result);
		normalize_dayTimeDuration(result);
	}
	free(lexical);
	return true;
}

static void normalize_yearMonthDuration(YearMonthDuration *result){
	result->year += result->month / 12;
	result->month = result->month % 12;
	if (result->month < 0) {
		result->month += 12;
		result->year -= 1;
	}
	if (result->year < 0){
		result->is_negative_duration = !result->is_negative_duration;
		result->year = -(result->year);
		if (result->month > 0) {
			result->month = 12 - result->month;
			result->year -= 1;
		}
	}
}

bool check_is_yearMonthDuration(Environment *env, CLIPSValue val, YearMonthDuration *result){
	int err;
	char *datatype, *lexical;
	CRIFITimeData *data = LoadingCRIFITimeData(env);
	regmatch_t matches[10];

	if (val.header->type != STRING_TYPE){
		return false;
	}
	datatype = lexeme_extract_datatype(env, val.lexemeValue);
	if (0!=strcmp(datatype, _XS_yearMonthDuration_)){
		free(datatype);
		return false;
	}
	free(datatype);
	lexical = lexeme_extract_lexical(env, val.lexemeValue);

	err = regexec(&(data->reg_yearMonthDuration), lexical, 10, matches, 0);
	if (err!=0){
		free(lexical);
		return false;
	} else if (result != NULL){
		transform_yearMonthDuration_match(lexical, matches, result);
		normalize_yearMonthDuration(result);
	}
	free(lexical);
	return true;
}


CLIPSValue crifi_create_dayTimeDuration(Environment *env, bool invert, int day, int hour, int minute, int seconds, int milliseconds){
	float tmpd;
	char outstring[80], tmpout[82+ sizeof(_XS_dayTimeDuration_)];
	int offset = 0;
	CLIPSValue result;
	DateTimeStamp q = {
		0, 0, day, hour, minute, seconds, milliseconds, 0, invert
	};
	normalize_dayTimeDuration(&q);
	if (q.is_negative_duration) {
		offset += sprintf(outstring+offset, "-P");
	} else {
		offset += sprintf(outstring+offset, "P");
	}
	if (q.day > 0){
		offset += sprintf(outstring+offset, "%dD", q.day);
	}
	if (q.hour > 0 || q.minute > 0 || q.second> 0 || q.millisecond >0){
		offset += sprintf(outstring+offset, "T");
		if (q.hour > 0){
			offset += sprintf(outstring+offset, "%dH", q.hour);
		}
		if (q.minute > 0){
			offset += sprintf(outstring+offset, "%dM", q.minute);
		}
		if (q.second > 0 && q.millisecond == 0){
			offset += sprintf(outstring+offset, "%dS", q.second);
		} else if (q.millisecond != 0){
			tmpd = q.second + (((float) q.millisecond)/1000);
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

	value_and_datatype_to_slotstring(tmpout,
			outstring, strlen(outstring),
			_XS_dayTimeDuration_, sizeof(_XS_dayTimeDuration_));
	result.lexemeValue = CreateString(env, tmpout);
	return result;
}


YearMonthDuration add_yearMonthDuration(YearMonthDuration val1, YearMonthDuration val2){
	if (val1.is_negative_duration != val2.is_negative_duration){
		val1.year -= val2.year;
		val1.month -= val2.month;
	} else {
		val1.year += val2.year;
		val1.month += val2.month;
	}
	normalize_yearMonthDuration(&val1);
	return val1;
}

YearMonthDuration subtract_yearMonthDuration(YearMonthDuration val1, YearMonthDuration val2){
	val2.is_negative_duration = !val2.is_negative_duration;
	return add_yearMonthDuration(val1, val2);
}


YearMonthDuration divide_yearMonthDuration(YearMonthDuration dur, float mult){
	YearMonthDuration ret;
	float months;
	long lmonths;
	months = (12*dur.year) + dur.month;
	months /= mult;
	lmonths = lround(months);
	ret.year = lmonths / 12;
	ret.month = lmonths % 12;
	ret.is_negative_duration = dur.is_negative_duration;
	return ret;
}

NumericValue divide_yearMonthDuration_by_yearMonthDuration(YearMonthDuration dur1, YearMonthDuration dur2){
	NumericValue ret;
	ret.t = NT_RATIONAL;
	if (dur1.is_negative_duration){
		ret.dividend = -((12*dur1.year) + dur1.month);
	} else {
		ret.dividend = (12*dur1.year) + dur1.month;
	}
	if (dur2.is_negative_duration){
		ret.divisor = -((12*dur2.year) + dur2.month);
	} else {
		ret.divisor = (12*dur2.year) + dur2.month;
	}
	return ret;
}


/**
 * This function has to consider precision of multiplication to get precision
 * expected in tests
 */
DateTimeStamp multiply_dayTimeDuration(DateTimeStamp dur, float mult){
	double prec;
	if (dur.millisecond != 0){
		prec = 1 * mult/10000;
	} else if (dur.second != 0){
		prec = 1000 * mult/10000;
	} else if (dur.minute != 0){
		prec = 60000 * mult/10000;
	} else {
		prec = 3600000 * mult/10000;
	}
	double tmp;
	if (mult < 0) dur.is_negative_duration = !dur.is_negative_duration;
	mult = fabsf(mult);
	tmp = mult * (float) dur.day;
	dur.day = tmp;
	tmp = 24*(tmp - dur.day) + (mult * (double) dur.hour);
	if (prec > 3600000) {
		dur.hour = lround(tmp);
		dur.minute = 0;
		dur.second = 0;
		dur.millisecond = 0;
		return dur;
	}
	dur.hour = tmp;
	tmp = 60*(tmp - dur.hour) + (mult * (double) dur.minute);
	if (prec > 60000) {
		dur.minute = lround(tmp);
		dur.second = 0;
		dur.millisecond = 0;
		return dur;
	}
	dur.minute = tmp;
	tmp = 60*(tmp - dur.minute) + (mult * (double) dur.second);
	if (prec > 1000) {
		dur.second = lround(tmp);
		dur.millisecond = 0;
		return dur;
	}
	dur.second = tmp;
	tmp = 1000*(tmp - dur.second) + (mult * (double) dur.millisecond);
	if (prec < 1) {
		dur.millisecond = lround(tmp);
	} else {
		dur.millisecond = 100*lround(tmp/100);
	}
	return dur;
}


NumericValue divide_dayTimeDuration_by_dayTimeDuration(DateTimeStamp dur1, DateTimeStamp dur2){
	NumericValue ret;
	int deep;
	long long ms1, ms2;
	if (dur1.millisecond != 0 || dur2.millisecond != 0){
		deep = 4;
	} else if (dur1.second != 0 || dur2.second != 0){
		deep = 3;
	} else if (dur1.minute != 0 || dur2.minute != 0){
		deep = 2;
	} else if (dur1.hour != 0 || dur2.hour != 0){
		deep = 1;
	} else {
		deep = 0;
	}
	ms1 = dur1.day;
	ms2 = dur2.day;
	switch (deep){
		case 1:
			ms1 *= 24;
			ms1 += dur1.hour;
			ms2 *= 24;
			ms2 += dur2.hour;
		case 2:
			ms1 *= 60;
			ms1 += dur1.minute;
			ms2 *= 60;
			ms2 += dur2.minute;
		case 3:
			ms1 *= 60;
			ms1 += dur1.second;
			ms2 *= 60;
			ms2 += dur2.second;
		case 4:
			ms1 *= 1000;
			ms1 += dur1.millisecond;
			ms2 *= 1000;
			ms2 += dur2.millisecond;
	}
	ret.t = NT_RATIONAL;
	if (dur1.is_negative_duration == dur2.is_negative_duration){
		ret.dividend = ms1;
	} else {
		ret.dividend = -ms1;
	}
	ret.divisor = ms2;
	return ret;
}




CLIPSValue crifi_create_yearMonthDuration(Environment *env, YearMonthDuration val){
	CLIPSValue result;
	char outstring[30], tmpout[32+ sizeof(_XS_yearMonthDuration_)];
	int offset = 0;
	if (val.year == 0 && val.month == 0){
		offset += sprintf(outstring+offset, "P0M");
	} else {
		if (val.is_negative_duration) {
			offset += sprintf(outstring+offset, "-P");
		} else {
			offset += sprintf(outstring+offset, "P");
		}
		if (val.year > 0){
			offset += sprintf(outstring+offset, "%dY", val.year);
		}
		if (val.month > 0){
			offset += sprintf(outstring+offset, "%dM", val.month);
		}
	}
	value_and_datatype_to_slotstring(tmpout,
			outstring, strlen(outstring),
			_XS_yearMonthDuration_, sizeof(_XS_yearMonthDuration_));
	result.lexemeValue = CreateString(env, tmpout);
	return result;
}



DateTimeStamp add_yearMonthDuration_to_dateTime(DateTimeStamp time, YearMonthDuration dur){
	if (dur.is_negative_duration){
		time.year -= dur.year;
		time.month -= dur.month;
	} else {
		time.year += dur.year;
		time.month += dur.month;
	}
	normalize_dateTimeStamp(&time);
	return time;
}

/*
DateTimeStamp add_dayTimeDuration_to_dateTime(DateTimeStamp time, DateTimeStamp dur){
	if (dur.is_negative_duration){
		time.day -= dur.day;
		time.hour -= dur.hour;
		time.minute -= dur.minute;
		time.second -= dur.second;
		time.millisecond -= dur.millisecond;
	} else {
		time.day += dur.day;
		time.hour += dur.hour;
		time.minute += dur.minute;
		time.second += dur.second;
		time.millisecond += dur.millisecond;
	}

	normalize_dateTimeStamp(&time);
	return time;
}

DateTimeStamp subtract_dayTimeDuration_from_dateTime(DateTimeStamp time, DateTimeStamp dur){
	dur.is_negative_duration = !dur.is_negative_duration;
	return add_dayTimeDuration_to_dateTime(time, dur);
}
*/

DateTimeStamp subtract_yearMonthDuration_from_dateTime(DateTimeStamp time, YearMonthDuration dur){
	dur.is_negative_duration = !dur.is_negative_duration;
	return add_yearMonthDuration_to_dateTime(time, dur);
}



CLIPSValue crifi_create_dateTime(Environment *env, DateTimeStamp time){
	int offset;
	float tmp;
	char outstring[80], tmpout[82+ sizeof(_XS_dateTime_)];
	int tz_minute, tz_hour;
	CLIPSValue result;
	normalize_dateTimeStamp(&time);

	offset = sprintf(outstring, "%d-%02d-%02dT%02d:%02d",time.year, time.month, time.day, time.hour, time.minute);
	if (time.millisecond == 0){
		offset += sprintf(outstring+offset, ":%02d", time.second);
	} else {
		tmp = time.second + (0.001 * time.millisecond);
		offset += sprintf(outstring+offset, ":%02.3f", tmp);
		//remove trailing '0'
		for (int i=0; i<2; i++){
			if (outstring[offset-1]=='0'){
				outstring[offset-1] = '\0';
				offset--;
			}
		}
	}
	if (time.timezone_minute < 0){
		tz_minute = abs(time.timezone_minute % 60);
		tz_hour = abs(time.timezone_minute / 60);
		offset += sprintf(outstring+offset, "-%02d:%02d", tz_hour, tz_minute);
	} else if (time.timezone_minute > 0){
		tz_minute = abs(time.timezone_minute % 60);
		tz_hour = abs(time.timezone_minute / 60);
		offset += sprintf(outstring+offset, "+%02d:%02d", tz_hour, tz_minute);
	}
	value_and_datatype_to_slotstring(tmpout,
			outstring, strlen(outstring),
			_XS_dateTime_, sizeof(_XS_dateTime_));
	result.lexemeValue = CreateString(env, tmpout);
	return result;
}


CLIPSValue crifi_create_date(Environment *env, DateTimeStamp time){
	int offset;
	float tmp;
	char outstring[80], tmpout[82+ sizeof(_XS_date_)];
	int tz_minute, tz_hour;
	CLIPSValue result;
	normalize_dateTimeStamp(&time);

	offset = sprintf(outstring, "%d-%02d-%02d",time.year, time.month, time.day, time.hour, time.minute);
	if (time.no_timezone_data){
	} else if (time.timezone_minute == 0){
		offset += sprintf(outstring+offset, "Z");
	} else {
		tz_minute = time.timezone_minute % 60;
		tz_hour = time.timezone_minute / 60;
		offset += sprintf(outstring+offset, "-%d:%d", tz_hour, tz_minute);
	}
	value_and_datatype_to_slotstring(tmpout,
			outstring, strlen(outstring),
			_XS_date_, sizeof(_XS_date_));
	result.lexemeValue = CreateString(env, tmpout);
	return result;
}

CLIPSValue crifi_create_time(Environment *env, DateTimeStamp time){
	int offset;
	float tmp;
	char outstring[80], tmpout[82+ sizeof(_XS_time_)];
	int tz_minute, tz_hour;
	CLIPSValue result;
	normalize_dateTimeStamp(&time);

	offset = sprintf(outstring, "%02d:%02d", time.hour, time.minute);
	if (time.millisecond == 0){
		offset += sprintf(outstring+offset, ":%02d", time.second);
	} else {
		tmp = time.second + (0.001 * time.millisecond);
		offset += sprintf(outstring+offset, ":%02.3f", tmp);
		//remove trailing '0'
		for (int i=0; i<2; i++){
			if (outstring[offset-1]=='0'){
				outstring[offset-1] = '\0';
				offset--;
			}
		}
	}
	if (time.timezone_minute < 0){
		tz_minute = abs(time.timezone_minute % 60);
		tz_hour = abs(time.timezone_minute / 60);
		offset += sprintf(outstring+offset, "-%02d:%02d", tz_hour, tz_minute);
	} else if (time.timezone_minute > 0){
		tz_minute = abs(time.timezone_minute % 60);
		tz_hour = abs(time.timezone_minute / 60);
		offset += sprintf(outstring+offset, "+%02d:%02d", tz_hour, tz_minute);
	}
	value_and_datatype_to_slotstring(tmpout,
			outstring, strlen(outstring),
			_XS_time_, sizeof(_XS_time_));
	result.lexemeValue = CreateString(env, tmpout);
	return result;
}


bool equal_dateTime(DateTimeStamp left, DateTimeStamp right){
	left.minute -= left.timezone_minute;
	left.timezone_minute = 0;
	right.minute -= right.timezone_minute;
	right.timezone_minute = 0;
	normalize_dateTimeStamp(&left);
	normalize_dateTimeStamp(&right);
	return left.year == right.year
		&& left.month == right.month
		&& left.day == right.day
		&& left.hour == right.hour
		&& left.minute == right.minute
		&& left.second == right.second
		&& left.millisecond == right.millisecond;
}

bool less_than_dateTime(DateTimeStamp left, DateTimeStamp right){
	left.minute -= left.timezone_minute;
	left.timezone_minute = 0;
	right.minute -= right.timezone_minute;
	right.timezone_minute = 0;
	normalize_dateTimeStamp(&left);
	normalize_dateTimeStamp(&right);
	if (left.year < right.year){
		return true;
	} else if (left.year > right.year){
		return false;
	}
	if (left.month < right.month){
		return true;
	} else if (left.month > right.month){
		return false;
	}
	if (left.day < right.day){
		return true;
	} else if (left.day > right.day){
		return false;
	}
	if (left.hour < right.hour){
		return true;
	} else if (left.hour > right.hour){
		return false;
	}
	if (left.minute < right.minute){
		return true;
	} else if (left.minute > right.minute){
		return false;
	}
	if (left.second < right.second){
		return true;
	} else if (left.second > right.second){
		return false;
	}
	if (left.millisecond < right.millisecond){
		return true;
	}
	return false;
}

bool greater_than_dateTime(DateTimeStamp left, DateTimeStamp right){
	left.minute -= left.timezone_minute;
	left.timezone_minute = 0;
	right.minute -= right.timezone_minute;
	right.timezone_minute = 0;
	normalize_dateTimeStamp(&left);
	normalize_dateTimeStamp(&right);
	if (left.year > right.year){
		return true;
	} else if (left.year < right.year){
		return false;
	}
	if (left.month > right.month){
		return true;
	} else if (left.month < right.month){
		return false;
	}
	if (left.day > right.day){
		return true;
	} else if (left.day < right.day){
		return false;
	}
	if (left.hour > right.hour){
		return true;
	} else if (left.hour < right.hour){
		return false;
	}
	if (left.minute > right.minute){
		return true;
	} else if (left.minute < right.minute){
		return false;
	}
	if (left.second > right.second){
		return true;
	} else if (left.second < right.second){
		return false;
	}
	if (left.millisecond > right.millisecond){
		return true;
	}
	return false;
}

bool less_than_dayTimeDuration(DateTimeStamp inleft, DateTimeStamp inright){
	DateTimeStamp left, right;
	normalize_dayTimeDuration(&inleft);
	normalize_dayTimeDuration(&inright);
	if (inleft.is_negative_duration){
		if (inright.is_negative_duration){
			left = inright;
			right = inleft;
		} else {
			return true;
		}
	} else {
		if (inright.is_negative_duration){
			return false;
		} else {
			left = inleft;
			right = inright;
		}
	}
	if (left.day < right.day){
		return true;
	} else if (left.day > right.day){
		return false;
	}
	if (left.hour < right.hour){
		return true;
	} else if (left.hour > right.hour){
		return false;
	}
	if (left.minute < right.minute){
		return true;
	} else if (left.minute > right.minute){
		return false;
	}
	if (left.second < right.second){
		return true;
	} else if (left.second > right.second){
		return false;
	}
	if (left.millisecond < right.millisecond){
		return true;
	}
	return false;
}

bool equal_dayTimeDuration(DateTimeStamp left, DateTimeStamp right){
	if (left.is_negative_duration != right.is_negative_duration){
		return false;
	}
	if (left.day != right.day){
		return false;
	}
	if (left.hour != right.hour){
		return false;
	}
	if (left.minute != right.minute){
		return false;
	}
	if (left.second != right.second){
		return false;
	}
	if (left.millisecond != right.millisecond){
		return false;
	}
	return true;
}

bool greater_than_dayTimeDuration(DateTimeStamp inleft, DateTimeStamp inright){
	DateTimeStamp left, right;
	if (inleft.is_negative_duration){
		if (inright.is_negative_duration){
			left = inright;
			right = inleft;
		} else {
			return false;
		}
	} else {
		if (inright.is_negative_duration){
			return true;
		} else {
			left = inleft;
			right = inright;
		}
	}
	if (left.day > right.day){
		return true;
	} else if (left.day < right.day){
		return false;
	}
	if (left.hour > right.hour){
		return true;
	} else if (left.hour < right.hour){
		return false;
	}
	if (left.minute > right.minute){
		return true;
	} else if (left.minute < right.minute){
		return false;
	}
	if (left.second > right.second){
		return true;
	} else if (left.second < right.second){
		return false;
	}
	if (left.millisecond > right.millisecond){
		return true;
	}
	return false;
}

bool greater_than_yearMonthDuration(YearMonthDuration inleft, YearMonthDuration inright){
	YearMonthDuration left, right;
	if (inleft.is_negative_duration){
		if (inright.is_negative_duration){
			left = inright;
			right = inleft;
		} else {
			return false;
		}
	} else {
		if (inright.is_negative_duration){
			return true;
		} else {
			left = inleft;
			right = inright;
		}
	}
	if (left.year > right.year){
		return true;
	} else if (left.year < right.year){
		return false;
	}
	if (left.month > right.month){
		return true;
	}
	return false;
}

bool less_than_yearMonthDuration(YearMonthDuration inleft, YearMonthDuration inright){
	YearMonthDuration left, right;
	if (inleft.is_negative_duration){
		if (inright.is_negative_duration){
			left = inright;
			right = inleft;
		} else {
			return true;
		}
	} else {
		if (inright.is_negative_duration){
			return false;
		} else {
			left = inleft;
			right = inright;
		}
	}
	if (left.year < right.year){
		return true;
	} else if (left.year > right.year){
		return false;
	}
	if (left.month < right.month){
		return true;
	}
	return false;
}

bool equal_yearMonthDuration(YearMonthDuration left, YearMonthDuration right){
	if (left.is_negative_duration != right.is_negative_duration){
		return false;
	}
	if (left.year != right.year){
		return false;
	}
	if (left.month != right.month){
		return false;
	}
	return true;
}
