set(CRIFI_MODELA_DATA_BASEURI "http://white.gobo/crifi/built_resources/data_modela#")
set(hint "data_modela")
set(compilelist_modela "" PARENT_SCOPE)

list(APPEND mytargets
	crifi_modelA
	crifi_modelA_checker
	rule-normalization
	transform-list
	rest
	create-root-script
	constants
	transform-actionblock
	formula-as-test
	import-rules
	init-defrules
	action-from-formula-as-clause
	process-external
	special_pred_translations_for_pattern
	process_lists
	process_member
	process_subclass
	process_Do
	inheritance

	variable-binding
	process_Atom
	process-Frames
	process-equal
	process_execute
	apply-generator
)

set(compilelist)
#list(APPEND uriendings "" ".ttl" ".rif" ".rifps")
set(targetending "ttl")
foreach(base ${mytargets})
	unset(targetfile)
	set(targetfilename "${base}.${targetending}")
	find_file(targetfile "${targetfilename}" HINTS "${hint}" NO_CACHE)
	if(NOT targetfile)
		message(FATAL_ERROR "missing file ${targetfilename} in ${hint}")
	endif()
	set(ending "")
	#foreach(ending ${uriendings})
		set(targeturi "${CRIFI_MODELA_DATA_BASEURI}${base}${ending}")
		list(APPEND compilelist_modela ${targeturi} ${targetfile})
	#endforeach()
endforeach()
