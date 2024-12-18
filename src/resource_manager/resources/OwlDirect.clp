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

(deffacts initialize-rulebase
	(TripleTemplate
		(subject _:1)
		(predicate <http://white.gobo/owldirect#rulebase>)
		(object (make-instance of AtomList)))
	(TripleTemplate
		(subject _:1)
		(predicate <http://white.gobo/owldirect#factbase>)
		(object (make-instance of AtomList)))
)

(defrule transform-member
	?f <- (TripleTemplate
		(subject ?instance)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object ?class))
	=>
	;add member skeleton to gobo:factbase
	(assert (Member (instance ?instance) (class ?class)))
	(retract ?f)
)

(deffunction create-clips-script (?description)
	(set-error "owldirect not implemented")
	(println "owldirect not implemented")
	(return "")
)
