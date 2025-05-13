#pragma once

#include "crifi_time.h"

//TODO: rename to CRIFITIMEMATCHSIZE
#define MATCHESSIZETIME 14

void normalize_dateTimeStamp(DateTimeStamp *result);


void date_regex_to_crifiDateTimeStamp(char *lexical,
			regmatch_t matches[MATCHESSIZETIME],
			DateTimeStamp* result);
void dateTimeStamp_regex_to_crifiDateTimeStamp(char *lexical,
			regmatch_t matches[MATCHESSIZETIME],
			DateTimeStamp* result);
void time_regex_to_crifiDateTimeStamp(char *lexical,
			regmatch_t matches[MATCHESSIZETIME],
			DateTimeStamp* result);

void transform_date_match(char *lexical,
			regmatch_t matches[MATCHESSIZETIME],
			DateTimeStamp* result);
void transform_dateTimeStamp_match(char *lexical,
			regmatch_t matches[MATCHESSIZETIME],
			DateTimeStamp* result);
void transform_time_match(char *lexical,
			regmatch_t matches[MATCHESSIZETIME],
			DateTimeStamp* result);
