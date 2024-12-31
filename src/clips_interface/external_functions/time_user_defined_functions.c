#include "time_user_defined_functions.h"
#include <crifi_time.h>
#include <crifi_numeric.h>
#include <math.h>
#include <n3parser.h>

#define RETURNFAIL(failure) \
		Writeln(env, failure);\
		SetErrorValue(env, &(CreateString(env, failure)->header));\
		out->voidValue = VoidConstant(env);\
		return;

void rif_is_literal_date(Environment *env, UDFContext *udfc, UDFValue *out){
	bool truth;
	bool invert = *(bool*) udfc->context;
	UDFValue udfval;
	CLIPSValue clipsval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	truth = check_is_date(env, clipsval, NULL);
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}


void rif_is_literal_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	bool truth;
	bool invert = *(bool*) udfc->context;
	UDFValue udfval;
	CLIPSValue clipsval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	DateTimeStamp tmp;
	truth = check_is_dateTime(env, clipsval, NULL);
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}


void rif_is_literal_dateTimeStamp(Environment *env, UDFContext *udfc, UDFValue *out){
	bool truth;
	bool invert = *(bool*) udfc->context;
	UDFValue udfval;
	CLIPSValue clipsval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	truth = check_is_dateTimeStamp(env, clipsval, NULL);
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}


void rif_is_literal_time(Environment *env, UDFContext *udfc, UDFValue *out){
	bool truth;
	bool invert = *(bool*) udfc->context;
	UDFValue udfval;
	CLIPSValue clipsval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	truth = check_is_time(env, clipsval, NULL);
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}


void rif_is_literal_dayTimeDuration(Environment *env, UDFContext *udfc, UDFValue *out){
	bool truth;
	bool invert = *(bool*) udfc->context;
	UDFValue udfval;
	CLIPSValue clipsval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	truth = check_is_dayTimeDuration(env, clipsval, NULL);
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}


void rif_is_literal_yearMonthDuration(Environment *env, UDFContext *udfc, UDFValue *out){
	bool truth;
	bool invert = *(bool*) udfc->context;
	UDFValue udfval;
	CLIPSValue clipsval;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	truth = check_is_yearMonthDuration(env, clipsval, NULL);
	if (invert) truth = !truth;
	out->lexemeValue = CreateBoolean(env, truth);
}


void rif_year_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	DateTimeStamp tmp;
	if(!check_is_dateTime(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. year-from-dateTime "
				"expects xs:dateTime");
	}
	clipsout = crifi_create_integer(env, tmp.year);
	out->value = clipsout.value;
}


void rif_month_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	DateTimeStamp tmp;
	if(!check_is_dateTime(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. year-from-dateTime "
				"expects xs:dateTime");
	}
	clipsout = crifi_create_integer(env, tmp.month);
	out->value = clipsout.value;
}


void rif_day_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	DateTimeStamp tmp;
	if(!check_is_dateTime(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. year-from-dateTime "
				"expects xs:dateTime");
	}
	clipsout = crifi_create_integer(env, tmp.day);
	out->value = clipsout.value;
}


void rif_hours_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	DateTimeStamp tmp;
	if(!check_is_dateTime(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. year-from-dateTime "
				"expects xs:dateTime");
	}
	clipsout = crifi_create_integer(env, tmp.hour);
	out->value = clipsout.value;
}


void rif_minutes_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	DateTimeStamp tmp;
	if(!check_is_dateTime(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. year-from-dateTime "
				"expects xs:dateTime");
	}
	clipsout = crifi_create_integer(env, tmp.minute);
	out->value = clipsout.value;
}


void rif_seconds_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	DateTimeStamp tmp;
	if(!check_is_dateTime(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. year-from-dateTime "
				"expects xs:dateTime");
	}
	clipsout = crifi_create_integer(env, tmp.second);
	out->value = clipsout.value;
}

