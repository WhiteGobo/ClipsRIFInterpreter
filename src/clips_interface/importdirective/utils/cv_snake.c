#include "cv_snake.h"

typedef struct cvSnake {
	CLIPSValue value;
	struct cvSnake* next;
} CVSnake;

CVSnake *cvsnake_insert_value(CVSnake* old, CLIPSValue value){
	CVSnake* next = malloc(sizeof(CVSnake));
	if (next == NULL){
		return NULL;
	}
	next->next = old;
	next->value.value = value.value;
	return next;
}

CLIPSValue* cv_snake_to_list(CVSnake* cv_list, int* number_cv_values){
	int i = 0;
	CLIPSValue* retvalues;
	if (number_cv_values == NULL){
		return NULL;
	}
	for (CVSnake *next = cv_list; next != NULL; next = next->next){
		i++;
	}
	*number_cv_values = i;
	retvalues = malloc(i * sizeof(CLIPSValue));
	if (retvalues == NULL){
		return NULL;
	}
	i = 0;
	for (CVSnake *next = cv_list; next != NULL; next = next->next){
		retvalues[i].value = next->value.value;
		i++;
	}
	return retvalues;
}

void free_cvsnake(CVSnake* cv_list){
	CVSnake *next = cv_list;
	CVSnake *tmp;
	while(next != NULL){
		tmp = next->next;
		free(next);
		next = tmp;
	}
}
