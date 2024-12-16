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

(deffunction print-member (?instance ?class) (str-cat 
"	(Member
		(instance " ?instance ")
		(class " ?class "))"
	))

(deffunction print-subclass (?sub ?super) (str-cat 
"	(Subclass
		(sub " ?sub ")
		(super " ?super "))"
	))

(defrule transform-member
	?f <- (TripleTemplate
		(subject ?instance)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object ?class))
	=>
	(assert (Member (instance ?instance) (class ?class)))
	(retract ?f)
)

(defrule transform-subclass
	?f <- (TripleTemplate
		(subject ?sub)
		(predicate <http://www.w3.org/2000/01/rdf-schema#subClassOf>)
		(object ?super))
	=>
	(assert (Subclass (sub ?sub) (super ?super)))
	(retract ?f)
)

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
	(bind ?factprint (create$))
	(do-for-all-facts ((?triple TripleTemplate)) TRUE
		(bind ?s ?triple:subject)
		(bind ?p ?triple:predicate)
		(bind ?o ?triple:object)
		(bind ?factprint (append$ ?factprint
					(print-triple ?s ?p ?o)))
	)
	(do-for-all-facts ((?member Member)) TRUE
		(bind ?factprint (append$ ?factprint
				(print-member ?member:instance ?member:class)))
	)
	(do-for-all-facts ((?fct Subclass)) TRUE
		(bind ?factprint (append$ ?factprint
				(print-subclass ?fct:sub ?fct:super)))
	)

	(if (eq 0 (length$ ?factprint)) then 
		(facts)
		(println "no rules created.")
		(return ""))
	(bind ?rules (print-deffacts (gensym) ?factprint))
	(bind ?err (clear-error))
	(if ?err then
		(println "caught errors during create-clips-script: " ?err)
		(return "")
	)
	(str-cat ?desc "
" ?templates "
" ?rules)
)
