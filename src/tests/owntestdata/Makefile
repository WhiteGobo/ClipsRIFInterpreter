default: openlist_as_pattern-premise.ttl openlist_as_pattern-conclusion.ttl

%.ttl: %.rifps
	rdfpipe -i rifps -o ntriples $< > $@
