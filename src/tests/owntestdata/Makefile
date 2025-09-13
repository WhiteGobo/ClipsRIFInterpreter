default: openlist_as_pattern-premise.ttl openlist_as_pattern-conclusion.ttl stacked_conditionals1-premise.ttl stacked_conditionals1-conclusion.ttl circular_patterns1-premise.ttl circular_patterns1-conclusion.ttl circular_patterns2-premise.ttl circular_patterns2-nonconclusion.ttl assign_var1-input.ttl assign_var2-input.ttl assign_var3-input.ttl assign_var4-input.ttl assign_var5-input.ttl assign_var6-input.ttl assign_var7-input.ttl assign_var8-input.ttl assign_var9-input.ttl assign_var10-input.ttl assign_var11-input.ttl  Membership-premise.ttl Membership-conclusion.ttl Subclass-premise.ttl Subclass-conclusion.ttl actionvar1-conclusion.ttl actionvar1-premise.ttl actionvar2-conclusion.ttl actionvar2-premise.ttl

%.ttl: %.rifps
	rdfpipe -i rifps -o ntriples $< > $@
