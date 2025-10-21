#include <gtest/gtest.h>
#include <unistd.h>
#include <linux/limits.h>

#include <ffi_clips_interface.h>
#include "crifi_import.h"
#include "ffi_constants.h"

#include "info_query.h"
#include "helper.h"



TEST(ExternalFunctionsTime, isLiteralDate){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-date> \"2000-12-13-11%3A00^^http://www.w3.org/2001/XMLSchema#date\" )"
			);
}

TEST(ExternalFunctionsTime, isLiteralDateTime){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-dateTime> \"2000-12-13T00%3A11%3A11.3^^http://www.w3.org/2001/XMLSchema#dateTime\" )"
			);
}

TEST(ExternalFunctionsTime, isLiteralDateTimeStamp){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-dateTimeStamp> \"2000-12-13T00%3A11%3A11.3Z^^http://www.w3.org/2001/XMLSchema#dateTimeStamp\" )"
			);
}

TEST(ExternalFunctionsTime, isLiteralTime){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-time> \"00%3A11%3A11.3Z^^http://www.w3.org/2001/XMLSchema#time\" )"
			);
}

TEST(ExternalFunctionsTime, isLiteralDayTimeDuration){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-dayTimeDuration> \"P3DT2H^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )"
			);
}

TEST(ExternalFunctionsTime, isLiteralYearMonthDuration){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-yearMonthDuration> \"P1Y2M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" )"
			);
}

TEST(ExternalFunctionsTime, isLiteralNotDate){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-not-date> \"foo\" )"
			);
}

TEST(ExternalFunctionsTime, isLiteralNotDateTime){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-not-dateTime> \"foo\" )"
			);
}

TEST(ExternalFunctionsTime, isLiteralNotDateTimeStamp){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-not-dateTimeStamp> \"foo\" )"
			);
}

TEST(ExternalFunctionsTime, isLiteralNotTime){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-not-time> \"foo\" )"
			);
}

TEST(ExternalFunctionsTime, isLiteralNotDayTimeDuration){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-not-dayTimeDuration> \"foo\" )"
			);
}

TEST(ExternalFunctionsTime, isLiteralNotYearMonthDuration){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-not-yearMonthDuration> \"foo\" )"
			);
}

TEST(ExternalFunctionsTime, castDate){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-date> (<http://www.w3.org/2001/XMLSchema#date> \"2000-12-13-11%3A00\" ) )"
			);
}

TEST(ExternalFunctionsTime, castDateTime){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-dateTime> (<http://www.w3.org/2001/XMLSchema#dateTime> \"2000-12-13T00%3A11%3A11.3\" ) )"
			);
}

TEST(ExternalFunctionsTime, castDateTimeStamp){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-dateTimeStamp> (<http://www.w3.org/2001/XMLSchema#dateTimeStamp> \"2000-12-13T00%3A11%3A11.3Z\" ) )"
			);
}

TEST(ExternalFunctionsTime, castTime){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-time> (<http://www.w3.org/2001/XMLSchema#time> \"00%3A11%3A11.3Z\" ) )"
			);
}

TEST(ExternalFunctionsTime, castDayTimeDuration){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-dayTimeDuration> (<http://www.w3.org/2001/XMLSchema#dayTimeDuration> \"P3DT2H\" ) )"
			);
}

TEST(ExternalFunctionsTime, castYearMonthDuration){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#is-literal-yearMonthDuration> (<http://www.w3.org/2001/XMLSchema#yearMonthDuration> \"P1Y2M\" ) )"
			);
}

TEST(ExternalFunctionsTime, yearFromDateTime){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#year-from-dateTime> \"1999-12-31T24%3A00%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" )\"2000^^http://www.w3.org/2001/XMLSchema#integer\")"
			);
}

TEST(ExternalFunctionsTime, monthFromDateTime){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#month-from-dateTime> \"1999-05-31T13%3A20%3A00-05%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" )\"5^^http://www.w3.org/2001/XMLSchema#integer\")"
			);
}

TEST(ExternalFunctionsTime, dayFromDateTime){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#day-from-dateTime> \"1999-05-31T13%3A20%3A00-05%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" )\"31^^http://www.w3.org/2001/XMLSchema#integer\")"
			);
}

TEST(ExternalFunctionsTime, hoursFromDateTime){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#hours-from-dateTime> \"1999-05-31T08%3A20%3A00-05%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" )\"8^^http://www.w3.org/2001/XMLSchema#integer\")"
			);
}

