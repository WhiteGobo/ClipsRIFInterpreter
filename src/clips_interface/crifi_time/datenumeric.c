#include "crifi_time.h"
#include "timeduration_object.h"
#include "timedata_object.h"
#include "macros_date_to_days.h"

#include <math.h>

void crifi_time_cast_as_dayTimeDuration(CrifiDuration *result){
	//result->type = DAYTIMEDURATION
	result->year = 0;
	result->month = 0;
}

void crifi_time_cast_as_yearMonthDuration(CrifiDuration *result){
	//result->type = YEARMONTHDURATION
	result->day = 0;
	result->hour = 0;
	result->minute = 0;
	result->second = 0;
	result->millisecond = 0;
}


bool crifi_time_cast_as_time(DateTimeStamp *time){
	switch (time->type){
		case CRIFI_TIME_DATETIMESTAMP_TIME:
			return true;
		case CRIFI_TIME_DATETIMESTAMP_DATETIME:
			time->type = CRIFI_TIME_DATETIMESTAMP_TIME;
			time->year = 0;
			time->month = 0;
			time->day = 0;
			return true;
		case CRIFI_TIME_DATETIMESTAMP_DATE:
		case CRIFI_TIME_DATETIMESTAMP_GYEARMONTH:
		case CRIFI_TIME_DATETIMESTAMP_GYEAR:
		case CRIFI_TIME_DATETIMESTAMP_GMONTHDAY:
		case CRIFI_TIME_DATETIMESTAMP_GMONTH:
		case CRIFI_TIME_DATETIMESTAMP_GDAY:
		case CRIFI_TIME_DATETIMESTAMP_UNKNOWN_TYPE:
		default:
			time->type = CRIFI_TIME_DATETIMESTAMP_UNKNOWN_TYPE;
			return false;
	}
}

bool crifi_time_cast_as_dateTime(DateTimeStamp *time){
	switch (time->type){
		case CRIFI_TIME_DATETIMESTAMP_DATETIME:
		case CRIFI_TIME_DATETIMESTAMP_DATE:
			time->type = CRIFI_TIME_DATETIMESTAMP_DATETIME;
			return true;
		case CRIFI_TIME_DATETIMESTAMP_TIME:
		case CRIFI_TIME_DATETIMESTAMP_GYEARMONTH:
		case CRIFI_TIME_DATETIMESTAMP_GYEAR:
		case CRIFI_TIME_DATETIMESTAMP_GMONTHDAY:
		case CRIFI_TIME_DATETIMESTAMP_GMONTH:
		case CRIFI_TIME_DATETIMESTAMP_GDAY:
		case CRIFI_TIME_DATETIMESTAMP_UNKNOWN_TYPE:
		default:
			time->type = CRIFI_TIME_DATETIMESTAMP_UNKNOWN_TYPE;
			return false;
	}
}

bool crifi_time_cast_as_date(DateTimeStamp *time){
	switch (time->type){
		case CRIFI_TIME_DATETIMESTAMP_DATETIME:
			time->type = CRIFI_TIME_DATETIMESTAMP_DATE;
			return true;
		case CRIFI_TIME_DATETIMESTAMP_DATE:
			time->hour = 0;
			time->minute = 0;
			time->second = 0;
			time->millisecond = 0;
			return true;
		case CRIFI_TIME_DATETIMESTAMP_TIME:
		case CRIFI_TIME_DATETIMESTAMP_GYEARMONTH:
		case CRIFI_TIME_DATETIMESTAMP_GYEAR:
		case CRIFI_TIME_DATETIMESTAMP_GMONTHDAY:
		case CRIFI_TIME_DATETIMESTAMP_GMONTH:
		case CRIFI_TIME_DATETIMESTAMP_GDAY:
		case CRIFI_TIME_DATETIMESTAMP_UNKNOWN_TYPE:
		default:
			time->type = CRIFI_TIME_DATETIMESTAMP_UNKNOWN_TYPE;
			return false;
	}
}




/**
 * works only correct in month 12
 */
static void transform_year_to_days(DateTimeStamp *result, int target_year){
	while (result->year > target_year) {
		if (LEAPYEAR(result)) {
			result->day += 366;
		} else {
			result->day += 365;
		}
		result->year--;
	}
}

static void transform_day_to_month(DateTimeStamp *result, int target_month){
	while (result->month < target_month){
		if (MONTH28(result)){
			result->month += 1;
			result->day -= 28;
		} else if (MONTH29(result)){
			result->month += 1;
			result->day -= 29;
		} else if (MONTH30(result)){
			result->month += 1;
			result->day -= 30;
		} else {
			result->month += 1;
			result->day -= 31;
		}
	}
}

CrifiDuration subtract_dateTime(DateTimeStamp val1, DateTimeStamp val2){
	CrifiDuration result;
	int dday, dhour, dminute, dseconds, dmilliseconds;
	transform_day_to_month(&val1, 12);
	transform_day_to_month(&val2, 12);
	if (val1.year > val2.year) {
		transform_year_to_days(&val1, val2.year);
	} else {
		transform_year_to_days(&val2, val1.year);
	}
	dday = val1.day - val2.day;
	dhour = val1.hour - val2.hour;
	dminute = val1.minute - val2.minute - val1.timezone_minute + val2.timezone_minute;
	dseconds = val1.second - val2.second;
	dmilliseconds = val1.millisecond - val2.millisecond;
	result = crifi_new_dayTimeDuration(false, dday, dhour, dminute, dseconds, dmilliseconds);
	normalize_duration(&result);
	return result;
}



