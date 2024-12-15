(deffunction append$ (?l $?x) (insert$ ?l (+ 1 (length$ ?l)) $?x))

(deffunction print-deffacts (?name ?triples) (str-cat
"(deffacts " ?name "
	" (expand$ ?triples) ")
"))

(deffunction print-triple (?subject ?predicate ?object) (str-cat 
"	(TripleTemplate
		(subject " ?subject ")
		(predicate " ?predicate ")
		(object " ?object "))"
	))

(deffunction create-clips-script (?description)
	(bind ?err (get-error))
	(if ?err then
		(println "caught errors before create-clips-script: " ?err)
		(return)
	)
	;replace newline with commented newlines:
	(bind ?desc (str-cat ";" ?description))
	(bind ?desc (str-replace ?desc "
" "
;"))
	(bind ?templates "")
	(bind ?triplesprint (create$))
	(do-for-all-facts ((?triple TripleTemplate)) TRUE
		(bind ?s ?triple:subject)
		(bind ?p ?triple:predicate)
		(bind ?o ?triple:object)
		(bind ?triplesprint (append$ ?triplesprint
					(print-triple ?s ?p ?o)))
	)
	(if (eq 0 (length$ ?triplesprint)) then 
		(facts)
		(println "no rules created.")
		(return ""))
	(bind ?rules (print-deffacts (gensym) ?triplesprint))
	(bind ?err (clear-error))
	(if ?err then
		(println "caught errors during create-clips-script: " ?err)
		(return "")
	)
	(str-cat ?desc "
" ?templates "
" ?rules)
)
