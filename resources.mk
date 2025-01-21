${TMPDIR}/OwlDirect.clp ${TMPDIR}/SimpleEntailment.clp ${TMPDIR}/RifLogic.clp::

${TMPDIR}/%.ntriples: resources/script_resource_manager/%.rifps
	mkdir -p ${TMPDIR}
	rdfpipe -i rifps -o ttl $<
	rdfpipe -i rifps -o ntriples $< > $@

${TMPDIR}/%.clp: ${TMPDIR}/%.ntriples
	${ENV_GENERATOR} generate_crifi_script -i $<
	${ENV_GENERATOR} generate_crifi_script -i $< > $@
	touch $@

TARGET_OT_RIFPS = ${TMPDIR}/official_tests_from_rifps

${TMPDIR}/RDF_Combination_Constant_Equivalence_1-import001.ntriples ${TMPDIR}/RDF_Combination_Constant_Equivalence_2-import001.ntriples ${TMPDIR}/RDF_Combination_Constant_Equivalence_3-import001.ntriples ${TMPDIR}/RDF_Combination_Constant_Equivalence_4-import001.ntriples ${TARGET_OT_RIFPS}/Builtins_String-premise.ntriples ${TARGET_OT_RIFPS}/Builtins_String-conclusion.ntriples::

${TMPDIR}/%.ntriples: resources/official_tests/%.ttl
	mkdir -p ${TMPDIR}
	rdfpipe -i ttl -o ntriples $< > $@
	printf "to update test:\n\ncp %s src/tests/data/\n\n" $@

${TARGET_OT_RIFPS}/%.ntriples: resources/official_tests/%.rifps
	mkdir -p ${TARGET_OT_RIFPS}
	rdfpipe -i rifps -o ntriples $< > $@
	printf "to update test:\n\ncp %s src/tests/data/\n\n" $@
