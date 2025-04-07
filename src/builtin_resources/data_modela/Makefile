default: crifi_modelA.ttl rule-normalization.ttl transform-list.ttl
%.ttl: %.rifps
	rdfpipe -i rifps -o ttl $< > $@
