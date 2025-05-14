#pragma once

bool castable_as_true(char* lexical, char *x, size_t xl);
bool castable_as_false(char* lexical, char *x, size_t xl);
bool castable_as_double(char* lexical, char *x, size_t xl);
bool castable_as_hexadecimal(char *lexical, char *x, size_t xl);
bool castable_as_long(char *lexical, char *x, size_t xl);
bool is_string_datatype(char *x, size_t xl);