void rif_year_from_date(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	DateTimeStamp tmp;
	if(!check_is_date(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. year-from-date expects xs:date");
	}
	clipsout = crifi_create_integer(env, tmp.year);
	out->value = clipsout.value;
}


void rif_month_from_date(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	DateTimeStamp tmp;
	if(!check_is_date(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. year-from-date expects xs:date");
	}
	clipsout = crifi_create_integer(env, tmp.month);
	out->value = clipsout.value;
}


void rif_day_from_date(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	DateTimeStamp tmp;
	if(!check_is_date(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. year-from-date expects xs:date");
	}
	clipsout = crifi_create_integer(env, tmp.day);
	out->value = clipsout.value;
}


void rif_hours_from_time(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	DateTimeStamp tmp;
	if(!check_is_time(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. year-from-date expects xs:date");
	}
	clipsout = crifi_create_integer(env, tmp.hour);
	out->value = clipsout.value;
}


void rif_minutes_from_time(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	DateTimeStamp tmp;
	if(!check_is_time(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. year-from-date expects xs:date");
	}
	clipsout = crifi_create_integer(env, tmp.minute);
	out->value = clipsout.value;
}


void rif_seconds_from_time(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	DateTimeStamp tmp;
	if(!check_is_time(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. year-from-date expects xs:date");
	}
	clipsout = crifi_create_integer(env, tmp.second);
	out->value = clipsout.value;
}


void rif_timezone_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	DateTimeStamp tmp;
	if(!check_is_dateTime(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. year-from-dateTime "
				"expects xs:dateTime");
	}
	clipsout = crifi_create_dayTimeDuration(env, false, 0, 0,
			tmp.timezone_minute, 0, 0);
	out->value = clipsout.value;
}


void rif_timezone_from_date(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	DateTimeStamp tmp;
	if(!check_is_date(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. timezone-from-date "
				"expects xs:date");
	}
	clipsout = crifi_create_dayTimeDuration(env, false, 0, 0,
			tmp.timezone_minute, 0, 0);
	out->value = clipsout.value;
}


void rif_timezone_from_time(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	DateTimeStamp tmp;
	if(!check_is_time(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. timezone-from-time "
				"expects xs:date");
	}
	clipsout = crifi_create_dayTimeDuration(env, false, 0, 0,
			tmp.timezone_minute, 0, 0);
	out->value = clipsout.value;
}


void rif_years_from_duration(Environment *env, UDFContext *udfc, UDFValue *out){
	YearMonthDuration tmp;
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	if(!check_is_yearMonthDuration(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. years-from-duration "
				"expects xs:yearMonthDuration");
	}
	if (tmp.is_negative_duration){
		clipsout = crifi_create_integer(env, -tmp.year);
	} else {
		clipsout = crifi_create_integer(env, tmp.year);
	}
	out->value = clipsout.value;
}


void rif_months_from_duration(Environment *env, UDFContext *udfc, UDFValue *out){
	YearMonthDuration tmp;
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	if(!check_is_yearMonthDuration(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. month-from-duration "
				"expects xs:yearMonthDuration.");
	}
	if (tmp.is_negative_duration){
		clipsout = crifi_create_integer(env, -tmp.month);
	} else {
		clipsout = crifi_create_integer(env, tmp.month);
	}
	out->value = clipsout.value;
}


void rif_days_from_duration(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTimeStamp tmp;
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	if(!check_is_dayTimeDuration(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. days-from-duration "
				"expects xs:dayTimeDuration.");
	}
	if (tmp.is_negative_duration){
		clipsout = crifi_create_integer(env, -tmp.day);
	}else {
		clipsout = crifi_create_integer(env, tmp.day);
	}
	out->value = clipsout.value;
}


void rif_hours_from_duration(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTimeStamp tmp;
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	if(!check_is_dayTimeDuration(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. hours-from-duration "
				"expects xs:dayTimeDuration.");
	}
	if (tmp.is_negative_duration){
		clipsout = crifi_create_integer(env, -tmp.hour);
	} else {
		clipsout = crifi_create_integer(env, tmp.hour);
	}
	out->value = clipsout.value;
}


void rif_minutes_from_duration(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTimeStamp tmp;
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	if(!check_is_dayTimeDuration(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. minutes-from-duration "
				"expects xs:dayTimeDuration.");
	}
	if (tmp.is_negative_duration){
		clipsout = crifi_create_integer(env, -tmp.minute);
	} else {
		clipsout = crifi_create_integer(env, tmp.minute);
	}
	out->value = clipsout.value;
}


void rif_seconds_from_duration(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTimeStamp tmp;
	long long ms;
	UDFValue udfval;
	CLIPSValue clipsval, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval.value = udfval.value;
	if(!check_is_dayTimeDuration(env, clipsval, &tmp)){
		RETURNFAIL("Missing Guard. seconds-from-duration "
				"expects xs:dayTimeDuration.");
	}
	if(tmp.millisecond != 0){
		ms = (1000*tmp.second) + tmp.millisecond;
		if (tmp.is_negative_duration){
			clipsout = crifi_create_rational(env, -ms, 1000);
		} else {
			clipsout = crifi_create_rational(env, ms, 1000);
		}
	} else {
		if (tmp.is_negative_duration){
			clipsout = crifi_create_integer(env, -tmp.second);
		} else {
			clipsout = crifi_create_integer(env, tmp.second);
		}
	}
	out->value = clipsout.value;
}


void rif_subtract_dateTimes(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTimeStamp tmp1, tmp2, outtmp;
	UDFValue udfval1, udfval2;
	CLIPSValue clipsval1, clipsval2, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval1)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfval2)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval1.value = udfval1.value;
	clipsval2.value = udfval2.value;
	if(!check_is_dateTime(env, clipsval1, &tmp1)){
		RETURNFAIL("Missing Guard. subtract-dateTimes");
	}
	if(!check_is_dateTime(env, clipsval2, &tmp2)){
		RETURNFAIL("Missing Guard. subtract-dateTimes");
	}
	outtmp = subtract_dateTime(tmp1, tmp2);
	clipsout = crifi_create_dayTimeDuration(env,
			outtmp.is_negative_duration,
			outtmp.day, outtmp.hour, outtmp.minute,
			outtmp.second, outtmp.millisecond);
	out->value = clipsout.value;
}


void rif_subtract_dates(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTimeStamp tmp1, tmp2, outtmp;
	UDFValue udfval1, udfval2;
	CLIPSValue clipsval1, clipsval2, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval1)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfval2)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval1.value = udfval1.value;
	clipsval2.value = udfval2.value;
	if(!check_is_date(env, clipsval1, &tmp1)){
		RETURNFAIL("Missing Guard. subtract-dateTimes");
	}
	if(!check_is_date(env, clipsval2, &tmp2)){
		RETURNFAIL("Missing Guard. subtract-dateTimes");
	}
	tmp1.timezone_minute = 0;
	tmp2.timezone_minute = 0;
	outtmp = subtract_dateTime(tmp1, tmp2);
	clipsout = crifi_create_dayTimeDuration(env,
			outtmp.is_negative_duration,
			outtmp.day, 0, 0, 0, 0);
	out->value = clipsout.value;
}


void rif_subtract_times(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTimeStamp tmp1, tmp2, outtmp;
	UDFValue udfval1, udfval2;
	CLIPSValue clipsval1, clipsval2, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval1)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfval2)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval1.value = udfval1.value;
	clipsval2.value = udfval2.value;
	if(!check_is_time(env, clipsval1, &tmp1)){
		RETURNFAIL("Missing Guard. subtract-dateTimes");
	}
	if(!check_is_time(env, clipsval2, &tmp2)){
		RETURNFAIL("Missing Guard. subtract-dateTimes");
	}
	outtmp = subtract_dateTime(tmp1, tmp2);
	clipsout = crifi_create_dayTimeDuration(env,
			outtmp.is_negative_duration,
			outtmp.day, outtmp.hour, outtmp.minute,
			outtmp.second, outtmp.millisecond);
	out->value = clipsout.value;
}


