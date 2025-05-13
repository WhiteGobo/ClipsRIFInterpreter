#pragma once

#include <clips.h>

/**
 * Identifier XS:date XS:dateTime and XS:dateTimeStamp.
 * They are castable in one another.
 *
 * See for more information:
 * `https://www.w3.org/TR/xpath-functions/#casting-from-primitive-to-primitive`_
 */
void rif_is_literal_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
//void rif_is_literal_date(Environment *env, UDFContext *udfc, UDFValue *out);
//void rif_is_literal_dateTimeStamp(Environment *env, UDFContext *udfc, UDFValue *out);

void rif_is_literal_time(Environment *env, UDFContext *udfc, UDFValue *out);

/**
 * Identifier XS:duration, XS:dayTimeDuration and XS:yearMonthDuration.
 */
void rif_is_literal_duration(Environment *env, UDFContext *udfc, UDFValue *out);
//void rif_is_literal_dayTimeDuration(Environment *env, UDFContext *udfc, UDFValue *out);
//void rif_is_literal_yearMonthDuration(Environment *env, UDFContext *udfc, UDFValue *out);


void rif_year_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_month_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_day_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_hours_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_minutes_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_seconds_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_year_from_date(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_month_from_date(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_day_from_date(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_hours_from_time(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_minutes_from_time(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_seconds_from_time(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_timezone_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
//void rif_timezone_from_date(Environment *env, UDFContext *udfc, UDFValue *out);
//void rif_timezone_from_time(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_years_from_duration(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_months_from_duration(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_days_from_duration(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_hours_from_duration(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_minutes_from_duration(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_seconds_from_duration(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_subtract_dateTimes(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_subtract_dates(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_subtract_times(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_add_yearMonthDurations(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_subtract_yearMonthDurations(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_multiply_yearMonthDuration(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_divide_yearMonthDuration(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_divide_yearMonthDuration_by_yearMonthDuration(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_add_dayTimeDurations(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_subtract_dayTimeDurations(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_multiply_dayTimeDuration(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_divide_dayTimeDuration(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_divide_dayTimeDuration_by_dayTimeDuration(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_add_yearMonthDuration_to_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_add_yearMonthDuration_to_date(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_add_dayTimeDuration_to_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_add_dayTimeDuration_to_date(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_add_dayTimeDuration_to_time(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_subtract_yearMonthDuration_from_date(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_subtract_yearMonthDuration_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_subtract_dayTimeDuration_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_subtract_dayTimeDuration_from_date(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_subtract_dayTimeDuration_from_time(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_dateTime_equal(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_dateTime_less_than(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_dateTime_greater_than(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_date_equal(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_date_less_than(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_date_greater_than(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_time_equal(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_time_less_than(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_time_greater_than(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_duration_equal(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_yearMonthDuration_less_than(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_yearMonthDuration_greater_than(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_dayTimeDuration_less_than(Environment *env, UDFContext *udfc, UDFValue *out);
void rif_dayTimeDuration_greater_than(Environment *env, UDFContext *udfc, UDFValue *out);
