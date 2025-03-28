#pragma once

typedef enum {
	CRIFI_IMPORT_IP_DIRECT,
	CRIFI_IMPORT_IP_UNKNOWN
} CRIFI_IMPORT_INTERPRETER_ID;

typedef struct importProcess {
	crifi_graph *graph;
	CRIFI_IMPORT_INTERPRETER_ID interpreter_id;
} ImportProcess;