void rif_add_yearMonthDurations(Environment *env, UDFContext *udfc, UDFValue *out){
	YearMonthDuration tmp1, tmp2, outtmp;
	UDFValue udfval1, udfval2;
	CLIPSValue clipsval1, clipsval2, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval1)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfval2)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval1.value = udfval1.value;
	clipsval2.value = udfval2.value;
	if(!check_is_yearMonthDuration(env, clipsval1, &tmp1)){
		RETURNFAIL("Missing Guard. subtract-dateTimes");
	}
	if(!check_is_yearMonthDuration(env, clipsval2, &tmp2)){
		RETURNFAIL("Missing Guard. subtract-dateTimes");
	}
	outtmp = add_yearMonthDuration(tmp1, tmp2);
	clipsout = crifi_create_yearMonthDuration(env, outtmp);
	out->value = clipsout.value;
}


void rif_subtract_yearMonthDurations(Environment *env, UDFContext *udfc, UDFValue *out){
	YearMonthDuration tmp1, tmp2, outtmp;
	UDFValue udfval1, udfval2;
	CLIPSValue clipsval1, clipsval2, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval1)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfval2)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval1.value = udfval1.value;
	clipsval2.value = udfval2.value;
	if(!check_is_yearMonthDuration(env, clipsval1, &tmp1)){
		RETURNFAIL("Missing Guard. subtract-dateTimes");
	}
	if(!check_is_yearMonthDuration(env, clipsval2, &tmp2)){
		RETURNFAIL("Missing Guard. subtract-dateTimes");
	}
	outtmp = subtract_yearMonthDuration(tmp1, tmp2);
	clipsout = crifi_create_yearMonthDuration(env, outtmp);
	out->value = clipsout.value;
}


void rif_multiply_yearMonthDuration(Environment *env, UDFContext *udfc, UDFValue *out){
	YearMonthDuration indur, outdur;
	UDFValue udfdur, udfmult;
	float months;
	long lmonths;
	CLIPSValue clipsdur, clipsmult, clipsout;
	NumericValue mult;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfdur)){
		RETURNFAIL("Argument error for multiply-yearMonthDuration.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfmult)){
		RETURNFAIL("Argument error for multiply-yearMonthDuration.");
	}
	clipsdur.value = udfdur.value;
	clipsmult.value = udfmult.value;
	if(!check_is_yearMonthDuration(env, clipsdur, &indur)){
		RETURNFAIL("Missing Guard. muliply-yearMonthDuration");
	}
	if(!clipsvalue_as_numeric_value(env, clipsmult, &mult) && mult.t != NT_NAN){
		RETURNFAIL("Missing Guard. muliply-yearMonthDuration");
	}
	outdur = multiply_yearMonthDuration(indur, nv_as_float(mult));
	clipsout = crifi_create_yearMonthDuration(env, outdur);
	out->value = clipsout.value;
}


void rif_divide_yearMonthDuration(Environment *env, UDFContext *udfc, UDFValue *out){
	YearMonthDuration indur, outdur;
	UDFValue udfdur, udfmult;
	float months;
	long lmonths;
	CLIPSValue clipsdur, clipsmult, clipsout;
	NumericValue mult;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfdur)){
		RETURNFAIL("Argument error for multiply-yearMonthDuration.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfmult)){
		RETURNFAIL("Argument error for multiply-yearMonthDuration.");
	}
	clipsdur.value = udfdur.value;
	clipsmult.value = udfmult.value;
	if(!check_is_yearMonthDuration(env, clipsdur, &indur)){
		RETURNFAIL("Missing Guard. divide-yearMonthDuration");
	}
	if(!clipsvalue_as_numeric_value(env, clipsmult, &mult) && mult.t != NT_NAN){
		RETURNFAIL("Missing Guard. divide-yearMonthDuration");
	}
	outdur = divide_yearMonthDuration(indur, nv_as_float(mult));
	clipsout = crifi_create_yearMonthDuration(env, outdur);
	out->value = clipsout.value;
}