TEST(ExternalFunctionsTime, minuteFromDateTime){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#minutes-from-dateTime> \"1999-05-31T13%3A20%3A00-05%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" )\"20^^http://www.w3.org/2001/XMLSchema#integer\")"
			);
}

TEST(ExternalFunctionsTime, secondsFromDateTime){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#seconds-from-dateTime> \"1999-05-31T13%3A20%3A00-05%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" )\"0^^http://www.w3.org/2001/XMLSchema#integer\")"
			);
}

TEST(ExternalFunctionsTime, yearFromDate){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#year-from-date> \"1999-12-31^^http://www.w3.org/2001/XMLSchema#date\" )\"1999^^http://www.w3.org/2001/XMLSchema#integer\")"
			);
}

TEST(ExternalFunctionsTime, monthFromDate){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#month-from-date> \"1999-05-31^^http://www.w3.org/2001/XMLSchema#date\" )\"5^^http://www.w3.org/2001/XMLSchema#integer\")"
			);
}

TEST(ExternalFunctionsTime, dayFromDate){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#day-from-date> \"1999-05-31^^http://www.w3.org/2001/XMLSchema#date\" )\"31^^http://www.w3.org/2001/XMLSchema#integer\")"
			);
}

TEST(ExternalFunctionsTime, hoursFromTime){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#hours-from-time> \"08%3A20%3A00-05%3A00^^http://www.w3.org/2001/XMLSchema#time\" )\"8^^http://www.w3.org/2001/XMLSchema#integer\")"
			);
}

TEST(ExternalFunctionsTime, minuteFromTime){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#minutes-from-time> \"13%3A20%3A00-05%3A00^^http://www.w3.org/2001/XMLSchema#time\" )\"20^^http://www.w3.org/2001/XMLSchema#integer\")"
			);
}

TEST(ExternalFunctionsTime, secondsFromTime){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#seconds-from-time> \"13%3A20%3A00-05%3A00^^http://www.w3.org/2001/XMLSchema#time\" )\"0^^http://www.w3.org/2001/XMLSchema#integer\")"
			);
}

TEST(ExternalFunctionsTime, timezoneFromDateTime){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#timezone-from-dateTime> \"1999-05-31T13%3A20%3A00-05%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" )\"-PT5H^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\")"
			);
}

TEST(ExternalFunctionsTime, timezoneFromDate){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#timezone-from-date> \"1999-05-31-05%3A00^^http://www.w3.org/2001/XMLSchema#date\" )\"-PT5H^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\")"
			);
}

TEST(ExternalFunctionsTime, timezoneFromTime){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#timezone-from-time> \"13%3A20%3A00-05%3A00^^http://www.w3.org/2001/XMLSchema#time\" )\"-PT5H^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\")"
			);
}

TEST(ExternalFunctionsTime, yearsFromDuration){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#years-from-duration> \"P20Y15M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" )\"21^^http://www.w3.org/2001/XMLSchema#integer\")"
			);
}

TEST(ExternalFunctionsTime, monthFromDuration){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#months-from-duration> \"P20Y15M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" )\"3^^http://www.w3.org/2001/XMLSchema#integer\")"
			);
}

TEST(ExternalFunctionsTime, daysFromDuration){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#days-from-duration> \"P3DT10H^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )\"3^^http://www.w3.org/2001/XMLSchema#integer\")"
			);
}

TEST(ExternalFunctionsTime, hoursFromDuration){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#hours-from-duration> \"P3DT10H^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )\"10^^http://www.w3.org/2001/XMLSchema#integer\")"
			);
}

TEST(ExternalFunctionsTime, minutesFromDuration){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#minutes-from-duration> \"-P5DT12H30M^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )\"-30^^http://www.w3.org/2001/XMLSchema#integer\")"
			);
}

TEST(ExternalFunctionsTime, secondsFromDuration){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#seconds-from-duration> \"P3DT10H12.5S^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )\"12.5^^http://www.w3.org/2001/XMLSchema#decimal\")"
			);
}

TEST(ExternalFunctionsTime, subtractDateTimes){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#subtract-dateTimes> \"2000-10-30T06%3A12%3A00-05%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" \"1999-11-28T09%3A00%3A00Z^^http://www.w3.org/2001/XMLSchema#dateTime\" )\"P337DT2H12M^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\")"
			);
}

TEST(ExternalFunctionsTime, subtractDates){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#subtract-dates> \"2000-10-30Z^^http://www.w3.org/2001/XMLSchema#date\" \"1999-11-28Z^^http://www.w3.org/2001/XMLSchema#date\" )\"P337D^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\")"
			);
}

