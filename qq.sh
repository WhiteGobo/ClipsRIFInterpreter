#!/usr/bin/bash

set -e #exit on failure
set -x

rdfpipe -i rifps -o ttl \
	resources/rules_rif_to_clips_script/SimpleEntailment.rifps \
	> tmp/SimpleEntailment.ttl

rdfpipe -i rifps -o ttl \
	resources/tmp/Assert-premise.rifps \
	> tmp/Assert-premise.ttl

./build/generate_crifi_script/generate_crifi_script \
	-i tmp/SimpleEntailment.ttl \
	> tmp/SimpleEntailment.clp

cat tmp/SimpleEntailment.clp

./build/generate_crifi_script/oneshot_crifi_script \
	-d tmp/Assert-premise.ttl \
	tmp/SimpleEntailment.clp
