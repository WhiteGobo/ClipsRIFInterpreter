#pragma once

#include <clips.h>

/**
 * Add internal functions to clips environment.
 *
 * If unsuccesful this is an internal error.
 */
bool add_literal_user_functions(Environment* env);

bool udfvalue_as_integer(UDFValue val, long long *out);