TEST(ExternalFunctionsTime, subtractTimes){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#subtract-times> \"11%3A12%3A00Z^^http://www.w3.org/2001/XMLSchema#time\" \"04%3A00%3A00Z^^http://www.w3.org/2001/XMLSchema#time\" )\"PT7H12M^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\")"
			);
}

TEST(ExternalFunctionsTime, addYearMonthDurations){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#add-yearMonthDurations> \"P2Y11M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" \"P3Y3M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" )\"P6Y2M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\")"
			);
}

TEST(ExternalFunctionsTime, subtractYearMonthDurations){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#subtract-yearMonthDurations> \"P2Y11M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" \"P3Y3M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" )\"-P4M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\")"
			);
}

TEST(ExternalFunctionsTime, multiplyYearMonthDuration){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#multiply-yearMonthDuration> \"P2Y11M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" \"2.3^^http://www.w3.org/2001/XMLSchema#decimal\" )\"P6Y9M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\")"
			);
}

TEST(ExternalFunctionsTime, divideYearMonthDuration){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#divide-yearMonthDuration> \"P2Y11M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" \"1.5^^http://www.w3.org/2001/XMLSchema#decimal\" )\"P1Y11M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\")"
			);
}

TEST(ExternalFunctionsTime, divideYearMonthDurationByYearMonthDuration){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#divide-yearMonthDuration-by-yearMonthDuration> \"P3Y4M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" \"-P1Y4M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" )\"-2.5^^http://www.w3.org/2001/XMLSchema#decimal\")"
			);
}

TEST(ExternalFunctionsTime, addDayTimeDurations){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#add-dayTimeDurations> \"P2DT12H5M^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" \"P5DT12H^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )\"P8DT5M^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\")"
			);
}

TEST(ExternalFunctionsTime, subtractDayTimeDurations){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#subtract-dayTimeDurations> \"P2DT12H^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" \"P1DT10H30M^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )\"P1DT1H30M^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\")"
			);
}

TEST(ExternalFunctionsTime, multiplyDayTimeDuration){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#multiply-dayTimeDuration> \"PT2H10M^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" \"2.1^^http://www.w3.org/2001/XMLSchema#decimal\" )\"PT4H33M^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\")"
			);
}

TEST(ExternalFunctionsTime, divideDayTimeDuration){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#divide-dayTimeDuration> \"P4D^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" \"2^^http://www.w3.org/2001/XMLSchema#integer\" )\"P2D^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\")"
			);
}

TEST(ExternalFunctionsTime, divideDayTimeDurationByDayTimeDuration){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#divide-dayTimeDuration-by-dayTimeDuration> \"P4D^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" \"P2D^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )\"2^^http://www.w3.org/2001/XMLSchema#integer\")"
			);
}

TEST(ExternalFunctionsTime, addYearMonthDurationToDateTime){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#add-yearMonthDuration-to-dateTime> \"2000-10-30T11%3A12%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" \"P1Y2M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" )\"2001-12-30T11%3A12%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\")"
			);
}

TEST(ExternalFunctionsTime, addYearMonthDurationToDate){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#add-yearMonthDuration-to-date> \"2000-10-30^^http://www.w3.org/2001/XMLSchema#date\" \"P1Y2M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" )\"2001-12-30^^http://www.w3.org/2001/XMLSchema#date\")"
			);
}

TEST(ExternalFunctionsTime, addDayTimeDurationToDateTime){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#add-dayTimeDuration-to-dateTime> \"2000-10-30T11%3A12%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" \"P3DT1H15M^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )\"2000-11-02T12%3A27%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\")"
			);
}

TEST(ExternalFunctionsTime, addDayTimeDurationToDate){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#add-dayTimeDuration-to-date> \"2004-10-30Z^^http://www.w3.org/2001/XMLSchema#date\" \"P2DT2H30M0S^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )\"2004-11-01Z^^http://www.w3.org/2001/XMLSchema#date\")"
			);
}

TEST(ExternalFunctionsTime, addDayTimeDurationToTime){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#add-dayTimeDuration-to-time> \"11%3A12%3A00^^http://www.w3.org/2001/XMLSchema#time\" \"P3DT1H15M^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )\"12%3A27%3A00^^http://www.w3.org/2001/XMLSchema#time\")"
			);
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#add-dayTimeDuration-to-time> \"23%3A12%3A00%2B03%3A00^^http://www.w3.org/2001/XMLSchema#time\" \"P1DT3H15M^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )\"02%3A27%3A00%2B03%3A00^^http://www.w3.org/2001/XMLSchema#time\")"
			);
}

