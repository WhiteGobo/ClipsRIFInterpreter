#pragma once

#include <clips.h>

typedef enum {
	IEQ_FALSE,
	IEQ_TRUE,
	IEQ_ERROR,
} IEQ_RET;

IEQ_RET internal_equal(Environment *env, CLIPSValue *left, CLIPSValue *right);
