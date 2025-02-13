#include "n3parser.h"

#include "percent_encode.h"

#define REGEXURIREF "^<("URLSYMBOLS"*)>$"
#define REGEXBLANKNODE "^_:("URLSYMBOLS"+)$"
#define REGEXDATATYPESINGLE "^\'(.*)\'[°^][°^]<("URLSYMBOLS"*)>$"
#define REGEXDATATYPE "^\"(.*)\"[°^][°^]<("URLSYMBOLS"*)>$"
#define REGEXLANG "^\"(([^\"]|(\\\"))*)\"@([a-zA-Z\-]*)$"
#define REGEXLANGSINGLE "^\'(([^\']|(\\\'))*)\'@([a-zA-Z\-]*)$"
#define REGEXSIMPLESINGLE "^\'(.*)\'$"
#define REGEXSIMPLE "^\"(.*)\"$"
#define REGEXCLIPSVALUELANGSTRING "^(.*)@@(.*)$"
#define REGEXCLIPSVALUELITERAL "^(.*)[°^][°^](.*)$"

/**
 * method given at registration for tidying up timedata after Environment is
 * freed
 */
static void release_crifi_n3parserdata(Environment *env){
	free_crifi_n3parserdata(LoadingCRIFIN3ParserData(env));
}

bool crifi_n3parserdata_register_data(Environment *env){
	if (! AllocateEnvironmentData(env, CRIFI_N3PARSER_DATA_INDEX,
						sizeof(CRIFIN3ParserData),
						release_crifi_n3parserdata))
	{
		Writeln(env, "Internal error 0. "
				"Cant load plugin for n3 parsing..");
		ExitRouter(env, EXIT_FAILURE);
		return false;
	}
	if(!initialize_crifi_n3parserdata(LoadingCRIFIN3ParserData(env))){
		return false;
	}
	return true;
}

bool initialize_crifi_n3parserdata(CRIFIN3ParserData *data){
	int err;
	data->next_blanknode_id = 0;
	err = regcomp(&(data->reg_uriref),
			REGEXURIREF,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	err = regcomp(&(data->reg_blanknode),
			REGEXBLANKNODE,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	err = regcomp(&(data->reg_datatype),
			REGEXDATATYPE,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	err = regcomp(&(data->reg_datatype_single),
			REGEXDATATYPESINGLE,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	err = regcomp(&(data->reg_lang),
			REGEXLANG,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	err = regcomp(&(data->reg_lang_single),
			REGEXLANGSINGLE,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	err = regcomp(&(data->reg_simple),
			REGEXSIMPLE,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	err = regcomp(&(data->reg_simple_single),
			REGEXSIMPLESINGLE,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	err = regcomp(&(data->reg_clipsvalue_langString),
			REGEXCLIPSVALUELANGSTRING,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	err = regcomp(&(data->reg_clipsvalue_literal),
			REGEXCLIPSVALUELITERAL,
			REG_EXTENDED);
	if (err != 0){
		free_crifi_n3parserdata(data);
		return false;
	}
	return true;
}

void free_crifi_n3parserdata(CRIFIN3ParserData *data){
	regfree(&(data->reg_uriref));
	regfree(&(data->reg_blanknode));
	regfree(&(data->reg_datatype));
	regfree(&(data->reg_datatype_single));
	regfree(&(data->reg_lang));
	regfree(&(data->reg_lang_single));
	regfree(&(data->reg_simple));
	regfree(&(data->reg_simple_single));
	regfree(&(data->reg_clipsvalue_langString));
	regfree(&(data->reg_clipsvalue_literal));
}