CrifiDuration subtract_durations(CrifiDuration dur1, CrifiDuration dur2){
	dur2.is_negative_duration = !dur2.is_negative_duration;
	return add_durations(dur1, dur2);
}


CrifiDuration add_durations(CrifiDuration dur1, CrifiDuration dur2){
	if (dur1.is_negative_duration != dur2.is_negative_duration){
		dur1.year -= dur2.month;
		dur1.month -= dur2.month;
		dur1.day -= dur2.day;
		dur1.hour -= dur2.hour;
		dur1.minute -= dur2.minute;
		dur1.second -= dur2.second;
		dur1.millisecond -= dur2.millisecond;
	} else {
		dur1.year += dur2.month;
		dur1.month += dur2.month;
		dur1.day += dur2.day;
		dur1.hour += dur2.hour;
		dur1.minute += dur2.minute;
		dur1.second += dur2.second;
		dur1.millisecond += dur2.millisecond;
	}
	normalize_duration(&dur1);
	return dur1;
}

CrifiDuration divide_duration(CrifiDuration dur, double mult){
	return multiply_duration(dur, 1/mult);
}

enum {
	PREC_MULTIPLY_DURATION_MONTH,
	PREC_MULTIPLY_DURATION_HOUR,
	PREC_MULTIPLY_DURATION_MINUTE,
	PREC_MULTIPLY_DURATION_SECOND,
	PREC_MULTIPLY_DURATION_MILLISECOND
};

CrifiDuration multiply_duration(CrifiDuration dur, double mult){
	int prec;
	float months;
	long lmonths;
	double tmp;
	CrifiDuration out = {.year=0, .month=0, .day=0, .hour=0, .minute=0, .second=0, .millisecond=0};
	if (mult < 0){
		out.is_negative_duration = !dur.is_negative_duration;
	} else {
		out.is_negative_duration = dur.is_negative_duration;
	}
	mult = fabsf(mult);
	if (dur.millisecond != 0){
		prec = PREC_MULTIPLY_DURATION_MILLISECOND;
	} else if (dur.second != 0){
		prec = PREC_MULTIPLY_DURATION_MILLISECOND;
	} else if (dur.minute != 0){
		prec = PREC_MULTIPLY_DURATION_SECOND;
	} else if (dur.hour != 0){
		prec = PREC_MULTIPLY_DURATION_MINUTE;
	} else if (dur.day != 0){
		prec = PREC_MULTIPLY_DURATION_HOUR;
	} else {
		prec = PREC_MULTIPLY_DURATION_MONTH;
	}

	months = (12*dur.year) + dur.month;
	months *= mult;
	lmonths = lround(months);
	out.year = lmonths / 12;
	out.month = lmonths % 12;
	if (prec == PREC_MULTIPLY_DURATION_MONTH){
		normalize_duration(&out);
		return out;
	}

	tmp = mult * dur.day;
	out.day = tmp;
	tmp = 24*(tmp - out.day) + (mult * dur.hour);
	if (prec == PREC_MULTIPLY_DURATION_HOUR){
		out.hour = lround(tmp);
		normalize_duration(&out);
		return out;
	}
	out.hour = tmp;
	tmp = 60*(tmp - out.hour) + (mult * dur.minute);
	if (prec == PREC_MULTIPLY_DURATION_MINUTE){
		out.minute = lround(tmp);
		normalize_duration(&out);
		return out;
	}
	out.minute = tmp;
	tmp = 60*(tmp - out.minute) + (mult * dur.second);
	if (prec == PREC_MULTIPLY_DURATION_SECOND){
		out.second = lround(tmp);
		normalize_duration(&out);
		return out;
	}
	out.second = tmp;
	tmp = 1000*(tmp - out.second) + (mult * dur.millisecond);
	out.millisecond = lround(tmp);
	normalize_duration(&out);
	return out;
}


DateTimeStamp subtract_duration_from_time(DateTimeStamp time, CrifiDuration dur){
	dur.is_negative_duration = true;
	return add_duration_to_time(time, dur);
}

DateTimeStamp add_duration_to_time(DateTimeStamp time, CrifiDuration dur){
	if (dur.is_negative_duration){
		time.year -= dur.year;
		time.month -= dur.month;
		time.day -= dur.day;
		time.hour -= dur.hour;
		time.minute -= dur.minute;
		time.second -= dur.second;
		time.millisecond -= dur.millisecond;
	} else {
		time.year += dur.year;
		time.month += dur.month;
		time.day += dur.day;
		time.hour += dur.hour;
		time.minute += dur.minute;
		time.second += dur.second;
		time.millisecond += dur.millisecond;
	}

	normalize_dateTimeStamp(&time);
	return time;
}
