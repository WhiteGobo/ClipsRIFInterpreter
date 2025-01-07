(deffunction <http://white.gobo/crifi/resource-manager#set_name> (?name)
	(assert (Atom
		(op <http://white.gobo/crifi/resource-manager#name>)
		(args ?name)))
)

(deffunction send-triple (?target ?subject ?predicate ?object)
	(if (eq STRING (type ?subject))
		then (bind ?subject (str-cat "\"" ?subject "\"")))
	(if (eq STRING (type ?predicate))
		then (bind ?predicate (str-cat "\"" ?predicate "\"")))
	(if (eq STRING (type ?object))
		then (bind ?object (str-cat "\"" ?object "\"")))
	(format ?target
		"	(TripleTemplate (subject %s) (predicate %s) (object %s))%n" ?subject ?predicate ?object
	)
)

(deffunction send-member (?target ?instance ?class )
	(if (eq STRING (type ?instance))
		then (bind ?instance (str-cat "\"" ?instance "\"")))
	(if (eq STRING (type ?class))
		then (bind ?class (str-cat "\"" ?class "\"")))
	(format ?target
		"	(Member (instance %s) (class %s))%n"
		?instance ?class
	)
)
(deffunction send-equal (?target ?left ?right)
	(if (eq STRING (type ?left))
		then (bind ?left (str-cat "\"" ?left "\"")))
	(if (eq STRING (type ?right))
		then (bind ?right (str-cat "\"" ?right "\"")))
	(format ?target
		"	(Equal (left %s) (right %s))%n" ?left ?right
	)
)
(deffunction send-subclass (?target ?sub ?super)
	(if (eq STRING (type ?sub))
		then (bind ?sub (str-cat "\"" ?sub "\"")))
	(if (eq STRING (type ?super))
		then (bind ?super (str-cat "\"" ?super "\"")))
	(format ?target
		"	(Subclass (sub %s) (super %s))%n" ?sub ?super
	)
)

(deffunction my-print-deffacts (?name)
	(format <http://white.gobo/crifi/resource-manager#outputrouter>
		"(deffacts %s%n" ?name
	)
	(do-for-all-facts ((?fct Atom))
		(eq ?fct:op <http://white.gobo/crifi/resource-manager/deffacts#triple>)
		(send-triple <http://white.gobo/crifi/resource-manager#outputrouter>
			(expand$ ?fct:args))
	)
	(do-for-all-facts ((?fct Atom))
		(eq ?fct:op <http://white.gobo/crifi/resource-manager/deffacts#member>)
		(send-member <http://white.gobo/crifi/resource-manager#outputrouter>
			(expand$ ?fct:args))
	)
	(do-for-all-facts ((?fct Atom))
		(eq ?fct:op <http://white.gobo/crifi/resource-manager/deffacts#subclass>)
		(send-subclass <http://white.gobo/crifi/resource-manager#outputrouter>
			(expand$ ?fct:args))
	)
	(do-for-all-facts ((?fct Atom))
		(eq ?fct:op <http://white.gobo/crifi/resource-manager/deffacts#equal>)
		(send-equal <http://white.gobo/crifi/resource-manager#outputrouter>
			(expand$ ?fct:args))
	)
	(format <http://white.gobo/crifi/resource-manager#outputrouter>
		")%n"
	)
)

(deffunction <http://white.gobo/crifi/resource-manager#create_script> ()
	(bind ?name (gensym))
	(do-for-fact ((?f Atom))
		(eq ?f:op <http://white.gobo/crifi/resource-manager#name>)
		(bind ?name (expand$ ?f:args)))
	(my-print-deffacts ?name)
)
