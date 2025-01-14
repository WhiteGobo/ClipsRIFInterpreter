#include <stdio.h>
#include <stdlib.h>
#include "uriencode.h"
#include "internal_uriencode.h"

char* uri_encode(const unsigned char *src, const size_t len, char *dst){
	unsigned char x;
	for (int i = 0; i < len; i++){
		x = src[i];
		if( check_decode[x] ){
			dst += sprintf(dst, "%%%2X", x);
		} else {
			*dst = x;
			dst++;
		}
	}
	*dst ='\0';
	return dst;
}

char *iri_to_uri(const unsigned char *src, const size_t len, char *dst){
	unsigned char x;
	for (int i = 0; i < len; i++){
		x = src[i];
		if( check_uri_coded[x] ){
			dst += sprintf(dst, "%%%2X", x);
		} else {
			*dst = x;
			dst++;
		}
	}
	*dst ='\0';
	return dst;
}

char *escape_html_uri(const unsigned char *src, const size_t len, char *dst){
	unsigned char x;
	for (int i = 0; i < len; i++){
		x = src[i];
		if( check_US_ASCII_coded[x] ){
			dst += sprintf(dst, "%%%2X", x);
		} else {
			*dst = x;
			dst++;
		}
	}
	*dst ='\0';
	return dst;
}

char* uri_decode(const unsigned char *src, const size_t len, char *dst){
	unsigned char first, second;
	for (int i = 0; i < len; i++){
		if( (src[i] == '%') && (i < len - 2) ){
			first = hexval[src[i+1]];
			second = hexval[src[i+2]];
			*dst = (first << 4) | second;
			i += 2;
		} else {
			*dst = src[i];
		}
		dst++;
	}
	*dst = '\0';
	return dst;
}