void rif_divide_yearMonthDuration_by_yearMonthDuration(Environment *env, UDFContext *udfc, UDFValue *out){
	YearMonthDuration tmp1, tmp2, outtmp;
	NumericValue outval;
	UDFValue udfval1, udfval2;
	CLIPSValue clipsval1, clipsval2, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval1)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfval2)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval1.value = udfval1.value;
	clipsval2.value = udfval2.value;
	if(!check_is_yearMonthDuration(env, clipsval1, &tmp1)){
		RETURNFAIL("Missing Guard. subtract-dateTimes");
	}
	if(!check_is_yearMonthDuration(env, clipsval2, &tmp2)){
		RETURNFAIL("Missing Guard. subtract-dateTimes");
	}
	outval = divide_yearMonthDuration_by_yearMonthDuration(tmp1, tmp2);
	clipsout = crifi_numeric_to_clipsvalue(env, outval);
	out->value = clipsout.value;
}


void rif_add_dayTimeDurations(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTimeStamp tmp1, tmp2, outtmp;
	NumericValue outval;
	UDFValue udfval1, udfval2;
	CLIPSValue clipsval1, clipsval2, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval1)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfval2)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval1.value = udfval1.value;
	clipsval2.value = udfval2.value;
	if(!check_is_dayTimeDuration(env, clipsval1, &tmp1)){
		RETURNFAIL("Missing Guard. subtract-dateTimes");
	}
	if(!check_is_dayTimeDuration(env, clipsval2, &tmp2)){
		RETURNFAIL("Missing Guard. subtract-dateTimes");
	}
	outtmp = add_dayTimeDurations(tmp1, tmp2);
	clipsout = crifi_create_dayTimeDuration(env,
			outtmp.is_negative_duration,
			outtmp.day, outtmp.hour, outtmp.minute,
			outtmp.second, outtmp.millisecond);
	out->value = clipsout.value;
}


void rif_subtract_dayTimeDurations(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTimeStamp tmp1, tmp2, outtmp;
	NumericValue outval;
	UDFValue udfval1, udfval2;
	CLIPSValue clipsval1, clipsval2, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval1)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfval2)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval1.value = udfval1.value;
	clipsval2.value = udfval2.value;
	if(!check_is_dayTimeDuration(env, clipsval1, &tmp1)){
		RETURNFAIL("Missing Guard. subtract-dateTimes");
	}
	if(!check_is_dayTimeDuration(env, clipsval2, &tmp2)){
		RETURNFAIL("Missing Guard. subtract-dateTimes");
	}
	outtmp = subtract_dayTimeDurations(tmp1, tmp2);
	clipsout = crifi_create_dayTimeDuration(env,
			outtmp.is_negative_duration,
			outtmp.day, outtmp.hour, outtmp.minute,
			outtmp.second, outtmp.millisecond);
	out->value = clipsout.value;
}


void rif_multiply_dayTimeDuration(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTimeStamp indur, outdur;
	UDFValue udfdur, udfmult;
	float months;
	long lmonths;
	CLIPSValue clipsdur, clipsmult, clipsout;
	NumericValue mult;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfdur)){
		RETURNFAIL("Argument error for multiply-yearMonthDuration.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfmult)){
		RETURNFAIL("Argument error for multiply-yearMonthDuration.");
	}
	clipsdur.value = udfdur.value;
	clipsmult.value = udfmult.value;
	if(!check_is_dayTimeDuration(env, clipsdur, &indur)){
		RETURNFAIL("Missing Guard. muliply-yearMonthDuration");
	}
	if(!clipsvalue_as_numeric_value(env, clipsmult, &mult) && mult.t != NT_NAN){
		RETURNFAIL("Missing Guard. muliply-yearMonthDuration");
	}
	outdur = multiply_dayTimeDuration(indur, nv_as_float(mult));
	clipsout = crifi_create_dayTimeDuration(env,
			outdur.is_negative_duration,
			outdur.day, outdur.hour, outdur.minute,
			outdur.second, outdur.millisecond);
	out->value = clipsout.value;
}


void rif_divide_dayTimeDuration(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTimeStamp indur, outdur;
	UDFValue udfdur, udfmult;
	float months;
	long lmonths;
	CLIPSValue clipsdur, clipsmult, clipsout;
	NumericValue mult;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfdur)){
		RETURNFAIL("Argument error for multiply-yearMonthDuration.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfmult)){
		RETURNFAIL("Argument error for multiply-yearMonthDuration.");
	}
	clipsdur.value = udfdur.value;
	clipsmult.value = udfmult.value;
	if(!check_is_dayTimeDuration(env, clipsdur, &indur)){
		RETURNFAIL("Missing Guard. muliply-yearMonthDuration");
	}
	if(!clipsvalue_as_numeric_value(env, clipsmult, &mult) && mult.t != NT_NAN){
		RETURNFAIL("Missing Guard. muliply-yearMonthDuration");
	}
	outdur = divide_dayTimeDuration(indur, nv_as_float(mult));
	clipsout = crifi_create_dayTimeDuration(env,
			outdur.is_negative_duration,
			outdur.day, outdur.hour, outdur.minute,
			outdur.second, outdur.millisecond);
	out->value = clipsout.value;
}


