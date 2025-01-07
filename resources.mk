${TMPDIR}/OwlDirect.clp ${TMPDIR}/SimpleEntailment.clp::

${TMPDIR}/%.ntriples: resources/script_resource_manager/%.rifps
	mkdir -p ${TMPDIR}
	rdfpipe -i rifps -o ntriples $< > $@

${TMPDIR}/%.clp: ${TMPDIR}/%.ntriples
	${ENV_GENERATOR} generate_crifi_script -i $<
	${ENV_GENERATOR} generate_crifi_script -i $< > $@
	touch $@


${TMPDIR}/%.ntriples: resources/official_tests/%.ttl
	rdfpipe -i ttl -o ntriples $< > $@
	printf "to update test:\n\ncp %s src/tests/data/\n\n" $@
