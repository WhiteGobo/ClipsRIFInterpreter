default: crifi_modelA.ttl crifi_modelA_checker.ttl rule-normalization.ttl transform-list.ttl rest.ttl create-root-script.ttl constants.ttl transform-actionblock.ttl formula-as-test.ttl import-rules.ttl init-defrules.ttl add-as-pattern.ttl action-from-formula-as-clause.ttl process-external.ttl special_pred_translations_for_pattern.ttl process_lists.ttl
%.ttl: %.rifps
	rdfpipe -i rifps -o ntriples $< > $@
