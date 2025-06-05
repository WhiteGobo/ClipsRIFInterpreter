default: openlist_as_pattern-premise.ttl openlist_as_pattern-conclusion.ttl stacked_conditionals1-premise.ttl stacked_conditionals1-conclusion.ttl

%.ttl: %.rifps
	rdfpipe -i rifps -o ntriples $< > $@
