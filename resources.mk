${TMPDIR}/OwlDirect.clp ${TMPDIR}/SimpleEntailment.clp ${TMPDIR}/RifLogic.clp::

${TMPDIR}/%.ntriples: resources/script_resource_manager/%.rifps
	mkdir -p ${TMPDIR}
	rdfpipe -i rifps -o ttl $<
	rdfpipe -i rifps -o ntriples $< > $@

${TMPDIR}/%.clp: ${TMPDIR}/%.ntriples
	${ENV_GENERATOR} generate_crifi_script -i $<
	${ENV_GENERATOR} generate_crifi_script -i $< > $@
	touch $@

${TMPDIR}/RDF_Combination_Constant_Equivalence_1-import001.ntriples ${TMPDIR}/RDF_Combination_Constant_Equivalence_2-import001.ntriples ${TMPDIR}/RDF_Combination_Constant_Equivalence_3-import001.ntriples ${TMPDIR}/RDF_Combination_Constant_Equivalence_4-import001.ntriples ${TMPDIR}/Builtins_String-premise.rifps ${TMPDIR}/Builtins_String-conclusion.rifps::

${TMPDIR}/%.ntriples: resources/official_tests/%.ttl
	rdfpipe -i ttl -o ntriples $< > $@
	printf "to update test:\n\ncp %s src/tests/data/\n\n" $@