void rif_divide_dayTimeDuration_by_dayTimeDuration(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTimeStamp tmp1, tmp2, outtmp;
	NumericValue outval;
	UDFValue udfval1, udfval2;
	CLIPSValue clipsval1, clipsval2, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfval1)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfval2)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipsval1.value = udfval1.value;
	clipsval2.value = udfval2.value;
	if(!check_is_dayTimeDuration(env, clipsval1, &tmp1)){
		RETURNFAIL("Missing Guard. "
				"divide-dayTimeDuration-by-dayTimeDuration");
	}
	if(!check_is_dayTimeDuration(env, clipsval2, &tmp2)){
		RETURNFAIL("Missing Guard. "
				"divide-dayTimeDuration-by-dayTimeDuration");
	}
	outval = divide_dayTimeDuration_by_dayTimeDuration(tmp1, tmp2);
	clipsout = crifi_numeric_to_clipsvalue(env, outval);
	out->value = clipsout.value;
}


void rif_add_yearMonthDuration_to_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	YearMonthDuration dur;
	DateTimeStamp time, outval;
	UDFValue udftime, udfdur;
	CLIPSValue clipstime, clipsdur, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udftime)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfdur)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipstime.value = udftime.value;
	clipsdur.value = udfdur.value;
	if(!check_is_dateTime(env, clipstime, &time)){
		RETURNFAIL("Missing Guard. "
				"divide-dayTimeDuration-by-dayTimeDuration");
	}
	if(!check_is_yearMonthDuration(env, clipsdur, &dur)){
		RETURNFAIL("Missing Guard. "
				"divide-dayTimeDuration-by-dayTimeDuration");
	}
	outval = add_yearMonthDuration_to_dateTime(time, dur);
	clipsout = crifi_create_dateTime(env, outval);
	out->value = clipsout.value;
}


void rif_add_yearMonthDuration_to_date(Environment *env, UDFContext *udfc, UDFValue *out){
	YearMonthDuration dur;
	DateTimeStamp time, outval;
	UDFValue udftime, udfdur;
	CLIPSValue clipstime, clipsdur, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udftime)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfdur)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipstime.value = udftime.value;
	clipsdur.value = udfdur.value;
	if(!check_is_date(env, clipstime, &time)){
		RETURNFAIL("Missing Guard. "
				"divide-dayTimeDuration-by-dayTimeDuration");
	}
	if(!check_is_yearMonthDuration(env, clipsdur, &dur)){
		RETURNFAIL("Missing Guard. "
				"divide-dayTimeDuration-by-dayTimeDuration");
	}
	outval = add_yearMonthDuration_to_dateTime(time, dur);
	clipsout = crifi_create_date(env, outval);
	out->value = clipsout.value;
}


void rif_add_dayTimeDuration_to_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTimeStamp time, dur, outval;
	UDFValue udftime, udfdur;
	CLIPSValue clipstime, clipsdur, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udftime)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfdur)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipstime.value = udftime.value;
	clipsdur.value = udfdur.value;
	if(!check_is_dateTime(env, clipstime, &time)){
		RETURNFAIL("Missing Guard. "
				"add-dayTimeDuration-to-dateTime");
	}
	if(!check_is_dayTimeDuration(env, clipsdur, &dur)){
		RETURNFAIL("Missing Guard. "
				"add-dayTimeDuration-to-dateTime");
	}
	outval = add_dayTimeDuration_to_dateTime(time, dur);
	clipsout = crifi_create_dateTime(env, outval);
	out->value = clipsout.value;
}


void rif_add_dayTimeDuration_to_date(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTimeStamp time, dur, outval;
	UDFValue udftime, udfdur;
	CLIPSValue clipstime, clipsdur, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udftime)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfdur)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipstime.value = udftime.value;
	clipsdur.value = udfdur.value;
	if(!check_is_date(env, clipstime, &time)){
		RETURNFAIL("Missing Guard. "
				"add-dayTimeDuration-to-date");
	}
	if(!check_is_dayTimeDuration(env, clipsdur, &dur)){
		RETURNFAIL("Missing Guard. "
				"add-dayTimeDuration-to-date");
	}
	outval = add_dayTimeDuration_to_dateTime(time, dur);
	clipsout = crifi_create_date(env, outval);
	out->value = clipsout.value;
}


