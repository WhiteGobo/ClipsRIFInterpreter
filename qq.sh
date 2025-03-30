#!/usr/bin/bash

set -e #exit on failure
set -x

if test -z "$logic_input"; then
	#logic_input="resources/tmp/Assert-premise.rifps"
	logic_input="resources/tmp/AssertRetract-premise.rifps"
fi

entailment="resources/rules_rif_to_clips_script/SimpleEntailment.rifps"
#entailment="resources/rules_rif_to_clips_script/test.rifps"

filename=$(basename -- "$logic_input")
extensionlogic="${filename##*.}"
filename=$(basename -- "$entailment")
extensionentailment="${filename##*.}"

temp_logic_in_ttl="tmp/temp_logic_in_ttl.ttl"
temp_clips_script_all_data="tmp/qq.out.ttl"

mkdir -p tmp

echo "transform data from rifps to turtle"
rdfpipe -i $extensionentailment -o ttl \
	$entailment \
	> tmp/SimpleEntailment.ttl

rdfpipe -i $extensionlogic -o ttl \
	$logic_input \
	> $temp_logic_in_ttl

echo "generate SimpleEntailment script"
./build/generate_crifi_script/generate_crifi_script \
	-i tmp/SimpleEntailment.ttl

./build/generate_crifi_script/generate_crifi_script \
	-i tmp/SimpleEntailment.ttl \
	> tmp/SimpleEntailment.clp

#cat tmp/SimpleEntailment.clp

echo "generate only data for the new script"
./build/generate_crifi_script/oneshot_crifi_script \
	-o turtle \
	-d $temp_logic_in_ttl \
	-m rif \
	tmp/SimpleEntailment.clp \
	> $temp_clips_script_all_data

python helper_myfilter.py $temp_clips_script_all_data \
	http://example.com/ \
	http://clips.script/ \
	#http://www.w3.org/2007/rif# \

echo "generate new script itself"
./build/generate_crifi_script/oneshot_crifi_script \
	-o clipsscript \
	-d $temp_logic_in_ttl \
	-m rif \
	tmp/SimpleEntailment.clp 
