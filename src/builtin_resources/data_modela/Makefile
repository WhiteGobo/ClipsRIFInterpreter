default: crifi_modelA.ttl crifi_modelA_checker.ttl rule-normalization.ttl transform-list.ttl rest.ttl create-root-script.ttl constants.ttl transform-actionblock.ttl formula-as-test.ttl import-rules.ttl init-defrules.ttl action-from-formula-as-clause.ttl process-external.ttl special_pred_translations_for_pattern.ttl process_lists.ttl variable-binding.ttl process_Atom.ttl process-Frames.ttl process-equal.ttl apply-generator.ttl process_member.ttl process_subclass.ttl process_Do.ttl
%.ttl: %.rifps
	rdfpipe -i rifps -o ntriples $< > $@
