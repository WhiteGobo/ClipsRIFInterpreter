/** crifi_time.h
 * Implements iso8601 parser and serializer.
 * Also offers methods to transform clipsvalues to <time.h>
 */

#include <time.h>
#include <clips.h>
#include <crifi_numeric.h>

typedef struct crifi_datetimestamp {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int millisecond;
	int timezone_minute;
	bool is_negative_duration;
	bool no_timezone_data;
} DateTimeStamp;

typedef struct crifi_yearMonthDur {
	int year;
	int month;
	bool is_negative_duration;
} YearMonthDuration;

/*
typedef struct crifi_dayTimeDur {
	int year;
	int month;
	bool is_negative_duration;
} DayTimeDuration;
*/

//struct tm
//
bool check_is_date(Environment *env, CLIPSValue val, DateTimeStamp *result);
bool check_is_dateTime(Environment *env, CLIPSValue val, DateTimeStamp *result);
bool check_is_dateTimeStamp(Environment *env, CLIPSValue val, DateTimeStamp *result);
bool check_is_time(Environment *env, CLIPSValue val, DateTimeStamp *result);
bool check_is_dayTimeDuration(Environment *env, CLIPSValue val, DateTimeStamp *result);
bool check_is_yearMonthDuration(Environment *env, CLIPSValue val, YearMonthDuration *result);

CLIPSValue crifi_create_dayTimeDuration(Environment *env, bool invert, int day, int hour, int minute, int seconds, int milliseconds);

CLIPSValue crifi_create_yearMonthDuration(Environment *env, YearMonthDuration val);

DateTimeStamp subtract_dateTime(DateTimeStamp val1, DateTimeStamp val2);

YearMonthDuration add_yearMonthDuration(YearMonthDuration val1, YearMonthDuration val2);
YearMonthDuration subtract_yearMonthDuration(YearMonthDuration val1, YearMonthDuration val2);
YearMonthDuration multiply_yearMonthDuration(YearMonthDuration dur, float mult);
YearMonthDuration divide_yearMonthDuration(YearMonthDuration dur, float mult);

NumericValue divide_yearMonthDuration_by_yearMonthDuration(YearMonthDuration dur1, YearMonthDuration dur2);

DateTimeStamp add_dayTimeDurations(DateTimeStamp dur1, DateTimeStamp dur2);
DateTimeStamp subtract_dayTimeDurations(DateTimeStamp dur1, DateTimeStamp dur2);

DateTimeStamp multiply_dayTimeDuration(DateTimeStamp dur, float mult);
DateTimeStamp divide_dayTimeDuration(DateTimeStamp dur, float mult);

NumericValue divide_dayTimeDuration_by_dayTimeDuration(DateTimeStamp dur1, DateTimeStamp dur2);
DateTimeStamp add_yearMonthDuration_to_dateTime(DateTimeStamp time, YearMonthDuration dur);
DateTimeStamp add_dayTimeDuration_to_dateTime(DateTimeStamp time, DateTimeStamp dur);
DateTimeStamp subtract_yearMonthDuration_from_dateTime(DateTimeStamp time, YearMonthDuration dur);


DateTimeStamp add_dayTimeDuration_to_dateTime(DateTimeStamp time, DateTimeStamp dur);
DateTimeStamp subtract_dayTimeDuration_from_dateTime(DateTimeStamp time, DateTimeStamp dur);


CLIPSValue crifi_create_dateTime(Environment *env, DateTimeStamp time);
CLIPSValue crifi_create_date(Environment *env, DateTimeStamp time);
CLIPSValue crifi_create_time(Environment *env, DateTimeStamp time);

bool equal_dateTime(DateTimeStamp left, DateTimeStamp right);
bool less_than_dateTime(DateTimeStamp left, DateTimeStamp right);
bool greater_than_dateTime(DateTimeStamp left, DateTimeStamp right);

bool greater_than_dayTimeDuration(DateTimeStamp inleft, DateTimeStamp inright);
bool less_than_dayTimeDuration(DateTimeStamp inleft, DateTimeStamp inright);
bool equal_dayTimeDuration(DateTimeStamp inleft, DateTimeStamp inright);

bool greater_than_yearMonthDuration(YearMonthDuration inleft, YearMonthDuration inright);
bool less_than_yearMonthDuration(YearMonthDuration inleft, YearMonthDuration inright);
bool equal_yearMonthDuration(YearMonthDuration left, YearMonthDuration right);
