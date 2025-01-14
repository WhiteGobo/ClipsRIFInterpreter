#pragma once

#include <stdbool.h>

char* uri_encode(const unsigned char *src, const size_t len, char *dst);
char* iri_to_uri(const unsigned char *src, const size_t len, char *dst);
char *escape_html_uri(const unsigned char *src, const size_t len, char *dst);

char* uri_decode(const unsigned char *src, const size_t len, char *dst);
