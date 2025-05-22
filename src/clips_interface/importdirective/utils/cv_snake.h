#pragma once
#include "ffi_clips_interface.h"

typedef struct cvSnake CVSnake;

CVSnake *cvsnake_insert_value(CVSnake* old, CLIPSValue value);

CLIPSValue* cv_snake_to_list(CVSnake* cv_list, int* number_cv_values);

void free_cvsnake(CVSnake* cv_list);