void rif_add_dayTimeDuration_to_time(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTimeStamp time, dur, outval;
	UDFValue udftime, udfdur;
	CLIPSValue clipstime, clipsdur, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udftime)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfdur)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipstime.value = udftime.value;
	clipsdur.value = udfdur.value;
	if(!check_is_time(env, clipstime, &time)){
		RETURNFAIL("Missing Guard. "
				"add-dayTimeDuration-to-date");
	}
	if(!check_is_dayTimeDuration(env, clipsdur, &dur)){
		RETURNFAIL("Missing Guard. "
				"add-dayTimeDuration-to-date");
	}
	outval = add_dayTimeDuration_to_dateTime(time, dur);
	clipsout = crifi_create_time(env, outval);
	out->value = clipsout.value;
}


void rif_subtract_yearMonthDuration_from_date(Environment *env, UDFContext *udfc, UDFValue *out){
	YearMonthDuration dur;
	DateTimeStamp time, outval;
	UDFValue udftime, udfdur;
	CLIPSValue clipstime, clipsdur, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udftime)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfdur)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipstime.value = udftime.value;
	clipsdur.value = udfdur.value;
	if(!check_is_date(env, clipstime, &time)){
		RETURNFAIL("Missing Guard. "
				"divide-dayTimeDuration-by-dayTimeDuration");
	}
	if(!check_is_yearMonthDuration(env, clipsdur, &dur)){
		RETURNFAIL("Missing Guard. "
				"divide-dayTimeDuration-by-dayTimeDuration");
	}
	outval = subtract_yearMonthDuration_from_dateTime(time, dur);
	clipsout = crifi_create_date(env, outval);
	out->value = clipsout.value;
}


void rif_subtract_yearMonthDuration_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	YearMonthDuration dur;
	DateTimeStamp time, outval;
	UDFValue udftime, udfdur;
	CLIPSValue clipstime, clipsdur, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udftime)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfdur)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipstime.value = udftime.value;
	clipsdur.value = udfdur.value;
	if(!check_is_dateTime(env, clipstime, &time)){
		RETURNFAIL("Missing Guard. "
				"divide-dayTimeDuration-by-dayTimeDuration");
	}
	if(!check_is_yearMonthDuration(env, clipsdur, &dur)){
		RETURNFAIL("Missing Guard. "
				"divide-dayTimeDuration-by-dayTimeDuration");
	}
	outval = subtract_yearMonthDuration_from_dateTime(time, dur);
	clipsout = crifi_create_dateTime(env, outval);
	out->value = clipsout.value;
}


void rif_subtract_dayTimeDuration_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTimeStamp dur;
	DateTimeStamp time, outval;
	UDFValue udftime, udfdur;
	CLIPSValue clipstime, clipsdur, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udftime)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfdur)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipstime.value = udftime.value;
	clipsdur.value = udfdur.value;
	if(!check_is_dateTime(env, clipstime, &time)){
		RETURNFAIL("Missing Guard. "
				"divide-dayTimeDuration-by-dayTimeDuration");
	}
	if(!check_is_dayTimeDuration(env, clipsdur, &dur)){
		RETURNFAIL("Missing Guard. "
				"divide-dayTimeDuration-by-dayTimeDuration");
	}
	outval = subtract_dayTimeDuration_from_dateTime(time, dur);
	clipsout = crifi_create_dateTime(env, outval);
	out->value = clipsout.value;
}


void rif_subtract_dayTimeDuration_from_date(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTimeStamp dur;
	DateTimeStamp time, outval;
	UDFValue udftime, udfdur;
	CLIPSValue clipstime, clipsdur, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udftime)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfdur)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipstime.value = udftime.value;
	clipsdur.value = udfdur.value;
	if(!check_is_date(env, clipstime, &time)){
		RETURNFAIL("Missing Guard. "
				"divide-dayTimeDuration-by-dayTimeDuration");
	}
	if(!check_is_dayTimeDuration(env, clipsdur, &dur)){
		RETURNFAIL("Missing Guard. "
				"divide-dayTimeDuration-by-dayTimeDuration");
	}
	outval = subtract_dayTimeDuration_from_dateTime(time, dur);
	clipsout = crifi_create_date(env, outval);
	out->value = clipsout.value;
}


void rif_subtract_dayTimeDuration_from_time(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTimeStamp dur;
	DateTimeStamp time, outval;
	UDFValue udftime, udfdur;
	CLIPSValue clipstime, clipsdur, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udftime)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfdur)){
		RETURNFAIL("Argument error for is-literal-date.");
	}
	clipstime.value = udftime.value;
	clipsdur.value = udfdur.value;
	if(!check_is_time(env, clipstime, &time)){
		RETURNFAIL("Missing Guard. "
				"divide-dayTimeDuration-by-dayTimeDuration");
	}
	if(!check_is_dayTimeDuration(env, clipsdur, &dur)){
		RETURNFAIL("Missing Guard. "
				"divide-dayTimeDuration-by-dayTimeDuration");
	}
	outval = subtract_dayTimeDuration_from_dateTime(time, dur);
	clipsout = crifi_create_time(env, outval);
	out->value = clipsout.value;
}