TEST(ExternalFunctionsTime, subtractYearMonthDurationFromDateTime){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#subtract-yearMonthDuration-from-dateTime> \"2000-10-30T11%3A12%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" \"P1Y2M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" )\"1999-08-30T11%3A12%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\")"
			);
}

TEST(ExternalFunctionsTime, subtractYearMonthDurationFromDate){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#subtract-yearMonthDuration-from-date> \"2000-10-30^^http://www.w3.org/2001/XMLSchema#date\" \"P1Y2M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" )\"1999-08-30^^http://www.w3.org/2001/XMLSchema#date\")"
			);
}

TEST(ExternalFunctionsTime, subtractDayTimeDurationFromDateTime){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#subtract-dayTimeDuration-from-dateTime> \"2000-10-30T11%3A12%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" \"P3DT1H15M^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )\"2000-10-27T09%3A57%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\")"
			);
}

TEST(ExternalFunctionsTime, subtractDayTimeDurationFromDate){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#subtract-dayTimeDuration-from-date> \"2000-10-30^^http://www.w3.org/2001/XMLSchema#date\" \"P3DT1H15M^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )\"2000-10-26^^http://www.w3.org/2001/XMLSchema#date\")"
			);
}

TEST(ExternalFunctionsTime, subtractDayTimeDurationFromTime){
	check_command_true( 
			"(eq (<http://www.w3.org/2007/rif-builtin-function#subtract-dayTimeDuration-from-time> \"11%3A12%3A00^^http://www.w3.org/2001/XMLSchema#time\" \"P3DT1H15M^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )\"09%3A57%3A00^^http://www.w3.org/2001/XMLSchema#time\")"
			);
}

TEST(ExternalFunctionsTime, dateTimeEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#dateTime-equal> \"2002-04-02T12%3A00%3A00-01%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" \"2002-04-02T17%3A00%3A00%2B04%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" )"
			);
}

TEST(ExternalFunctionsTime, dateTimeLessThan){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#dateTime-less-than> \"2002-04-01T12%3A00%3A00-01%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" \"2002-04-02T17%3A00%3A00%2B04%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" )"
			);
}

TEST(ExternalFunctionsTime, dateTimeGreaterThan){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#dateTime-greater-than> \"2002-04-03T12%3A00%3A00-01%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" \"2002-04-02T17%3A00%3A00%2B04%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" )"
			);
}

TEST(ExternalFunctionsTime, dateEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#date-equal> \"2004-12-25-12%3A00^^http://www.w3.org/2001/XMLSchema#date\" \"2004-12-26%2B12%3A00^^http://www.w3.org/2001/XMLSchema#date\" )"
			);
}

TEST(ExternalFunctionsTime, dateLessThan){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#date-less-than> \"2004-12-24^^http://www.w3.org/2001/XMLSchema#date\" \"2004-12-26^^http://www.w3.org/2001/XMLSchema#date\" )"
			);
}

TEST(ExternalFunctionsTime, dateGreaterThan){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#date-greater-than> \"2004-12-26^^http://www.w3.org/2001/XMLSchema#date\" \"2004-12-25^^http://www.w3.org/2001/XMLSchema#date\" )"
			);
}

TEST(ExternalFunctionsTime, timeEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#time-equal> \"21%3A30%3A00%2B10%3A30^^http://www.w3.org/2001/XMLSchema#time\" \"06%3A00%3A00-05%3A00^^http://www.w3.org/2001/XMLSchema#time\" )"
			);
}

TEST(ExternalFunctionsTime, timeLessThan){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#time-less-than> \"20%3A30%3A00%2B10%3A30^^http://www.w3.org/2001/XMLSchema#time\" \"06%3A00%3A00-05%3A00^^http://www.w3.org/2001/XMLSchema#time\" )"
			);
}

TEST(ExternalFunctionsTime, timeGreaterThan){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#time-greater-than> \"22%3A30%3A00%2B10%3A30^^http://www.w3.org/2001/XMLSchema#time\" \"06%3A00%3A00-05%3A00^^http://www.w3.org/2001/XMLSchema#time\" )"
			);
}

TEST(ExternalFunctionsTime, durationEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#duration-equal> \"P1Y^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" \"P12M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" )"
			);
}

