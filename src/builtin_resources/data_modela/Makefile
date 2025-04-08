default: crifi_modelA.ttl crifi_modelA_checker.ttl rule-normalization.ttl transform-list.ttl rest.ttl
%.ttl: %.rifps
	rdfpipe -i rifps -o ttl $< > $@