void rif_dateTime_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = *(bool*) udfc->context;
	bool success;
	DateTimeStamp left, right;
	UDFValue udfleft, udfright;
	CLIPSValue clipsleft, clipsright, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfleft)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfright)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	clipsleft.value = udfleft.value;
	clipsright.value = udfright.value;
	if(!check_is_dateTime(env, clipsleft, &left)){
		RETURNFAIL("Missing Guard.");
	}
	if(!check_is_dateTime(env, clipsright, &right)){
		RETURNFAIL("Missing Guard.");
	}
	success = equal_dateTime(left, right);
	if (invert) success = !success;
	out->lexemeValue = CreateBoolean(env, success);
}


void rif_dateTime_less_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = *(bool*) udfc->context;
	bool success;
	DateTimeStamp left, right;
	UDFValue udfleft, udfright;
	CLIPSValue clipsleft, clipsright, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfleft)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfright)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	clipsleft.value = udfleft.value;
	clipsright.value = udfright.value;
	if(!check_is_dateTime(env, clipsleft, &left)){
		RETURNFAIL("Missing Guard.");
	}
	if(!check_is_dateTime(env, clipsright, &right)){
		RETURNFAIL("Missing Guard.");
	}
	success = less_than_dateTime(left, right);
	if (invert) success = !success;
	out->lexemeValue = CreateBoolean(env, success);
}


void rif_dateTime_greater_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = *(bool*) udfc->context;
	bool success;
	DateTimeStamp left, right;
	UDFValue udfleft, udfright;
	CLIPSValue clipsleft, clipsright, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfleft)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfright)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	clipsleft.value = udfleft.value;
	clipsright.value = udfright.value;
	if(!check_is_dateTime(env, clipsleft, &left)){
		RETURNFAIL("Missing Guard.");
	}
	if(!check_is_dateTime(env, clipsright, &right)){
		RETURNFAIL("Missing Guard.");
	}
	success = greater_than_dateTime(left, right);
	if (invert) success = !success;
	out->lexemeValue = CreateBoolean(env, success);
}


void rif_date_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = *(bool*) udfc->context;
	bool success;
	DateTimeStamp left, right;
	UDFValue udfleft, udfright;
	CLIPSValue clipsleft, clipsright, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfleft)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfright)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	clipsleft.value = udfleft.value;
	clipsright.value = udfright.value;
	if(!check_is_date(env, clipsleft, &left)){
		RETURNFAIL("Missing Guard.");
	}
	if(!check_is_date(env, clipsright, &right)){
		RETURNFAIL("Missing Guard.");
	}
	success = equal_dateTime(left, right);
	if (invert) success = !success;
	out->lexemeValue = CreateBoolean(env, success);
}


void rif_date_less_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = *(bool*) udfc->context;
	bool success;
	DateTimeStamp left, right;
	UDFValue udfleft, udfright;
	CLIPSValue clipsleft, clipsright, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfleft)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfright)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	clipsleft.value = udfleft.value;
	clipsright.value = udfright.value;
	if(!check_is_date(env, clipsleft, &left)){
		RETURNFAIL("Missing Guard.");
	}
	if(!check_is_date(env, clipsright, &right)){
		RETURNFAIL("Missing Guard.");
	}
	success = less_than_dateTime(left, right);
	if (invert) success = !success;
	out->lexemeValue = CreateBoolean(env, success);
}


void rif_date_greater_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = *(bool*) udfc->context;
	bool success;
	DateTimeStamp left, right;
	UDFValue udfleft, udfright;
	CLIPSValue clipsleft, clipsright, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfleft)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfright)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	clipsleft.value = udfleft.value;
	clipsright.value = udfright.value;
	if(!check_is_date(env, clipsleft, &left)){
		RETURNFAIL("Missing Guard.");
	}
	if(!check_is_date(env, clipsright, &right)){
		RETURNFAIL("Missing Guard.");
	}
	success = greater_than_dateTime(left, right);
	if (invert) success = !success;
	out->lexemeValue = CreateBoolean(env, success);
}


void rif_time_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = *(bool*) udfc->context;
	bool success;
	DateTimeStamp left, right;
	UDFValue udfleft, udfright;
	CLIPSValue clipsleft, clipsright, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfleft)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfright)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	clipsleft.value = udfleft.value;
	clipsright.value = udfright.value;
	if(!check_is_time(env, clipsleft, &left)){
		RETURNFAIL("Missing Guard.");
	}
	if(!check_is_time(env, clipsright, &right)){
		RETURNFAIL("Missing Guard.");
	}
	success = equal_dateTime(left, right);
	if (invert) success = !success;
	out->lexemeValue = CreateBoolean(env, success);
}


void rif_time_less_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = *(bool*) udfc->context;
	bool success;
	DateTimeStamp left, right;
	UDFValue udfleft, udfright;
	CLIPSValue clipsleft, clipsright, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfleft)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfright)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	clipsleft.value = udfleft.value;
	clipsright.value = udfright.value;
	if(!check_is_time(env, clipsleft, &left)){
		RETURNFAIL("Missing Guard.");
	}
	if(!check_is_time(env, clipsright, &right)){
		RETURNFAIL("Missing Guard.");
	}
	success = less_than_dateTime(left, right);
	if (invert) success = !success;
	out->lexemeValue = CreateBoolean(env, success);
}