TEST(ExternalFunctionsTime, yearMonthDurationLessThan){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#yearMonthDuration-less-than> \"P1Y^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" \"P13M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" )"
			);
}

TEST(ExternalFunctionsTime, yearMonthDurationGreaterThan){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#yearMonthDuration-greater-than> \"P1Y^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" \"P11M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" )"
			);
}

TEST(ExternalFunctionsTime, dayTimeDurationLessThan){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#dayTimeDuration-less-than> \"P1D^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" \"PT25H^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )"
			);
}

TEST(ExternalFunctionsTime, dayTimeDurationGreaterThan){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#dayTimeDuration-greater-than> \"P1D^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" \"PT23H^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )"
			);
}

TEST(ExternalFunctionsTime, dateTimeNotEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#dateTime-not-equal> \"2002-04-01T12%3A00%3A00-01%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" \"2002-04-02T17%3A00%3A00%2B04%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" )"
			);
}

TEST(ExternalFunctionsTime, dateTimeLessThanOrEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#dateTime-less-than-or-equal> \"2002-04-01T12%3A00%3A00-01%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" \"2002-04-02T17%3A00%3A00%2B04%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" )"
			);
}

TEST(ExternalFunctionsTime, dateTimeGreaterThanOrEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#dateTime-greater-than-or-equal> \"2002-04-03T12%3A00%3A00-01%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" \"2002-04-02T17%3A00%3A00%2B04%3A00^^http://www.w3.org/2001/XMLSchema#dateTime\" )"
			);
}

TEST(ExternalFunctionsTime, dateNotEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#date-not-equal> \"2004-12-24^^http://www.w3.org/2001/XMLSchema#date\" \"2004-12-26^^http://www.w3.org/2001/XMLSchema#date\" )"
			);
}

TEST(ExternalFunctionsTime, dateLessThanOrEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#date-less-than-or-equal> \"2004-12-24^^http://www.w3.org/2001/XMLSchema#date\" \"2004-12-26^^http://www.w3.org/2001/XMLSchema#date\" )"
			);
}

TEST(ExternalFunctionsTime, dateGreaterThanOrEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#date-greater-than-or-equal> \"2004-12-26^^http://www.w3.org/2001/XMLSchema#date\" \"2004-12-25^^http://www.w3.org/2001/XMLSchema#date\" )"
			);
}

TEST(ExternalFunctionsTime, timeNotEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#time-not-equal> \"20%3A30%3A00%2B10%3A30^^http://www.w3.org/2001/XMLSchema#time\" \"06%3A00%3A00-05%3A00^^http://www.w3.org/2001/XMLSchema#time\" )"
			);
}

TEST(ExternalFunctionsTime, timeLessThanOrEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#time-less-than-or-equal> \"20%3A30%3A00%2B10%3A30^^http://www.w3.org/2001/XMLSchema#time\" \"06%3A00%3A00-05%3A00^^http://www.w3.org/2001/XMLSchema#time\" )"
			);
}

TEST(ExternalFunctionsTime, timeGreaterThanOrEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#time-greater-than-or-equal> \"22%3A30%3A00%2B10%3A30^^http://www.w3.org/2001/XMLSchema#time\" \"06%3A00%3A00-05%3A00^^http://www.w3.org/2001/XMLSchema#time\" )"
			);
}

TEST(ExternalFunctionsTime, durationNotEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#duration-not-equal> \"P1Y^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" \"P1M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" )"
			);
}

TEST(ExternalFunctionsTime, yearMonthDurationLessThanOrEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#yearMonthDuration-less-than-or-equal> \"P1Y^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" \"P13M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" )"
			);
}

TEST(ExternalFunctionsTime, yearMonthDurationGreaterThanOrEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#yearMonthDuration-greater-than-or-equal> \"P1Y^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" \"P11M^^http://www.w3.org/2001/XMLSchema#yearMonthDuration\" )"
			);
}

TEST(ExternalFunctionsTime, dayTimeDurationLessThanOrEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#dayTimeDuration-less-than-or-equal> \"P1D^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" \"PT25H^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )"
			);
}

TEST(ExternalFunctionsTime, dayTimeDurationGreaterThanOrEqual){
	check_command_true( 
			"(<http://www.w3.org/2007/rif-builtin-predicate#dayTimeDuration-greater-than-or-equal> \"P1D^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" \"PT23H^^http://www.w3.org/2001/XMLSchema#dayTimeDuration\" )"
			);
}
