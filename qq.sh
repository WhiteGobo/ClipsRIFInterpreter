#!/usr/bin/bash

set -e #exit on failure
set -x

entailment="resources/rules_rif_to_clips_script/SimpleEntailment.rifps"
#entailment="resources/rules_rif_to_clips_script/test.rifps"

entailment_ttl="tmp/SimpleEntailment.ttl"

mkdir -p tmp

rdfpipe -i rifps -o ttl \
	$entailment \
	> tmp/SimpleEntailment.ttl

rdfpipe -i rifps -o ttl \
	resources/tmp/Assert-premise.rifps \
	> tmp/Assert-premise.ttl

./build/generate_crifi_script/generate_crifi_script \
	-i tmp/SimpleEntailment.ttl

./build/generate_crifi_script/generate_crifi_script \
	-i tmp/SimpleEntailment.ttl \
	> tmp/SimpleEntailment.clp

cat tmp/SimpleEntailment.clp

./build/generate_crifi_script/oneshot_crifi_script \
	-o turtle \
	-d tmp/Assert-premise.ttl \
	tmp/SimpleEntailment.clp \
	> tmp/qq.out.ttl

python helper_myfilter.py tmp/qq.out.ttl \
	http://example.com/ \
	http://clips.script/ \
	#http://www.w3.org/2007/rif# \


cat tmp/Assert-premise.clp

./build/generate_crifi_script/oneshot_crifi_script \
	-o clipsscript \
	-d tmp/Assert-premise.ttl \
	tmp/SimpleEntailment.clp 
