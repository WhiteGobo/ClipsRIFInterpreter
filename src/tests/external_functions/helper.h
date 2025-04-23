#include <gtest/gtest.h>
#include <unistd.h>
#include <linux/limits.h>

#include <ffi_clips_interface.h>
#include <ntriplesParser.h>
#include "crifi_import.h"
#include "ffi_constants.h"

#include "info_query.h"

void check_command_true(const char* command);
void fprintf_command_result(FILE* f, const char *command);
