/**
 * See example_info_query.c for an example.
 */
#pragma once

#include <ffi_clips_interface.h>
#include <n3parser.h>

#define TRIPLETEMPLATE "TripleTemplate"
#define TRIPLESLOTSUBJECT "subject"
#define TRIPLESLOTPREDICATE "predicate"
#define TRIPLESLOTOBJECT "object"
#define TRIPLESLOTCONTEXT "context"

#ifdef __cplusplus
extern "C" {
#endif

Fact *get_next_triple(Environment *env, Fact *f);

bool clipsvalue_is_uri(Environment *env, CLIPSValue val);
bool clipsvalue_is_bnode(Environment *env, CLIPSValue val);
bool clipsvalue_is_literal(Environment *env, CLIPSValue val);

char *extract_uri(Environment *env, TypeHeader *head);
char *extract_bnodeid(Environment *env, TypeHeader *head);

char *extract_lexical(Environment *env, TypeHeader *head);
char *extract_datatype(Environment *env, TypeHeader *head);
char *extract_lang(Environment *env, TypeHeader *head);

#ifdef __cplusplus
} //extern "C"
#endif
