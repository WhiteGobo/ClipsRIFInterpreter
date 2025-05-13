#pragma once

#include "crifi_time.h"

void dayTimeDuration_regex_to_crifiDuration(char *lexical, regmatch_t matches[14], CrifiDuration* result);
void yearMonthDuration_regex_to_crifiDuration(char *lexical, regmatch_t matches[14], CrifiDuration* result);

void normalize_duration(CrifiDuration *result);

void transform_yearMonthDuration_match(char *lexical, regmatch_t matches[14], YearMonthDuration* result);

void transform_dayTimeDuration_match(char *lexical, regmatch_t matches[14], DateTimeStamp* result);
