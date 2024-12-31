/** \file ffi_clips_interface.h
 * Public interface asdf
 *
 */
#pragma once
#ifndef _FFIINTERFACE_H_
#define _FFIINTERFACE_H_

// See `https://stackoverflow.com/questions/623219/is-private-a-c-keyword`_
// for more information. public is needed for declaration as public in docs
// and in libraries.
// fails with gtest if cplusplus isnt checked.
#ifndef __cplusplus
#ifndef public
/// See \ref FFI_PLUGIN_EXPORT
#define public
#endif
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>//needed for extern working boolean

//#if defined(__has_include)
//#if __has_include("myinclude.h")
# include <clips.h>
//#endif
//#endif

//#if _WIN32
//#include <windows.h>
//#else
//#include <pthread.h>
//#include <unistd.h>
//#endif

//#if _WIN32
//#define FFI_PLUGIN_EXPORT public __declspec(dllexport)
//#else
/// Used Used for declaration of a function as public
#define FFI_PLUGIN_EXPORT
//#endif

/// Macro to iterate through TriplesLinkedList
#define FOREACH_TRIPLE(tllist, current) for (struct TriplesLinkedList *current = tllist; current != NULL; current=current->rest)


#ifdef __cplusplus
extern "C" {
#endif


/**
 * Return value of \ref load_config.
 *
 * If used with flutters ffigen, please see under the
 * keyword silence-enum-warning in `https://pub.dev/packages/ffigen`_.
 */
typedef enum {
	/// No Error
	CTC_LC_NO_ERROR = 0,
	/// Couldnt open file
	CTC_LC_OPEN_FILE_ERROR = 1,
	/// Error during parsing
	CTC_LC_PARSING_ERROR = 2,
	/// Unprocessed error
	CTC_LC_UNKNOWN_STATE = 3,
} RET_LOADCONFIG;

/**
 * Describe which type the value of DynamicValue is.
 */
typedef enum {
	/// no return value(?)
	CTC_DYNAMIC_VOID = 0,
	/// use ?
	CTC_DYNAMIC_ERROR = 1,
	/// use val.string
	CTC_DYNAMIC_STRING = 2,
	/// use val.integer
	CTC_DYNAMIC_INT = 3,
	/// use val.boolean
	CTC_DYNAMIC_BOOL = 4,
} DYNAMIC_TYPE;

typedef enum {
	CNT_URI = 0,
	CNT_BNODE = 1,
	CNT_LITERAL = 2,
} CLIPSNODETYPE;

/**
 * Error description during \ref eval
 */
typedef enum {
	CTC_CTD_CANTTRANSLATE = 0,
	/// parsing error
	CTC_CTD_PARSING_ERROR = 1,
	CTC_CTD_PROCESSING_ERROR = 2,
} CLIPS_TO_DYNAMIC_ERROR;


/// A char* which contains an encoded string
typedef const char* Utf8String;

/// A string which contains a node in N3_Format
typedef const char* N3String;

typedef struct crifiExtension {
	void *(*generate_context)();
	struct crifiExtension *nextExtension;
} CRIFIExtension;

/**
 * contains the graph and additional information. Used to transfer all needed
 * data for c framework as a single struct.
 * Use init_graph to create a new one.
 */
struct clips_graph_container
{
	/// inErrorState != 0 if some irreperaible problem occured
	int inErrorState;

	/// im not sure
	Environment *environment;

	CRIFIExtension *extensions;
};

/**
 * Arbitrary value. It's recommended to free via \ref free_dynamic_value.
 * Freeing is necessary if it represents a string.
 */
struct DynamicValue
{
	/// header
	DYNAMIC_TYPE type;
	/** \union DynamicValueContent
	 * asdf
	 */
	/** \var val
	 * place for the value. use specific value depending on type
	 */
	union DynamicValueContent {
		/// im not sure
		void *content;
		/// value if type is string
		char *string;
		/// value if type is integer(CTC_DYNAMIC_INT)
		long long integer;
		///value if type is bool(CTC_DYNMIC_BOOL)
		bool boolean;
		/// value if type is error(CTC_DYNAMIC_ERROR)
		CLIPS_TO_DYNAMIC_ERROR error;
	} val;
};

/**
 * Used to transport a list of triples outside the framework.
 * Use free_linked_list after usage.
 *
 * Helperfunction: \ref FOREACH_TRIPLE
 */
struct TriplesLinkedList
{
	/// first value of triple
	N3String subject;
	/// second value of triple
	N3String predicate;
	/// third value of triple
	N3String object;
	/// rest of the list.
	struct TriplesLinkedList *rest;
};

/**
 * Return type of build_triple
 */
typedef enum {
	CRI_RET_BUILDTRIPLE_NOERROR = 0,
	CRI_RET_PARSING_ERROR_SUBJECT,
	CRI_RET_PARSING_ERROR_PREDICATE,
	CRI_RET_PARSING_ERROR_OBJECT,
	/**
	 * Returned when an internal error occured, which shouldnt be possible.
	 */
	CRI_RET_INTERNAL_ERROR,
	/**
	 * Raised when fbassert returns FBE_DEFTEMPLATE_NOT_FOUND_ERROR,
	 * FBE_IMPLIED_DEFTEMPLATE_ERROR or FBE_NULL_POINTER_ERROR
	 */
	CRI_RET_MISSING_TRIPLE_TEMPLATE,
	/**
	 * Raised when fbassert returns FBE_RULE_NETWORK_ERROR
	 */
	CRI_RET_BROKEN_RULE_NETWORK,
	/**
	 * Raised when fbassert returns FBE_COULD_NOT_ASSERT_ERROR
	 */
	CRI_RET_NOT_ASSERT_ERROR,
} CRI_RET_BUILDTRIPLE;

#define ASSERT_NOERROR(assert_return_value) (assert_return_value.parsing_error == CRI_RET_BUILDTRIPLE_NOERROR.parsing_error) && (assert_return_value.slotnumber == CRI_RET_BUILDTRIPLE_NOERROR.slotnumber)


/**
 * frees given struct TriplesLinkedList
 */
FFI_PLUGIN_EXPORT void free_linked_list(struct TriplesLinkedList *);

/**
 * return last TriplesLinkedList in list.
 */
FFI_PLUGIN_EXPORT struct TriplesLinkedList *last_triple(struct TriplesLinkedList *);

/**
 * append a new TriplesLinkedList. Creates new list if first is NULL.
 */
FFI_PLUGIN_EXPORT struct TriplesLinkedList *append_triple(struct TriplesLinkedList *first, N3String subject, N3String predicate, N3String object);

/**
 * concatenate two TriplesLinkedList by linking the start of the second
 * to the first. Returns 0 if success.
 */
FFI_PLUGIN_EXPORT int concatenate_triples(struct TriplesLinkedList *first, struct TriplesLinkedList *second);

/**
 * Start for everything this framework does.
 * Creates a new graph clips_graph_container. Counterpart to close_graph
 */
FFI_PLUGIN_EXPORT struct clips_graph_container init_graph(); 

/**
 * load configuration from filesystem and reset.
 *
 * example:
 * ```C
 * struct clips_graph_container graph = init_graph();
 * RET_LOADCONFIG err = load_config(graph, "path/to/config.clp");
 * if (err == CTC_LC_NO_ERROR){...}
 * close_graph(graph)
 * ```
 */
FFI_PLUGIN_EXPORT RET_LOADCONFIG load_config(struct clips_graph_container graph_container, char *configPath);

/**
 * load configuration from memory and reset.
 */
FFI_PLUGIN_EXPORT RET_LOADCONFIG load_config_mem(
		struct clips_graph_container graphContainer,
		const char* configString, size_t lengthString);

/**
 * End for everything this framework does.
 * Deletes a clips_graph_container. Counterpart to init_graph 
 */
FFI_PLUGIN_EXPORT int close_graph(struct clips_graph_container);

/**
 * Returns list of all facts in graph.
 * Filter removes all facts, that havent the exact subject, predicate or object.
 */
FFI_PLUGIN_EXPORT struct TriplesLinkedList *get_facts(struct clips_graph_container graph_container, char *filter_subject, char *filter_predicate, char *filter_object);

/**
 * Asserts fact and returns success. Expects values in builtin format.
 *
 * @param[subject] cant be NULL
 * @param[predicate] cant be NULL
 * @param[object] cant be NULL
 * @param[context] cant be NULL
 */
FFI_PLUGIN_EXPORT CRI_RET_BUILDTRIPLE assert_fact(
		struct clips_graph_container graph,
		const N3String subject, const N3String predicate,
		const N3String object, const char* context
		);

/**
 * Run logic. Returns number of rules executed.
 */
FFI_PLUGIN_EXPORT long long run_rules(struct clips_graph_container graph, long long limit);

/**
 * Evaluate given clips command. Return value has to be freed after use with 
 * \ref free_dynamic_value.
 */
FFI_PLUGIN_EXPORT struct DynamicValue eval(struct clips_graph_container, Utf8String command);


/**
 * Build given clips prompt
 */
FFI_PLUGIN_EXPORT int build(struct clips_graph_container graph, Utf8String command);

/**
 * load clips rules script and reset.
 */
FFI_PLUGIN_EXPORT bool load_script(struct clips_graph_container graph, Utf8String script);

/**
 * free dynamic value.
 */
FFI_PLUGIN_EXPORT void free_dynamic_value(struct DynamicValue val);

/**
 * add new plugin
 */
FFI_PLUGIN_EXPORT void add_plugin(struct clips_graph_container *graph);


/**
 * check if unhandled error occured
 */
FFI_PLUGIN_EXPORT bool graph_in_errorstate(struct clips_graph_container graph);

#ifdef __cplusplus
}
#endif

#endif
