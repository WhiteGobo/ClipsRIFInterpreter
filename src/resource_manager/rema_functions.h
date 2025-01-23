#pragma once

//dont include clips.h directly but only over ffi_clips_interface because
//in c externally defined and not native to c++
//#include <clips.h>
#include <ffi_clips_interface.h>

void print_builtin_literal(Environment *env, UDFContext *udfc, UDFValue *out);