void rif_time_greater_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = *(bool*) udfc->context;
	bool success;
	DateTimeStamp left, right;
	UDFValue udfleft, udfright;
	CLIPSValue clipsleft, clipsright, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfleft)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfright)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	clipsleft.value = udfleft.value;
	clipsright.value = udfright.value;
	if(!check_is_time(env, clipsleft, &left)){
		RETURNFAIL("Missing Guard.");
	}
	if(!check_is_time(env, clipsright, &right)){
		RETURNFAIL("Missing Guard.");
	}
	success = greater_than_dateTime(left, right);
	if (invert) success = !success;
	out->lexemeValue = CreateBoolean(env, success);
}


void rif_duration_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = *(bool*) udfc->context;
	bool success;
	DateTimeStamp left, right;
	YearMonthDuration ymleft, ymright;
	UDFValue udfleft, udfright;
	CLIPSValue clipsleft, clipsright, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfleft)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfright)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	clipsleft.value = udfleft.value;
	clipsright.value = udfright.value;
	if(check_is_dayTimeDuration(env, clipsleft, &left)){
		if(check_is_dayTimeDuration(env, clipsright, &right)){
			success = equal_dayTimeDuration(left, right);
		} else if (check_is_yearMonthDuration(env, clipsright, NULL)){
			success = false;
		} else {
			RETURNFAIL("Missing Guard.");
		}
		if (invert) success = !success;
		out->lexemeValue = CreateBoolean(env, success);
	} else if (check_is_yearMonthDuration(env, clipsleft, &ymleft)){
		if (check_is_yearMonthDuration(env, clipsright, &ymright)){
			success = equal_yearMonthDuration(ymleft, ymright);
		} else if (check_is_dayTimeDuration(env, clipsright, NULL)){
			success = false;
		} else {
			RETURNFAIL("Missing Guard.");
		}
		if (invert) success = !success;
		out->lexemeValue = CreateBoolean(env, success);
	} else {
		RETURNFAIL("Missing Guard.");
	}
}


void rif_yearMonthDuration_less_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = *(bool*) udfc->context;
	bool success;
	YearMonthDuration left, right;
	UDFValue udfleft, udfright;
	CLIPSValue clipsleft, clipsright, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfleft)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfright)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	clipsleft.value = udfleft.value;
	clipsright.value = udfright.value;
	if(!check_is_yearMonthDuration(env, clipsleft, &left)){
		RETURNFAIL("Missing Guard.");
	}
	if(!check_is_yearMonthDuration(env, clipsright, &right)){
		RETURNFAIL("Missing Guard.");
	}
	success = less_than_yearMonthDuration(left, right);
	if (invert) success = !success;
	out->lexemeValue = CreateBoolean(env, success);
}


void rif_yearMonthDuration_greater_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = *(bool*) udfc->context;
	bool success;
	YearMonthDuration left, right;
	UDFValue udfleft, udfright;
	CLIPSValue clipsleft, clipsright, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfleft)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfright)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	clipsleft.value = udfleft.value;
	clipsright.value = udfright.value;
	if(!check_is_yearMonthDuration(env, clipsleft, &left)){
		RETURNFAIL("Missing Guard.");
	}
	if(!check_is_yearMonthDuration(env, clipsright, &right)){
		RETURNFAIL("Missing Guard.");
	}
	success = greater_than_yearMonthDuration(left, right);
	if (invert) success = !success;
	out->lexemeValue = CreateBoolean(env, success);
}

void rif_dayTimeDuration_less_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = *(bool*) udfc->context;
	bool success;
	DateTimeStamp left, right;
	UDFValue udfleft, udfright;
	CLIPSValue clipsleft, clipsright, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfleft)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfright)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	clipsleft.value = udfleft.value;
	clipsright.value = udfright.value;
	if(!check_is_dayTimeDuration(env, clipsleft, &left)){
		RETURNFAIL("Missing Guard.");
	}
	if(!check_is_dayTimeDuration(env, clipsright, &right)){
		RETURNFAIL("Missing Guard.");
	}
	success = less_than_dayTimeDuration(left, right);
	if (invert) success = !success;
	out->lexemeValue = CreateBoolean(env, success);
}


void rif_dayTimeDuration_greater_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool invert = *(bool*) udfc->context;
	bool success;
	DateTimeStamp left, right;
	UDFValue udfleft, udfright;
	CLIPSValue clipsleft, clipsright, clipsout;
	if (!UDFFirstArgument(udfc, STRING_BIT, &udfleft)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	if (!UDFNextArgument(udfc, STRING_BIT, &udfright)){
		out->lexemeValue = CreateBoolean(env, false);
		RETURNFAIL("Argument error.");
	}
	clipsleft.value = udfleft.value;
	clipsright.value = udfright.value;
	if(!check_is_dayTimeDuration(env, clipsleft, &left)){
		RETURNFAIL("Missing Guard.");
	}
	if(!check_is_dayTimeDuration(env, clipsright, &right)){
		RETURNFAIL("Missing Guard.");
	}
	success = greater_than_dayTimeDuration(left, right);
	if (invert) success = !success;
	out->lexemeValue = CreateBoolean(env, success);
}
