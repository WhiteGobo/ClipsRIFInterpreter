(deffunction <http://white.gobo/crifi/resource-manager#set_name> (?name)
	(assert (Atom
		(op <http://white.gobo/crifi/resource-manager#name>)
		(args ?name)))
)

(deffunction <http://white.gobo/crifi/resource-manager#create_script> ()
	(bind ?name (gensym))
	(do-for-fact ((?f Atom))
		(eq ?f:op <http://white.gobo/crifi/resource-manager#name>)
		(bind ?name (expand$ ?f:args)))
	(format <http://white.gobo/crifi/resource-manager#outputrouter>
		"(deffacts %s%n" ?name
	)
	(do-for-all-facts ((?fct Atom))
		(eq ?fct:op <http://white.gobo/crifi/resource-manager/deffacts#triple>)
		(format <http://white.gobo/crifi/resource-manager#outputrouter>
			"	(TripleTemplate (subject %s) (predicate %s) (object %s))%n" (expand$ ?fct:args)
		)
	)
	(do-for-all-facts ((?fct Atom))
		(eq ?fct:op <http://white.gobo/crifi/resource-manager/deffacts#member>)
		(format <http://white.gobo/crifi/resource-manager#outputrouter>
			"	(Member (instance %s) (class %s))%n" (expand$ ?fct:args)
		)
	)
	(do-for-all-facts ((?fct Atom))
		(eq ?fct:op <http://white.gobo/crifi/resource-manager/deffacts#subclass>)
		(format <http://white.gobo/crifi/resource-manager#outputrouter>
			"	(Subclass (sub %s) (super %s))%n" (expand$ ?fct:args)
		)
	)
	(do-for-all-facts ((?fct Atom))
		(eq ?fct:op <http://white.gobo/crifi/resource-manager/deffacts#equal>)
		(format <http://white.gobo/crifi/resource-manager#outputrouter>
			"	(Equal (left %s) (right %s))%n" (expand$ ?fct:args)
		)
	)
	(format <http://white.gobo/crifi/resource-manager#outputrouter>
		")%n"
	)
)
