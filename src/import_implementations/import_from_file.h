#pragma once

#include <stdio.h>

RET_CRIFI_IMPORT import_data_from_file(crifi_graph *graph,
		FILE *inputfile, const char *filename,
		ImportProcess *process, const char *syntax_uri);
